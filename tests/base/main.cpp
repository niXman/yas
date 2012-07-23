
#include <iostream>
#include <fstream>
#include <cstdio>

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

// mem archives traits
template<typename OA, typename IA>
struct concrete_archive_traits<true, OA, IA> {
	typedef OA oarchive_type;
	typedef IA iarchive_type;

	/** output archive */
	struct oarchive {
		oarchive():oa(0) {}
		~oarchive() { delete oa; }

		oarchive_type* operator->() { return oa; }

		template<typename T>
		oarchive_type& operator& (const T& v) { return (*(oa) & v); }

		yas::uint32_t size() const { return oa->get_intrusive_buffer().size; }

		bool compare(const void* ptr, yas::uint32_t size) const {
			return size == oa->get_intrusive_buffer().size
				? (memcmp(oa->get_intrusive_buffer().data, ptr, size)==0)
				: false
			;
		}

		oarchive_type* oa;
	};
	static void ocreate(oarchive& oa, const char* archive_type, const char* io_type) {
		((void)archive_type);
		((void)io_type);
		oa.oa = new oarchive_type;
	}

	/** input archive */
	struct iarchive {
		iarchive():ia(0) {}
		~iarchive() { delete ia; }

		iarchive_type* operator->() { return ia; }

		template<typename T>
		iarchive_type& operator& (T& v) { return (*(ia) & v); }

		iarchive_type* ia;
	};
	static void icreate(iarchive& ia, oarchive& oa, const char* archive_type, const char* io_type) {
		((void)archive_type);
		((void)io_type);
		ia.ia = new iarchive_type(oa.oa->get_intrusive_buffer());
	}
};

/***************************************************************************/

static yas::uint32_t oa_cnt = 0;

// file archives traits
template<typename OA, typename IA>
struct concrete_archive_traits<false, OA, IA> {
	typedef OA oarchive_type;
	typedef IA iarchive_type;

	struct oarchive {
		oarchive():oa(0) {++oa_cnt;}
		~oarchive() {
			delete oa;
			--oa_cnt;
			std::remove(fname.c_str());
		}

		oarchive_type* operator->() { return oa; }

		template<typename T>
		oarchive_type& operator& (const T& v) { return (*(oa) & v); }

		yas::uint32_t size() {
			file.flush();
			std::ifstream f(fname, std::ios::binary);
			f.seekg(0, std::ios::end);
			yas::uint32_t s = f.tellg();
			return s;
		}

		bool compare(const void* ptr, yas::uint32_t size) {
			if ( this->size() != size ) return false;
			std::string str(size, 0);
			std::ifstream f(fname, std::ios::binary);
			assert(f);
			f.read(&str[0], size);
			return memcmp(str.c_str(), ptr, size) == 0;
		}

		std::string fname;
		std::ofstream file;
		oarchive_type* oa;
	};
	static void ocreate(oarchive& oa, const char* archive_type, const char* io_type) {
		std::ostringstream os;
		os << oa_cnt;

		oa.fname += archive_type;
		oa.fname += "_";
		oa.fname += os.str();
		oa.fname += "_";
		oa.fname += io_type;
		oa.fname += ".bin";
		oa.file.open(oa.fname, std::ios::trunc|std::ios::binary);
		assert(oa.file.good());
		oa.oa = new oarchive_type(oa.file);
	}

	struct iarchive {
		iarchive():ia(0) {}
		~iarchive() { delete ia; }

		iarchive_type* operator->() { return ia; }

		template<typename T>
		iarchive_type& operator& (T& v) { return (*(ia) & v); }

		std::string fname;
		std::ifstream file;
		iarchive_type* ia;
	};
	static void icreate(iarchive& ia, oarchive& oa, const char* archive_type, const char* io_type) {
		((void)io_type);
		((void)archive_type);
		ia.fname = oa.fname;
		oa.file.flush();
		ia.file.open(ia.fname, std::ios::binary);
		assert(ia.file.good());
		ia.ia = new iarchive_type(ia.file);
	}
};

/***************************************************************************/

