
#include <iostream>
#include <cstdio>

#include <yas/serializers/std_types_serializers.hpp>
#include <yas/serializers/boost_types_serializers.hpp>
#include <yas/serializers/qt_types_serializers.hpp>

#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>

#include "types_test.hpp"
#include "binary_test.hpp"
//#include "text_test.hpp"
//#include "json_test.hpp"

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	types_test();
	binary_tests();
	//text_tests();
	//json_tests();
}

/***************************************************************************/
