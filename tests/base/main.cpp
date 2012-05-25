
#include <iostream>
#include <cstdio>

#include <yas/serializers/std_types_serializers.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>

#include "binary_test.hpp"
//#include "text_test.hpp"
//#include "json_test.hpp"

/***************************************************************************/

struct type1 {
	std::string str;

	template<typename archive_type>
	void serialize(archive_type& ar) {
		ar & str;
	}
};

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	type1 t1;
	yas::binary_mem_oarchive oa;
	oa & t1;

	binary_tests();
	//text_tests();
	//json_tests();
}

/***************************************************************************/
