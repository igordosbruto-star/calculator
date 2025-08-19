CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
CORE_DIR = ../core
INCLUDES = -Iinclude -I../include -I../third_party -I$(CORE_DIR)/include
QT_CFLAGS := $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS := $(shell pkg-config --libs Qt6Widgets)
CXXFLAGS += $(QT_CFLAGS)

CORE_LIB = $(CORE_DIR)/libcore.a

CLI_SRC := src/cli/app.cpp src/cli/args.cpp src/cli/parser.cpp src/cli/utils.cpp src/cli/commands.cpp
FIN_SRC := $(wildcard ../src/finance/*.cpp)
SRC := $(wildcard src/*.cpp) $(CLI_SRC) \
       $(wildcard src/domain/*.cpp) $(wildcard src/custo/*.cpp) \
       $(wildcard src/ui/*.cpp) $(FIN_SRC)
LIB_SRC := $(filter-out src/main.cpp,$(SRC))
OBJ := $(LIB_SRC:.cpp=.o)

all: libduke.a libduke.so

libduke.a: $(OBJ) $(CORE_LIB)
	ar rcs $@ $(OBJ)

libduke.so: $(OBJ) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(QT_LIBS) -L$(CORE_DIR) -lcore -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

cli: libduke.a $(CORE_LIB) src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(QT_LIBS) -o app

tests: libduke.a $(CORE_LIB)
	$(MAKE) -C tests run_tests

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean cli tests
clean:
	rm -f $(OBJ) libduke.a libduke.so app
	$(MAKE) -C tests clean
