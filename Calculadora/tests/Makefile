CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST -include namespace.h
CORE_DIR = ../../core
INCLUDES = -I../include -I../third_party -I$(CORE_DIR)/include

CORE_LIB = $(CORE_DIR)/libcore.a
LIB = ../libcalculadora.a

TEST_SRCS = $(wildcard *.cpp)

run_tests: $(TEST_SRCS) $(LIB) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) $(INCLUDES) $(LIB) $(CORE_LIB) -o run_tests

$(LIB):
	$(MAKE) -C .. libcalculadora.a

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean
clean:
	rm -f run_tests
