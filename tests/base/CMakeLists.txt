cmake_minimum_required(VERSION 3.2)
project(yas-base-test)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
    include_directories("/home/nixman/boost-1.66.0-gcc-7.2/include")
    add_definitions(
        -DBOOST_ERROR_CODE_HEADER_ONLY
        -DBOOST_CHRONO_HEADER_ONLY
        -DYAS_SERIALIZE_BOOST_TYPES
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
#    include_directories("/home/nixman/boost-1.66.0-gcc-7.2/include")
    add_definitions(
        -DBOOST_ERROR_CODE_HEADER_ONLY
        -DBOOST_CHRONO_HEADER_ONLY
        -DYAS_SERIALIZE_BOOST_TYPES
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /d1parsePackExpressions-  /bigobj")
    include_directories("C:/Libraries/boost_1_66_0")
    add_definitions(
        -DBOOST_ERROR_CODE_HEADER_ONLY
        -DBOOST_CHRONO_HEADER_ONLY
        -DYAS_SERIALIZE_BOOST_TYPES
        -D_CRT_SECURE_NO_WARNINGS
    )
    link_directories("C:\Libraries\boost_1_64_0\lib32-msvc-14.1")
endif()

include_directories(
    ../../include
)

set(SOURCE_FILES
    include/array.hpp
    include/auto_array.hpp
    include/base64.hpp
    include/base_object.hpp
    include/bitset.hpp
    include/boost_cont_deque.hpp
    include/boost_cont_flat_map.hpp
    include/boost_cont_flat_multimap.hpp
    include/boost_cont_flat_multiset.hpp
    include/boost_cont_flat_set.hpp
    include/boost_cont_list.hpp
    include/boost_cont_map.hpp
    include/boost_cont_multimap.hpp
    include/boost_cont_multiset.hpp
    include/boost_cont_set.hpp
    include/boost_cont_slist.hpp
    include/boost_cont_stable_vector.hpp
    include/boost_cont_static_vector.hpp
    include/boost_cont_string.hpp
    include/boost_cont_vector.hpp
    include/boost_cont_wstring.hpp
    include/boost_fusion_list.hpp
    include/boost_fusion_map.hpp
    include/boost_fusion_pair.hpp
    include/boost_fusion_set.hpp
    include/boost_fusion_tuple.hpp
    include/boost_fusion_vector.hpp
    include/boost_tuple.hpp
    include/boost_variant.hpp
    include/buffer.hpp
    include/chrono.hpp
    include/complex.hpp
    include/deque.hpp
    include/endian.hpp
    include/enum.hpp
    include/forward_list.hpp
    include/fundamental.hpp
    include/header.hpp
    include/json_conformance.hpp
    include/list.hpp
    include/map.hpp
    include/multimap.hpp
    include/multiset.hpp
    include/one_func.hpp
    include/one_memfn.hpp
    include/optional.hpp
    include/pair.hpp
    include/serialize.hpp
    include/serialization.hpp
    include/set.hpp
    include/split_func.hpp
    include/split_memfn.hpp
    include/std_streams.hpp
    include/string.hpp
    include/tuple.hpp
    include/unordered_map.hpp
    include/unordered_multimap.hpp
    include/unordered_multiset.hpp
    include/unordered_set.hpp
    include/vector.hpp
    include/version.hpp
    include/wstring.hpp
    include/yas_object.hpp
    main.cpp
)

add_executable(yas-base-test ${SOURCE_FILES})
