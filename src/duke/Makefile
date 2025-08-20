CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
CORE_DIR = ../../core
INCLUDES = -I../../include -I../../include/duke -I../../third_party/nlohmann -I$(CORE_DIR)/include
QT_CFLAGS := $(shell pkg-config --cflags Qt6Widgets 2>/dev/null)
QT_LIBS := $(shell pkg-config --libs Qt6Widgets 2>/dev/null)
CXXFLAGS += $(QT_CFLAGS)

CORE_LIB = $(CORE_DIR)/libcore.a

CLI_SRC := cli/app.cpp cli/args.cpp cli/parser.cpp cli/utils.cpp cli/commands.cpp
FIN_SRC := $(wildcard ../finance/*.cpp)
SRC := $(wildcard *.cpp) $(CLI_SRC)        $(wildcard domain/*.cpp) $(wildcard custo/*.cpp)        $(wildcard ui/*.cpp) $(FIN_SRC)
LIB_SRC := $(filter-out main.cpp,$(SRC))
OBJ := $(LIB_SRC:.cpp=.o)

all: libduke.a libduke.so

libduke.a: $(OBJ) $(CORE_LIB)
	ar rcs $@ $(OBJ)

libduke.so: $(OBJ) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(QT_LIBS) -L$(CORE_DIR) -lcore -o $@

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

cli: libduke.a $(CORE_LIB) main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(QT_LIBS) -o app

.PHONY: clean cli
clean:
	rm -f $(OBJ) libduke.a libduke.so app

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)
