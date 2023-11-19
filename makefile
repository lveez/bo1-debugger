src_dir := $(CURDIR)/src
bin_dir := $(CURDIR)/bin

SRC = $(wildcard $(src_dir)/*.cpp $(src_dir)/*/*.cpp)

CXX := g++
CXXFLAGS := -O3 
ALL_CXXFLAGS := $(CXXFLAGS) -shared -std=c++20

LDFLAGS := -L./dep/lib
LDLIBS := -lminhook

all:
	$(CXX) $(ALL_CXXFLAGS) $(SRC) $(LDFLAGS) $(LDLIBS) -I./dep/inc -o$(bin_dir)/bo1-debugger.dll
