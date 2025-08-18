CXX = g++
CXXFLAGS = -std=c++17 -Wall
INCLUDES = -Iinclude -Ithird_party

SRC := $(wildcard src/*.cpp) $(wildcard src/domain/*.cpp) $(wildcard src/custo/*.cpp)

app: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) -o $@

.PHONY: clean
clean:
	rm -f app
