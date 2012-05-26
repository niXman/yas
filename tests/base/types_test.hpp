
#ifndef _yas__types_test_hpp__included_
#define _yas__types_test_hpp__included_

#include <yas/config/config.hpp>

/***************************************************************************/

void types_test() {
	static_assert(sizeof(yas::int8_t)==1, "bad yas::int8_t sizeof!");
	static_assert(sizeof(yas::uint8_t)==1, "bad yas::uint8_t sizeof!");
	static_assert(sizeof(yas::int16_t)==2, "bad yas::int16_t sizeof!");
	static_assert(sizeof(yas::uint16_t)==2, "bad yas::uint16_t sizeof!");
	static_assert(sizeof(yas::int32_t)==4, "bad yas::int32_t sizeof!");
	static_assert(sizeof(yas::uint32_t)==4, "bad yas::uint32_t sizeof!");
	static_assert(sizeof(yas::int64_t)==8, "bad yas::int64_t sizeof!");
	static_assert(sizeof(yas::uint64_t)==8, "bad yas::uint64_t sizeof!");
}

/***************************************************************************/

#endif // _yas__types_test_hpp__included_
