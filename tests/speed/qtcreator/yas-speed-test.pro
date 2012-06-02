QT -= core gui
TARGET = yas-speed-test
CONFIG += console
CONFIG -= app_bundle qt
TEMPLATE = app

DEFINES += \
	YAS_SERIALIZE_BOOST_TYPES=1

#QMAKE_CXX = clang++

QMAKE_CXXFLAGS += \
	-std=c++0x

INCLUDEPATH += \
	../../../include \

LIBS += \
	-lboost_system \
	-lboost_serialization

SOURCES += \
	../main.cpp

HEADERS += \
	../include/speed_split_methods.hpp \
	../include/speed_split_functions.hpp \
	../include/speed_one_method.hpp \
	../include/speed_one_function.hpp
