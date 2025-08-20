CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
CORE_DIR = ../../core
INCLUDES = -I../../include -I../../include/duke -I../../third_party/nlohmann -I$(CORE_DIR)/include
WX_CXXFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)
CXXFLAGS += $(WX_CXXFLAGS)

CORE_LIB = $(CORE_DIR)/libcore.a

CLI_SRC := cli/app.cpp cli/args.cpp cli/parser.cpp cli/utils.cpp cli/commands.cpp cli/processor.cpp
FIN_SRC := $(wildcard ../finance/*.cpp)
GUI_MAIN := gui/main_wx.cpp
GUI_SRC := gui/Navigation.cpp
SRC := $(wildcard *.cpp) $(CLI_SRC) \
$(wildcard domain/*.cpp) $(wildcard custo/*.cpp) \
$(wildcard ui/*.cpp) $(FIN_SRC)
LIB_SRC := $(filter-out main.cpp,$(SRC)) $(GUI_SRC)
OBJ := $(LIB_SRC:.cpp=.o)

GUI_OBJ := $(GUI_SRC:.cpp=.o)
GUI_MAIN_OBJ := $(GUI_MAIN:.cpp=.o)

all: libduke.a libduke.so

libduke.a: $(OBJ) $(CORE_LIB)
	ar rcs $@ $(OBJ)

libduke.so: $(OBJ) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -shared $(OBJ) $(WX_LIBS) -L$(CORE_DIR) -lcore -o $@

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

cli: libduke.a $(CORE_LIB) main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(WX_LIBS) -o app

gui: libduke.a $(CORE_LIB) $(GUI_OBJ) $(GUI_MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(GUI_OBJ) $(GUI_MAIN_OBJ) $(INCLUDES) -L. -lduke -L$(CORE_DIR) -lcore $(WX_LIBS) -o app_gui

.PHONY: clean cli gui
clean:
	        rm -f $(OBJ) $(GUI_OBJ) $(GUI_MAIN_OBJ) libduke.a libduke.so app app_gui

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)
