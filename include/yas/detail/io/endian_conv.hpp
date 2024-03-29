
// Copyright (c) 2010-2023 niXman (github dot nixman at pm dot me). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__detail__io__endian_conv_hpp
#define __yas__detail__io__endian_conv_hpp

#include <yas/detail/config/config.hpp>
#include <yas/detail/type_traits/type_traits.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

template<typename T>
struct storage_type {
	enum {
		 is_float  = std::is_same<T, float>::value
		,is_double = std::is_same<T, double>::value
	};
	static_assert(is_float||is_double, "only double or float types is allowed");

	using type = typename std::conditional<
		 is_float
		,std::uint32_t
		,std::uint64_t
	>::type;
};

struct endian_converter {
	template<typename T>
	static T bswap(const T &v, __YAS_ENABLE_IF_IS_16BIT(T))
	{ return __YAS_NETWORK_TO_LOCAL16(v); }
	template<typename T>
	static T bswap(const T &v, __YAS_ENABLE_IF_IS_32BIT(T))
	{ return __YAS_NETWORK_TO_LOCAL32(v); }
	template<typename T>
	static T bswap(const T &v, __YAS_ENABLE_IF_IS_64BIT(T))
	{ return __YAS_NETWORK_TO_LOCAL64(v); }

	template<typename T>
	static typename storage_type<T>::type
	to_network(const T &v, __YAS_ENABLE_IF_IS_ANY_OF(T, float, double)) {
		union {
			typename storage_type<T>::type u;
			T v;
		} u;
		u.v = v;

		return bswap(u.u);
	}

	template<typename T>
	static T
	from_network(const typename storage_type<T>::type &v, __YAS_ENABLE_IF_IS_ANY_OF(T, float, double)) {
		union {
			typename storage_type<T>::type u;
			T v;
		} u;
		u.u = v;

		u.u = bswap(u.u);

		return u.v;
	}
};

/***************************************************************************/

} // ns detail
} // ns yas

#endif // __yas__detail__io__endian_conv_hpp
