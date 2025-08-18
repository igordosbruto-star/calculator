CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
INCLUDES = -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=%.o)

all: libcore.a libcore.so

libcore.a: $(OBJ)
	ar rcs $@ $(OBJ)

libcore.so: $(OBJ)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) -o $@

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) libcore.a libcore.so
