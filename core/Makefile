CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
INCLUDES = -Iinclude -I../include -I../third_party/nlohmann
WX_CXXFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)
CXXFLAGS += $(WX_CXXFLAGS)
XML_LIBS := $(shell pkg-config --libs tinyxml2 2>/dev/null || echo -ltinyxml2)

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=%.o)

all: libcore.a libcore.so

libcore.a: $(OBJ)
	ar rcs $@ $(OBJ)

libcore.so: $(OBJ)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(WX_LIBS) $(XML_LIBS) -o $@

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) libcore.a libcore.so
