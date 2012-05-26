YAS
===

Yet Another Serialization

===
YAS is created as a replacement of boost.serialization because of its insufficient speed of serialization.
Increase speed of the YAS serialization compared with boost.serialization is:
 - ~2...3 times in release mode
 - ~6...7 times in debug mode

===
Currently only a binary serialization implemented.

===
Planned the support for the following types of archives:
 - binary
 - text (currently not implemented)(-)
 - json (-)

===
Planned the support for the following compilers:
 - GCC
 - Clang
 - Intel
 - MSVC

Currently only GCC-4.6.3 x32/x64 tested.

===
Planned the support for the following serializable types:
 - all built-in types
 - std::array
 - std::bitset
 - std::string
 - std::wstring
 - std::pair
 - std::tuple
 - std::vector
 - std::list
 - std::forward_list
 - std::map
 - std::multimap
 - std::set
 - std::multiset
 - std::unordered_map
 - std::unordered_multimap
 - std::unordered_set
 - std::unordered_multiset
 - boost::array
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

Currently supports all types except Qt types.

===
