
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
void tests(yas::uint32_t iterations, std::vector<std::string>& reports) {
	static const char* archive_type =
	yas::is_binary_archive<OA>::value ? "binary:"
		: yas::is_text_archive<OA>::value ? "text  :"
			: yas::is_json_archive<OA>::value ? "json  :"
				: "unknown:"
	;

	reports.push_back(one_function_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(split_functions_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(one_method_speed_test<OA, IA>(iterations, archive_type));
	reports.push_back(split_methods_speed_test<OA, IA>(iterations, archive_type));
}

/***************************************************************************/

int main() {
	setvbuf(stdout, 0, _IONBF, 0);

	yas::uint32_t iterations = 1024*1024*10;
	std::vector<std::string> reports;

	tests<yas::binary_mem_oarchive, yas::binary_mem_iarchive>(iterations, reports);
	tests<yas::text_mem_oarchive, yas::text_mem_iarchive>(iterations, reports);
	//tests<yas::json_mem_oarchive, yas::json_mem_iarchive>(iterations, reports);

	std::vector<std::string>::const_iterator it = reports.begin();
	for ( ; it != reports.end(); ++it ) {
		std::cout << *it << std::endl;
	}
}

/***************************************************************************/