#define YAS_RUN_TEST(testname, passcnt, failcnt) \
	printf( \
		 "%-6s %-4s: %-18s -> %s\n" \
		,(yas::is_binary_archive<OA>::value ? "binary" \
			: yas::is_text_archive<OA>::value ? "text" \
				: yas::is_json_archive<OA>::value ? "json" \
			: "unknown" \
		 ) \
		,(yas::is_mem_archive<OA>::value?"mem":"file") \
		,#testname \
		,(testname ## _test<concrete_archive_traits<yas::is_mem_archive<OA>::value,OA,IA>>( \
			(yas::is_binary_archive<OA>::value ? "binary" \
				: yas::is_text_archive<OA>::value ? "text" \
					: yas::is_json_archive<OA>::value ? "json" \
				: "unknown" \
			 ) \
			,(yas::is_mem_archive<OA>::value?"mem":"file") \
		)?(++passcnt,"passed"):(++failcnt,"failed!")) \
	)

template<typename OA, typename IA>
void tests(yas::uint32_t& p, yas::uint32_t& e) {
	YAS_RUN_TEST(version					, p, e);
	YAS_RUN_TEST(pod						, p, e);
	YAS_RUN_TEST(enum						, p, e);
	YAS_RUN_TEST(base_object			, p, e);
	YAS_RUN_TEST(auto_array				, p, e);
#if defined(YAS_HAS_BOOST_ARRAY) || defined(YAS_HAS_STD_ARRAY)
	YAS_RUN_TEST(array					, p, e);
#endif
	YAS_RUN_TEST(bitset					, p, e);
#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR) || defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
	YAS_RUN_TEST(buffer					, p, e);
#endif
	YAS_RUN_TEST(string					, p, e);
	YAS_RUN_TEST(wstring					, p, e);
	YAS_RUN_TEST(pair						, p, e);
#if defined(YAS_HAS_BOOST_TUPLE) || defined(YAS_HAS_STD_TUPLE)
	YAS_RUN_TEST(tuple					, p, e);
#endif
	YAS_RUN_TEST(vector					, p, e);
	YAS_RUN_TEST(list						, p, e);
#if defined(YAS_HAS_STD_FORWARD_LIST)
	YAS_RUN_TEST(forward_list			, p, e);
#endif
	YAS_RUN_TEST(map						, p, e);
	YAS_RUN_TEST(set						, p, e);
	YAS_RUN_TEST(multimap				, p, e);
	YAS_RUN_TEST(multiset				, p, e);
#if defined(YAS_HAS_BOOST_UNORDERED) || defined(YAS_HAS_STD_UNORDERED)
	YAS_RUN_TEST(unordered_map			, p, e);
	YAS_RUN_TEST(unordered_set			, p, e);
	YAS_RUN_TEST(unordered_multimap	, p, e);
	YAS_RUN_TEST(unordered_multiset	, p, e);
#endif
#if defined(YAS_HAS_BOOST_FUSION)
	YAS_RUN_TEST(fusion_pair			, p, e);
	YAS_RUN_TEST(fusion_tuple			, p, e);
	YAS_RUN_TEST(fusion_vector			, p, e);
	YAS_RUN_TEST(fusion_list			, p, e);
	YAS_RUN_TEST(fusion_set				, p, e);
	YAS_RUN_TEST(fusion_map				, p, e);
#endif
	YAS_RUN_TEST(one_function			, p, e);
	YAS_RUN_TEST(split_functions		, p, e);
	YAS_RUN_TEST(one_method				, p, e);
	YAS_RUN_TEST(split_methods			, p, e);
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	types_test();

	yas::uint32_t passed = 0;
	yas::uint32_t failed = 0;

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>(passed, failed);
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>(passed, failed);
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>(passed, failed);
	tests<yas::binary_file_oarchive, yas::binary_file_iarchive>(passed, failed);
	tests<yas::text_file_oarchive, yas::text_file_iarchive>(passed, failed);
	//tests<yas::json_file_oarchive, yas::json_file_iarchive>(passed, failed);

	std::cout << std::endl
	<< "/***************************************************/" << std::endl
	<< "> platform bits: " << (YAS_PLATFORM_BITS()) << std::endl
	<< "> passed tests : " << passed << std::endl
	<< "> failed tests : " << failed << std::endl
	<< "/***************************************************/" << std::endl;
}

/***************************************************************************/
