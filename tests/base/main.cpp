
#include <iostream>
#include <algorithm>
#include <numeric>

#include <cstdio>
#include <ctime>

#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/text_iarchive.hpp>
#include <yas/text_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/json_oarchive.hpp>

#include <yas/serializers/std_types_serializers.hpp>

#if defined(YAS_SERIALIZE_BOOST_TYPES)
#include <yas/serializers/boost_types_serializers.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/include/comparison.hpp>
#endif // defined(YAS_SERIALIZE_BOOST_TYPES)

#if defined(YAS_SERIALIZE_QT_TYPES)
#include <yas/serializers/qt_types_serializers.hpp>
#endif

#include "include/array.hpp"
#include "include/auto_array.hpp"
#include "include/bitset.hpp"
#include "include/buffer.hpp"
#include "include/enum.hpp"
#include "include/base_object.hpp"
#include "include/forward_list.hpp"
#include "include/fusion_list.hpp"
#include "include/fusion_map.hpp"
#include "include/fusion_pair.hpp"
#include "include/fusion_set.hpp"
#include "include/fusion_tuple.hpp"
#include "include/fusion_vector.hpp"
#include "include/list.hpp"
#include "include/map.hpp"
#include "include/multimap.hpp"
#include "include/multiset.hpp"
#include "include/pair.hpp"
#include "include/pod.hpp"
#include "include/set.hpp"
#include "include/string.hpp"
#include "include/tuple.hpp"
#include "include/types.hpp"
#include "include/unordered_map.hpp"
#include "include/unordered_multimap.hpp"
#include "include/unordered_multiset.hpp"
#include "include/unordered_set.hpp"
#include "include/vector.hpp"
#include "include/version.hpp"
#include "include/wstring.hpp"

#include "include/one_function.hpp"
#include "include/one_method.hpp"
#include "include/split_functions.hpp"
#include "include/split_methods.hpp"

/***************************************************************************/

template<bool, typename, typename>
struct concrete_archive_traits;

template<typename OA, typename IA>
struct concrete_archive_traits<true, OA, IA> {
	typedef OA oarchive_type;
	typedef IA iarchive_type;
//#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR)
//	typedef std::shared_ptr<oarchive_type> oarchive_ptr;
//	typedef std::shared_ptr<iarchive_type> iarchive_ptr;
//#elif defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
//	typedef boost::shared_ptr<oarchive_type> oarchive_ptr;
//	typedef boost::shared_ptr<iarchive_type> iarchive_ptr;
//#else
	typedef std::auto_ptr<OA> oarchive_ptr;
	typedef std::auto_ptr<IA> iarchive_ptr;
//#endif

	static oarchive_ptr ocreate(const char*) {
		oarchive_ptr archive(new oarchive_type);
		return archive;
	}
	static iarchive_ptr icreate(const char*) { return 0; }
	static iarchive_ptr icreate(const char*, const yas::intrusive_buffer& buf) {
		iarchive_ptr archive(new iarchive_type(buf));
		return archive;
	}
};

template<typename OA, typename IA>
struct concrete_archive_traits<false, OA, IA> {
	typedef OA oarchive_type;
	typedef IA iarchive_type;

	struct oarchive_ptr {
		oarchive_ptr(const std::string& fname) {
			file.reset(new std::ofstream(fname));
			archive.reset(new OA(*file));
		}
		oarchive_ptr(const oarchive_ptr& r)
		{file=r.file;archive=r.archive;}

		OA* operator->() { return archive.get(); }

	private:
		std::auto_ptr<std::ofstream> file;
		std::auto_ptr<OA> archive;
	};

	struct iarchive_ptr {
		iarchive_ptr(const std::string& fname) {
			file.reset(new std::ifstream(fname));
			archive.reset(new IA(*file));
		}

		IA* operator->() { return archive.get(); }
	private:
		std::auto_ptr<std::ifstream> file;
		std::auto_ptr<IA> archive;
	};

	static oarchive_ptr ocreate(const char* archive_type) {
		static const std::string filename("test."); filename += archive_type;
		return oarchive_ptr(filename);
	}
	static iarchive_ptr icreate(const char* archive_type) {
		static const std::string filename("test."); filename += archive_type;
		return iarchive_ptr(filename);
	}
};

