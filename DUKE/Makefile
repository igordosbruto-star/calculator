CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
CORE_DIR = ../core
INCLUDES = -Iinclude -Ithird_party -I$(CORE_DIR)/include

CORE_LIB = $(CORE_DIR)/libcore.a

SRC := $(wildcard src/*.cpp) $(wildcard src/cli/*.cpp) \
       $(wildcard src/domain/*.cpp) $(wildcard src/custo/*.cpp) \
       $(wildcard src/ui/*.cpp)
LIB_SRC := $(filter-out src/main.cpp,$(SRC))
OBJ := $(LIB_SRC:.cpp=.o)

all: libcalculadora.a libcalculadora.so

libcalculadora.a: $(OBJ) $(CORE_LIB)
	ar rcs $@ $(OBJ)

libcalculadora.so: $(OBJ) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) -L$(CORE_DIR) -lcore -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

cli: libcalculadora.a $(CORE_LIB) src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp $(INCLUDES) -L. -lcalculadora -L$(CORE_DIR) -lcore -o app

tests: libcalculadora.a $(CORE_LIB)
	$(MAKE) -C tests run_tests

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean cli tests
clean:
	rm -f $(OBJ) libcalculadora.a libcalculadora.so app
	$(MAKE) -C tests clean
