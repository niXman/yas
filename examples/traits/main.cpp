
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

#include <yas/serialize.hpp>

#undef NDEBUG
#include <cassert>

/***************************************************************************/

struct my_traits {
    static std::size_t itoa(char *buf, const std::size_t bufsize, std::int32_t v) {
        return std::snprintf(buf, bufsize, "%d", v);
    }
};

struct my_traits2 {
    template<typename T>
    static T atoi(const char *str, std::size_t) {
        return static_cast<T>(std::strtol(str, 0, 10));
    }
};

/***************************************************************************/

int main() {
    std::int32_t src = 33, dst = 0;
    constexpr std::size_t flags = yas::mem|yas::json;

    auto buf = yas::save<flags>(YAS_OBJECT_NVP("object", ("v", src)));

    yas::load<flags>(buf, YAS_OBJECT_NVP("object", ("v", dst)));

    assert(src == dst);
}

/***************************************************************************/
