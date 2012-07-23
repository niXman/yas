
#include <iostream>
#include <ctime>

#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/text_iarchive.hpp>
#include <yas/text_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/json_oarchive.hpp>

#include <yas/serializers/std_types_serializers.hpp>

#include "include/speed_one_function.hpp"
#include "include/speed_one_method.hpp"
#include "include/speed_split_functions.hpp"
#include "include/speed_split_methods.hpp"

/***************************************************************************/

template<typename OA, typename IA>
void tests(yas::uint32_t iterations) {
	static const char* archive_type =
	yas::is_binary_archive<OA>::value ? "binary:"
		: yas::is_text_archive<OA>::value ? "text  :"
			: yas::is_json_archive<OA>::value ? "json  :"
				: "unknown:"
	;

	std::cout << one_function_speed_test<OA, IA>(iterations, archive_type) << std::endl;
	std::cout << split_functions_speed_test<OA, IA>(iterations, archive_type) << std::endl;
	std::cout << one_method_speed_test<OA, IA>(iterations, archive_type) << std::endl;
	std::cout << split_methods_speed_test<OA, IA>(iterations, archive_type) << std::endl;
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	yas::uint32_t iterations = 1024*1024*10;

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>(iterations);
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>(iterations);
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>(iterations);
}

/***************************************************************************/
