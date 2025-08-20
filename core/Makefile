CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
INCLUDES = -Iinclude -I../include -I../third_party/nlohmann
QT_CFLAGS := $(shell pkg-config --cflags Qt6Core)
QT_LIBS := $(shell pkg-config --libs Qt6Core)
CXXFLAGS += $(QT_CFLAGS)
XML_LIBS := $(shell pkg-config --libs tinyxml2 2>/dev/null || echo -ltinyxml2)

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=%.o)

all: libcore.a libcore.so

libcore.a: $(OBJ)
	ar rcs $@ $(OBJ)

libcore.so: $(OBJ)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(QT_LIBS) $(XML_LIBS) -o $@

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) libcore.a libcore.so
