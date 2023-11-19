src_dir := ./src
bin_dir := ./bin

SRC = $(wildcard $(src_dir)/*.cpp $(src_dir)/*/*.cpp)

CXX := g++
CXXFLAGS := -O3 
ALL_CXXFLAGS := $(CXXFLAGS) -shared -std=c++20

LDFLAGS := -L./dep/lib
LDLIBS := -lminhook

all:
	$(CXX) $(ALL_CXXFLAGS) -H $(SRC) $(LDFLAGS) $(LDLIBS) -I./dep/inc -o$(bin_dir)/bo1-debugger.dll

header:
	$(CXX) $(CXXFLAGS) -std=c++20 src/stdc++.hpp