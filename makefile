
.PHONY: all clean

PREFIX ?= /usr/local

CXX ?= g++
MOC ?= `pkg-config QtCore --variable=moc_location`

CXXFLAGS ?= -I . -g -ffast-math -mtune=native -Wall -fPIC `pkg-config --cflags QtCore QtDBus jack`
CFLAGS ?= $(CXXFLAGS)

LDFLAGS ?= -ldl `pkg-config --libs QtCore QtDBus jack` -lboost_program_options -lboost_filesystem -lboost_system -lboost_regex -Wl,-rpath=$(PREFIX)/lib

all: nqms

nqms: main.cc module.h ladspa_module.h engine.h makefile ringbuffer.h assign.h disposable.h ladspa_plugin.h ladspa_library.h ladspapp.h library.h ladspa_plugin_instance.h ladspa_world.h
	$(CXX) $(CXXFLAGS) -o nqms main.cc $(LDFLAGS)

