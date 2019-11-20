CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror `pkg-config --cflags libndn-cxx` -DBOOST_LOG_DYN_LINK
LIBS = `pkg-config --libs libndn-cxx`
DESTDIR ?= /usr/local

PROGRAMS = producer consumer

all: $(PROGRAMS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(PROGRAMS) tap-tunnel

install: all
	sh -c 'for P in $(PROGRAMS); do cp $$P $(DESTDIR)/bin/ndn6-$$P; done'

uninstall:
	sh -c 'for P in $(PROGRAMS); do rm -f $(DESTDIR)/bin/ndn6-$$P; done'
