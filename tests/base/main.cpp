
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>

#include <yas/serializers/std_types_serializers.hpp>

#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/text_iarchive.hpp>
#include <yas/text_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/json_oarchive.hpp>

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

#include "include/speed_one_function.hpp"
#include "include/speed_one_method.hpp"
#include "include/speed_split_functions.hpp"
#include "include/speed_split_methods.hpp"

/***************************************************************************/

template<typename OA, typename IA>
bool tests(yas::uint32_t& p, yas::uint32_t& e, yas::uint32_t iterations, std::vector<std::string>& reports) {
	static const char* archive_type =
	yas::is_binary_archive<OA>::value ? "binary:"
		: yas::is_text_archive<OA>::value ? "text  :"
			: yas::is_json_archive<OA>::value ? "json  :"
				: "unknown:";

	static const char* passed = "passed";
	static const char* failed = "failed!";

	printf("%s VERSION            test %s\n", archive_type, (version_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s POD                test %s\n", archive_type, (pod_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s ENUM               test %s\n", archive_type, (enum_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s BASE_OBJECT        test %s\n", archive_type, (base_object_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s AUTO_ARRAY         test %s\n", archive_type, (auto_array_test<OA, IA>()?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_ARRAY) || defined(YAS_HAS_STD_ARRAY)
	printf("%s ARRAY              test %s\n", archive_type, (array_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
	printf("%s BITSET             test %s\n", archive_type, (bitset_test<OA, IA>()?(++p,passed):(++e,failed)));
#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR) || defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
	printf("%s BUFFER             test %s\n", archive_type, (buffer_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
	printf("%s STRING             test %s\n", archive_type, (string_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s WSTRING            test %s\n", archive_type, (wstring_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s PAIR               test %s\n", archive_type, (pair_test<OA, IA>()?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_TUPLE) || defined(YAS_HAS_STD_TUPLE)
	printf("%s TUPLE              test %s\n", archive_type, (tuple_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
	printf("%s VECTOR             test %s\n", archive_type, (vector_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s LIST               test %s\n", archive_type, (list_test<OA, IA>()?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_STD_FORWARD_LIST)
	printf("%s FORWARD_LIST       test %s\n", archive_type, (forward_list_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
	printf("%s MAP                test %s\n", archive_type, (map_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s SET                test %s\n", archive_type, (set_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s MULTIMAP           test %s\n", archive_type, (multimap_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s MULTISET           test %s\n", archive_type, (multiset_test<OA, IA>()?(++p,passed):(++e,failed)));
#if defined(YAS_HAS_BOOST_UNORDERED) || defined(YAS_HAS_STD_UNORDERED)
	printf("%s UNORDERED_MAP      test %s\n", archive_type, (unordered_map_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_SET      test %s\n", archive_type, (unordered_set_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_MULTIMAP test %s\n", archive_type, (unordered_multimap_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s UNORDERED_MULTISET test %s\n", archive_type, (unordered_multiset_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
#if defined(YAS_HAS_BOOST_FUSION)
	printf("%s FUSION_PAIR        test %s\n", archive_type, (fusion_pair_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s FUSION_TUPLE       test %s\n", archive_type, (fusion_tuple_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s FUSION_VECTOR      test %s\n", archive_type, (fusion_vector_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s FUSION_LIST        test %s\n", archive_type, (fusion_list_test<OA, IA>()?(++p,passed):(++e,failed)));
//   printf("%s FUSION_SET         test %s\n", archive_type, (fusion_set_test<OA, IA>()?(++p,passed):(++e,failed)));
//   printf("%s FUSION_MAP         test %s\n", archive_type, (fusion_map_test<OA, IA>()?(++p,passed):(++e,failed)));
#endif
	printf("%s ONE_FUNCTION       test %s\n", archive_type, (one_function_serializer_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s SPLIT_FUNCTIONS    test %s\n", archive_type, (split_functions_serializer_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s ONE_METHOD         test %s\n", archive_type, (one_method_serializer_test<OA, IA>()?(++p,passed):(++e,failed)));
	printf("%s SPLIT_METHODS      test %s\n", archive_type, (split_methods_serializer_test<OA, IA>()?(++p,passed):(++e,failed)));

	reports.push_back(one_function_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(split_functions_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(one_method_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(split_methods_speed_test<OA, IA>(iterations, archive_type));

	return true;
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	types_test();

	yas::uint32_t passed = 0;
	yas::uint32_t failed = 0;

	yas::uint32_t iterations = 1024*1024*10;
	std::vector<std::string> reports;

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>(passed, failed, iterations, reports);
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>(passed, failed, iterations, reports);
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>(passed, failed, iterations, reports);

	std::cout << std::endl
	<< "/***************************************************/" << std::endl
	<< "> platform bits: " << (YAS_PLATFORM_BITS_IS_64()?64:32) << std::endl
	<< "> passed tests : " << passed << std::endl
	<< "> failed tests : " << failed << std::endl
	<< "/***************************************************/" << std::endl;

	std::vector<std::string>::const_iterator it = reports.begin();
	for ( ; it != reports.end(); ++it ) {
		std::cout << *it << std::endl;
	}
}

/***************************************************************************/
