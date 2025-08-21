CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
INCLUDES = -Iinclude -I../include -I../third_party/nlohmann -I../third_party/tinyxml2
WX_CXXFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)
CXXFLAGS += $(WX_CXXFLAGS)
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=%.o) tinyxml2.o

all: libcore.a libcore.so

libcore.a: $(OBJ)
	ar rcs $@ $(OBJ)

libcore.so: $(OBJ)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(WX_LIBS) -o $@

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

tinyxml2.o: ../third_party/tinyxml2/tinyxml2.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) libcore.a libcore.so
