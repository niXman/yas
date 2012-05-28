
#ifndef _yas__static_assert_hpp__included_
#define _yas__static_assert_hpp__included_

#include <yas/config/config.hpp>

namespace yas{
namespace detail {

#if defined(YAS_HAS_STATIC_ASSERT)

#define YAS_STATIC_ASSERT(cond, message) \
	static_assert((cond), # message)

#else

#define YAS_STATIC_ASSERT(cond, message) \
	typedef char __STATIC_ASSERT___##message##__[(cond)?1:-1]

#endif // defined(YAS_HAS_STATIC_ASSERT)

} // namespace detail
} // namespace yas

#endif // _yas__static_assert_hpp__included_
