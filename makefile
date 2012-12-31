
.PHONY: all clean

PREFIX ?= /usr/local

CXX ?= g++
MOC ?= `pkg-config QtCore --variable=moc_location`

CXXFLAGS ?= -I . -g -O3 -ffast-math -mtune=native -Wall -fPIC `pkg-config --cflags QtCore QtDBus jack`
CFLAGS ?= $(CXXFLAGS)

LDFLAGS ?= `pkg-config --libs QtCore QtDBus jack` -lboost_program_options  -Wl,-rpath=$(PREFIX)/lib

all: nqms

nqms: main.cc module.h state.h ladspa_module.h engine.h makefile ringbuffer.h
	$(CXX) $(CXXFLAGS) -o nqms main.cc $(LDFLAGS)