/***************************************************************************/

template<typename OA, typename IA>
void tests(yas::uint32_t& p, yas::uint32_t& e) {
	static const char* archive_type =
	yas::is_binary_archive<OA>::value ? "binary"
		: yas::is_text_archive<OA>::value ? "text"
			: yas::is_json_archive<OA>::value ? "json"
				: "unknown"
	;

	typedef concrete_archive_traits<
		 yas::is_mem_archive<OA>::value
		,OA
		,IA
	> concrete_traits;

	static const char* passed = "passed";
	static const char* failed = "failed!";

	printf("%8s: VERSION          test %s\n", archive_type, (version_test<concrete_traits>(archive_type)?(++p,passed):(++e,failed)));
	printf("%8s: POD              test %s\n", archive_type, (pod_test<concrete_traits>(archive_type)?(++p,passed):(++e,failed)));
#if 0
	printf("%s ENUM               test %s\n", archive_type, (enum_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s BASE_OBJECT        test %s\n", archive_type, (base_object_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s AUTO_ARRAY         test %s\n", archive_type, (auto_array_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_ARRAY) || defined(YAS_HAS_STD_ARRAY)
	printf("%s ARRAY              test %s\n", archive_type, (array_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
	printf("%s BITSET             test %s\n", archive_type, (bitset_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR) || defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
	printf("%s BUFFER             test %s\n", archive_type, (buffer_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
	printf("%s STRING             test %s\n", archive_type, (string_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s WSTRING            test %s\n", archive_type, (wstring_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s PAIR               test %s\n", archive_type, (pair_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_TUPLE) || defined(YAS_HAS_STD_TUPLE)
	printf("%s TUPLE              test %s\n", archive_type, (tuple_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
	printf("%s VECTOR             test %s\n", archive_type, (vector_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s LIST               test %s\n", archive_type, (list_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_STD_FORWARD_LIST)
	printf("%s FORWARD_LIST       test %s\n", archive_type, (forward_list_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
	printf("%s MAP                test %s\n", archive_type, (map_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s SET                test %s\n", archive_type, (set_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s MULTIMAP           test %s\n", archive_type, (multimap_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s MULTISET           test %s\n", archive_type, (multiset_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_UNORDERED) || defined(YAS_HAS_STD_UNORDERED)
	printf("%s UNORDERED_MAP      test %s\n", archive_type, (unordered_map_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_SET      test %s\n", archive_type, (unordered_set_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_MULTIMAP test %s\n", archive_type, (unordered_multimap_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_MULTISET test %s\n", archive_type, (unordered_multiset_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
#if defined(YAS_HAS_BOOST_FUSION)
	printf("%s FUSION_PAIR        test %s\n", archive_type, (fusion_pair_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s FUSION_TUPLE       test %s\n", archive_type, (fusion_tuple_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s FUSION_VECTOR      test %s\n", archive_type, (fusion_vector_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s FUSION_LIST        test %s\n", archive_type, (fusion_list_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
//   printf("%s FUSION_SET         test %s\n", archive_type, (fusion_set_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
//   printf("%s FUSION_MAP         test %s\n", archive_type, (fusion_map_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
	printf("%s ONE_FUNCTION       test %s\n", archive_type, (one_function_serializer_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s SPLIT_FUNCTIONS    test %s\n", archive_type, (split_functions_serializer_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s ONE_METHOD         test %s\n", archive_type, (one_method_serializer_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
	printf("%s SPLIT_METHODS      test %s\n", archive_type, (split_methods_serializer_test<OA, IA>(archive_type)?(++p,passed):(++e,failed)));
#endif
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	types_test();

	yas::uint32_t passed = 0;
	yas::uint32_t failed = 0;

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>(passed, failed);
	//tests<yas::binary_file_oarchive, yas::binary_file_iarchive>(passed, failed);
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>(passed, failed);
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>(passed, failed);

	std::cout << std::endl
	<< "/***************************************************/" << std::endl
	<< "> platform bits: " << (YAS_PLATFORM_BITS_IS_64()?64:32) << std::endl
	<< "> passed tests : " << passed << std::endl
	<< "> failed tests : " << failed << std::endl
	<< "/***************************************************/" << std::endl;
}

/***************************************************************************/
