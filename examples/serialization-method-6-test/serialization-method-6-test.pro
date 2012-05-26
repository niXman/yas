TEMPLATE = app
CONFIG += console
CONFIG -= qt app_bundle

QMAKE_CXXFLAGS += \
	-std=c++0x

INCLUDEPATH += \
	../../include \

SOURCES += \
	main.cpp
