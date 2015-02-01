YAS
===
Yet Another Serialization

===
YAS is created as a replacement of boost.serialization because of its insufficient speed of serialization.
Binary serialization:
       +-------------------+
       |  boost  |   YAS   |
+------+---------+---------+---------+
| save | 142 ms  | 24 ms   | +500%   |
+------+---------+---------+---------+
| load | 114 ms  | 8 ms    | +1300%  |
+------------------------------------+

Text serialization:
       +-------------------+
       |  boost  |   YAS   |
+------+---------+---------+---------+
| save | 8090 ms | 277 ms  | +28000% |
+------+---------+---------+---------+
| load | 8794 ms | 265 ms  | +33000% |
+------------------------------------+

Yas is header only library. You do not need to link it with your code.
Yas does not depend on third-party libraries or boost.
Yas require C++11 support.
Yas binary archives is endian independent.

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
 - qbitarray
 - qbytearray
 - qchar
 - qcolor
 - qdate
 - qdatetime
 - qhash
 - qlist
 - qmap
 - qmultihash
 - qmultimap
 - qpoint
 - qpointf
 - qpolygon
 - qpolygonf
 - qqueue
 - qrect
 - qrectf
 - qregion
 - qset
 - qsize
 - qsizef
 - qstack
 - qstring
 - qstringlist
 - qtime
 - qurl
 - quuid
 - qvariant
 - qvarianthash
 - qvariantlist
 - qvariantmap
 - qvector
 - qvector2d
 - qvector3d
 - qvector4d
 - yas::intrusive_buffer [1] (only save)
 - yas::shared_buffer [2]

Currently supports all types except Qt types.

===
If you use YAS in your project - please tell to the author with the short description of the reasons and advantages in comparison with other serialization libraries ;)

===
[1] https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L45
[2] https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L64
