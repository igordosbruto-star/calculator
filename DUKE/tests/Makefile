CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST
QT_CFLAGS := $(shell pkg-config --cflags Qt6Widgets Qt6Test)
QT_LIBS := $(shell pkg-config --libs Qt6Widgets Qt6Test)
CXXFLAGS += $(QT_CFLAGS)
MOC = /usr/lib/qt6/libexec/moc
CORE_DIR = ../../core
CALC_DIR = ..
LIB_CORE = $(CORE_DIR)/libcore.a
LIB_DUKE = $(CALC_DIR)/libduke.a

.RECIPEPREFIX = >

SRCS := $(filter-out gui_mainwindow.test.cpp moc_GuiBridge.cpp,$(wildcard *.cpp))

run_tests: $(SRCS) moc_GuiBridge.cpp $(LIB_DUKE) $(LIB_CORE) gui_mainwindow.test
>$(CXX) $(CXXFLAGS) $(SRCS) \
>    $(CALC_DIR)/src/gui/GuiBridge.cpp moc_GuiBridge.cpp \
>    -I$(CALC_DIR)/include -I$(CALC_DIR)/../include \
>    -I$(CALC_DIR)/../third_party -I$(CORE_DIR)/include \
>    $(LIB_DUKE) $(LIB_CORE) $(QT_LIBS) -o run_tests

gui_mainwindow.test: gui_mainwindow.test.cpp moc_GuiBridge.cpp $(LIB_CORE) $(LIB_DUKE)
>$(CXX) $(CXXFLAGS) gui_mainwindow.test.cpp \
>    $(CALC_DIR)/src/gui/MainWindow.cpp $(CALC_DIR)/src/gui/GuiBridge.cpp \
>    moc_GuiBridge.cpp \
>    -I$(CALC_DIR)/include -I$(CALC_DIR)/../include \
>    -I$(CALC_DIR)/../third_party -I$(CORE_DIR)/include \
>    $(LIB_DUKE) $(LIB_CORE) $(QT_LIBS) -o gui_mainwindow.test

moc_GuiBridge.cpp: $(CALC_DIR)/include/gui/GuiBridge.h
>$(MOC) $< -o $@

$(LIB_DUKE):
>@true

$(LIB_CORE):
>@true

clean:
>rm -f run_tests gui_mainwindow.test moc_GuiBridge.cpp

.PHONY: run_tests clean
