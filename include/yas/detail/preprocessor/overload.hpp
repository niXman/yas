# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef YAS_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define YAS_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <yas/detail/preprocessor/config.hpp>
# include <yas/detail/preprocessor/cat.hpp>
# include <yas/detail/preprocessor/vsize.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if YAS_PP_VARIADICS
#    define YAS_PP_OVERLOAD(prefix, ...) YAS_PP_CAT(prefix, YAS_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif
