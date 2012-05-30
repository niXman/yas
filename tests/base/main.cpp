
#include <iostream>
#include <algorithm>
#include <cstdio>

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

#include "array.hpp"
#include "auto_array.hpp"
#include "bitset.hpp"
#include "buffer.hpp"
#include "enum.hpp"
#include "forward_list.hpp"
#include "fusion_list.hpp"
#include "fusion_map.hpp"
#include "fusion_pair.hpp"
#include "fusion_set.hpp"
#include "fusion_tuple.hpp"
#include "fusion_vector.hpp"
#include "list.hpp"
#include "map.hpp"
#include "multimap.hpp"
#include "multiset.hpp"
#include "pair.hpp"
#include "pod.hpp"
#include "set.hpp"
#include "string.hpp"
#include "tuple.hpp"
#include "types.hpp"
#include "unordered_map.hpp"
#include "unordered_multimap.hpp"
#include "unordered_multiset.hpp"
#include "unordered_set.hpp"
#include "vector.hpp"
#include "version.hpp"
#include "wstring.hpp"

#include "one_function.hpp"
#include "one_method.hpp"
#include "split_functions.hpp"
#include "split_methods.hpp"

#include "speed_one_function.hpp"
#include "speed_one_method.hpp"
#include "speed_split_functions.hpp"
#include "speed_split_methods.hpp"

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/


/***************************************************************************/

namespace _binary_size_test {

struct _binary_size_test_pod_type {
	_binary_size_test_pod_type() {}

	size_t x;
	size_t y;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned) {
		ar & x
			& y;
	}
	template<typename Archive>
	void serialize(Archive& ar) {
		ar & x
			& y;
	}
};

} // namespace size_test

#if defined(YAS_SERIALIZE_BOOST_TYPES)
#include <sstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

void _binary_boost_archive(const size_t iteration) {
	_binary_size_test::_binary_size_test_pod_type t;
	std::ostringstream os;
	boost::archive::binary_oarchive oa(os);
	for ( size_t idx = 0; idx < iteration; ++idx ) {
		t.x = t.y = idx;
		oa & t;
	}
}
#endif // defined(YAS_SERIALIZE_BOOST_TYPES)

template<typename OA, typename IA>
void _binary_yas_archive(const size_t iteration) {
	_binary_size_test::_binary_size_test_pod_type t;
	OA oa/*(new char[1024*1024*200], 1024*1024*200)*/;
	for ( size_t idx = 0; idx < iteration; ++idx ) {
		t.x = t.y = idx;
		oa & t;
	}
}

template<typename OA, typename IA>
bool speed_test() {
	const size_t count = 1024*1024*10;
	clock_t start = clock();
	clock_t boost_time=0, yas_time;

#if defined(YAS_SERIALIZE_BOOST_TYPES)
	_binary_boost_archive(count);
	std::cout << "boost time: " << (boost_time=(clock()-start)/(CLOCKS_PER_SEC/1000)) << " ms." << std::endl;
#endif
	start = clock();
	_binary_yas_archive<OA, IA>(count);
	std::cout << "yas time  : " << (yas_time=(clock()-start)/(CLOCKS_PER_SEC/1000)) << " ms." << std::endl;

	std::cout << "speed up  : " << (((double)boost_time)/((double)yas_time)) << std::endl;

	return true;
}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/

