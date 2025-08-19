CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST
QT_CFLAGS := $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS := $(shell pkg-config --libs Qt6Widgets)
CXXFLAGS += $(QT_CFLAGS)
CORE_DIR = ../../core
CALC_DIR = ..
LIB_CORE = $(CORE_DIR)/libcore.a
LIB_DUKE = $(CALC_DIR)/libduke.a

SRCS := $(wildcard *.cpp)

run_tests: $(SRCS) $(LIB_DUKE) $(LIB_CORE)
	$(CXX) $(CXXFLAGS) $(SRCS) -I$(CALC_DIR)/include -I$(CALC_DIR)/../include -I$(CALC_DIR)/../third_party -I$(CORE_DIR)/include $(LIB_DUKE) $(LIB_CORE) $(QT_LIBS) -o run_tests

$(LIB_DUKE):
	$(MAKE) -C $(CALC_DIR) libduke.a

$(LIB_CORE):
	$(MAKE) -C $(CORE_DIR) libcore.a

clean:
	rm -f run_tests

.PHONY: run_tests clean
