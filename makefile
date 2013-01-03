
.PHONY: all clean

PREFIX ?= /usr/local

CXX ?= g++

CXXFLAGS ?= -I . -g -ffast-math -mtune=native -Wall -fPIC `pkg-config --cflags jack ladspamm-0`
CFLAGS ?= $(CXXFLAGS)

LDFLAGS ?= -ldl `pkg-config --libs jack ladspamm-0` -lboost_program_options -lboost_filesystem -lboost_system -lboost_regex -lreadline -Wl,-rpath=$(PREFIX)/lib

all: nqms

nqms: main.cc module.h ladspa_module.h engine.h makefile ringbuffer.h assign.h disposable.h 
	$(CXX) $(CXXFLAGS) -o nqms main.cc $(LDFLAGS)

