CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lfreeimage -lpng -lz

ifeq ($(OS),Windows_NT)
	.EXE = .exe
else
	.EXE =
endif

CXX_SRCS = $(wildcard src/*.cpp)
CXX_OBJS = $(CXX_SRCS:src/%.cpp=build/%.o)

.PHONY: all clean

all: grit

grit: $(CXX_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(CXX_OBJS)
	rm -f grit$(EXE)
	rm -rf build