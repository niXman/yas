QT -= core gui
TARGET = yas-base-test
CONFIG += console
CONFIG -= app_bundle qt
TEMPLATE = app

DEFINES += \
	YAS_SERIALIZE_BOOST_TYPES=1 \
	YAS_SHARED_BUFFER_USE_STD_SHARED_PTR=1 \
	YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR=1 \
	YAS_HAS_BOOST_TUPLE=1 \
	YAS_HAS_STD_TUPLE=1 \
	YAS_HAS_STD_FORWARD_LIST=1 \
	YAS_HAS_BOOST_FUSION=1 \
	YAS_HAS_STD_ARRAY=1 \
	YAS_HAS_BOOST_ARRAY=1

#QMAKE_CXX = clang++

QMAKE_CXXFLAGS += \
	-std=c++0x

INCLUDEPATH += \
	../../../include \

SOURCES += \
	../main.cpp

HEADERS += \
	 ../include/wstring.hpp \
	 ../include/version.hpp \
	 ../include/vector.hpp \
	 ../include/unordered_set.hpp \
	 ../include/unordered_multiset.hpp \
	 ../include/unordered_multimap.hpp \
	 ../include/unordered_map.hpp \
	 ../include/types.hpp \
	 ../include/tuple.hpp \
	 ../include/string.hpp \
	 ../include/split_methods.hpp \
	 ../include/split_functions.hpp \
	 ../include/set.hpp \
	 ../include/pod.hpp \
	 ../include/pair.hpp \
	 ../include/one_method.hpp \
	 ../include/one_function.hpp \
	 ../include/multiset.hpp \
	 ../include/multimap.hpp \
	 ../include/map.hpp \
	 ../include/list.hpp \
	 ../include/fusion_vector.hpp \
	 ../include/fusion_tuple.hpp \
	 ../include/fusion_set.hpp \
	 ../include/fusion_pair.hpp \
	 ../include/fusion_map.hpp \
	 ../include/fusion_list.hpp \
	 ../include/forward_list.hpp \
	 ../include/enum.hpp \
	 ../include/buffer.hpp \
	 ../include/bitset.hpp \
	 ../include/base_object.hpp \
	 ../include/auto_array.hpp \
	 ../include/array.hpp
