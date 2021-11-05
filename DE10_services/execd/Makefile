CXX = g++
#CXXFLAGS = -Wall
CXXFLAGS = -Wall -std=c++11

all: execd

execd: execd.cpp config_file.h
	$(CXX) execd.cpp -o execd $(CXXFLAGS)

clean:
	rm -f test
 
