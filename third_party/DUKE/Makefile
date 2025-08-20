CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
CORE_DIR = ../../core
SRC_DIR = ../../src/duke
INCLUDES = -I../../include -I../../include/duke -I../../third_party -I$(CORE_DIR)/include
QT_CFLAGS := $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS := $(shell pkg-config --libs Qt6Widgets)
CXXFLAGS += $(QT_CFLAGS)

CORE_LIB = $(CORE_DIR)/libcore.a

CLI_SRC := $(SRC_DIR)/cli/app.cpp $(SRC_DIR)/cli/args.cpp $(SRC_DIR)/cli/parser.cpp $(SRC_DIR)/cli/utils.cpp $(SRC_DIR)/cli/commands.cpp
GUI_MAIN = $(SRC_DIR)/gui/main_qt.cpp
FIN_SRC := $(wildcard ../../src/finance/*.cpp)
SRC := $(wildcard $(SRC_DIR)/*.cpp) $(CLI_SRC) \
       $(wildcard $(SRC_DIR)/domain/*.cpp) $(wildcard $(SRC_DIR)/custo/*.cpp) \
       $(wildcard $(SRC_DIR)/ui/*.cpp) $(wildcard $(SRC_DIR)/gui/*.cpp) $(FIN_SRC)
LIB_SRC := $(filter-out $(SRC_DIR)/main.cpp $(GUI_MAIN),$(SRC))
OBJ := $(patsubst $(SRC_DIR)/%, out/%, $(LIB_SRC:.cpp=.o))

all: libduke.a libduke.so

libduke.a: $(OBJ) $(CORE_LIB)
	ar rcs $@ $(OBJ)

libduke.so: $(OBJ) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(QT_LIBS) -L$(CORE_DIR) -lcore -o $@

out/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

cli: libduke.a $(CORE_LIB) $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(QT_LIBS) -o app

gui: libduke.a $(CORE_LIB) $(GUI_MAIN)
	$(CXX) $(CXXFLAGS) $(GUI_MAIN) $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(QT_LIBS) -o app_gui

tests: libduke.a $(CORE_LIB)
	$(MAKE) -C tests run_tests

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean cli gui tests
clean:
	rm -f $(OBJ) libduke.a libduke.so app app_gui
	$(MAKE) -C tests clean
