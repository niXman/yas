[![Build Status](https://travis-ci.org/niXman/yas.svg?branch=master)](https://travis-ci.org/niXman/yas)

YAS
===
Yet Another Serialization

##### Graphical representations

###### Size

![Size](https://raw.githubusercontent.com/STEllAR-GROUP/cpp-serializers/c78526f97fb2e4ac9d000ca9d6a076561680c29f/images/size.png)

###### Time

![Time](https://raw.githubusercontent.com/STEllAR-GROUP/cpp-serializers/c78526f97fb2e4ac9d000ca9d6a076561680c29f/images/time.png)


===
* YAS is created as a replacement of boost.serialization because of its insufficient speed of serialization.
* YAS is header only library. You do not need to link it with your code.
* YAS does not depend on third-party libraries or boost.
* YAS require C++11 support.
* YAS binary archives is endian independent.

===
Supported the following types of archives:
 - binary
 - text
 - json (uncompleted)

===
Supported the following compilers:
 - GCC  : 4.8.0, 4.8.1, 4.8.2, ... - x32/x64
 - MinGW: 4.8.0, 4.8.1, 4.8.2, ... - x32/x64
 - Clang: 3.3, 3.4, ... - x32/x64
 - Intel: (untested)
 - MSVC : 2013, 2015, ... - x32/x64

===
Planned the support for the following serializable types:
 - all built-in types
 - enum`s and 'enum class'es
 - std::array
 - std::bitset
 - std::chrono::duration
 - std::chrono::time_point
 - std::complex
 - std::deque
 - std::forward_list
 - std::list
 - std::map
 - std::multimap
 - std::multiset
 - std::optional
 - std::pair
 - std::set
 - std::string
 - std::tuple
 - std::unordered_map
 - std::unordered_multimap
 - std::unordered_multiset
 - std::unordered_set
 - std::vector
 - std::wstring
 - boost::array
 - boost::chrono::duration
 - boost::chrono::time_point
 - boost::optional
 - boost::container::deque
 - boost::container::string
 - boost::container::wstring
 - boost::container::vector
 - boost::container::static_vector
 - boost::container::stable_vector
 - boost::container::list
 - boost::container::slist
 - boost::container::map
 - boost::container::multimap
 - boost::container::set
 - boost::container::multiset
 - boost::container::flat_map
 - boost::container::flat_multimap
 - boost::container::flat_set
 - boost::container::flat_multiset
 - boost::unordered_map
 - boost::unordered_multimap
 - boost::unordered_set
 - boost::unordered_multiset
 - boost::fusion::pair
 - boost::fusion::tuple
 - boost::fusion::vector
 - boost::fusion::list
 - boost::fusion::map
 - boost::fusion::set
 - [yas::intrusive_buffer](https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L48) (only save)
 - [yas::shared_buffer](https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L67)

===
Projects using this library
---------------------------

* [K3](https://github.com/DaMSL/K3): K3 is a programming language for building large-scale data systems
* [cppan](https://github.com/tarasko/cppan): Class members annotations for C++