template<typename OA, typename IA>
bool tests() {
	static const char* test_type =
	yas::is_binary_archive<OA>::value ? "binary:"
		: yas::is_text_archive<OA>::value ? "text  :"
			: yas::is_json_archive<OA>::value ? "json  :"
				: "unknown:";

	static const char* passed = "passed";
	static const char* failed = "failed!";

	printf("%s VERSION            test %s\n", test_type, (version_test<OA, IA>()?passed:failed));
	printf("%s POD                test %s\n", test_type, (pod_test<OA, IA>()?passed:failed));
	printf("%s ENUM               test %s\n", test_type, (enum_test<OA, IA>()?passed:failed));
	printf("%s AUTO_ARRAY         test %s\n", test_type, (auto_array_test<OA, IA>()?passed:failed));
#if defined(YAS_HAS_BOOST_ARRAY) || defined(YAS_HAS_STD_ARRAY)
	printf("%s ARRAY              test %s\n", test_type, (array_test<OA, IA>()?passed:failed));
#endif
	printf("%s BITSET             test %s\n", test_type, (bitset_test<OA, IA>()?passed:failed));
#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR) || defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
	printf("%s BUFFER             test %s\n", test_type, (buffer_test<OA, IA>()?passed:failed));
#endif
	printf("%s STRING             test %s\n", test_type, (string_test<OA, IA>()?passed:failed));
	printf("%s WSTRING            test %s\n", test_type, (wstring_test<OA, IA>()?passed:failed));
	printf("%s PAIR               test %s\n", test_type, (pair_test<OA, IA>()?passed:failed));
#if defined(YAS_HAS_BOOST_TUPLE) || defined(YAS_HAS_STD_TUPLE)
	printf("%s TUPLE              test %s\n", test_type, (tuple_test<OA, IA>()?passed:failed));
#endif
	printf("%s VECTOR             test %s\n", test_type, (vector_test<OA, IA>()?passed:failed));
	printf("%s LIST               test %s\n", test_type, (list_test<OA, IA>()?passed:failed));
#if defined(YAS_HAS_STD_FORWARD_LIST)
	printf("%s FORWARD_LIST       test %s\n", test_type, (forward_list_test<OA, IA>()?passed:failed));
#endif
	printf("%s MAP                test %s\n", test_type, (map_test<OA, IA>()?passed:failed));
	printf("%s SET                test %s\n", test_type, (set_test<OA, IA>()?passed:failed));
	printf("%s MULTIMAP           test %s\n", test_type, (multimap_test<OA, IA>()?passed:failed));
	printf("%s MULTISET           test %s\n", test_type, (multiset_test<OA, IA>()?passed:failed));
#if defined(YAS_HAS_BOOST_UNORDERED) || defined(YAS_HAS_STD_UNORDERED)
	printf("%s UNORDERED_MAP      test %s\n", test_type, (unordered_map_test<OA, IA>()?passed:failed));
	printf("%s UNORDERED_SET      test %s\n", test_type, (unordered_set_test<OA, IA>()?passed:failed));
	printf("%s UNORDERED_MULTIMAP test %s\n", test_type, (unordered_multimap_test<OA, IA>()?passed:failed));
	printf("%s UNORDERED_MULTISET test %s\n", test_type, (unordered_multiset_test<OA, IA>()?passed:failed));
#endif
#if defined(YAS_HAS_BOOST_FUSION)
	printf("%s FUSION_PAIR        test %s\n", test_type, (fusion_pair_test<OA, IA>()?passed:failed));
	printf("%s FUSION_TUPLE       test %s\n", test_type, (fusion_tuple_test<OA, IA>()?passed:failed));
	printf("%s FUSION_VECTOR      test %s\n", test_type, (fusion_vector_test<OA, IA>()?passed:failed));
	printf("%s FUSION_LIST        test %s\n", test_type, (fusion_list_test<OA, IA>()?passed:failed));
//   printf("%s FUSION_SET         test %s\n", test_type, (fusion_set_test<OA, IA>()?passed:failed));
//   printf("%s FUSION_MAP         test %s\n", test_type, (fusion_map_test<OA, IA>()?passed:failed));
#endif
	printf("%s ONE_FUNCTION       test %s\n", test_type, (one_function_serializer_test<OA, IA>()?passed:failed));
	printf("%s SPLIT_FUNCTIONS    test %s\n", test_type, (split_functions_serializer_test<OA, IA>()?passed:failed));
	printf("%s ONE_METHOD         test %s\n", test_type, (one_method_serializer_test<OA, IA>()?passed:failed));
	printf("%s SPLIT_METHODS      test %s\n", test_type, (split_methods_serializer_test<OA, IA>()?passed:failed));

	one_function_speed_test<OA, IA>();
	split_functions_speed_test<OA, IA>();
	one_method_speed_test<OA, IA>();
	split_methods_speed_test<OA, IA>();

	return true;
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	types_test();

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>();
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>();
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>();
}

/***************************************************************************/
