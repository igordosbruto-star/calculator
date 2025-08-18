CXX = g++
CXXFLAGS = -std=c++17 -Wall
CORE_DIR = ../core
INCLUDES = -Iinclude -Ithird_party -I$(CORE_DIR)/include

CORE_LIB = $(CORE_DIR)/libcore.a

SRC := $(wildcard src/*.cpp) $(wildcard src/cli/*.cpp) $(wildcard src/domain/*.cpp) $(wildcard src/custo/*.cpp) $(wildcard src/ui/*.cpp)

app: $(SRC) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) -L$(CORE_DIR) -lcore -o $@

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean
clean:
	rm -f app
