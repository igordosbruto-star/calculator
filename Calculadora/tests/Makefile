CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST
INCLUDES = -I../include -I../third_party

TEST_SRCS = $(wildcard *.cpp)
SRC_FILES = ../src/Material.cpp ../src/Corte.cpp ../src/cli.cpp \
            ../src/plano_corte.cpp ../src/persist.cpp \
            ../src/domain/MaterialUnitario.cpp \
            ../src/domain/MaterialLinear.cpp \
            ../src/domain/MaterialCubico.cpp

run_tests: $(TEST_SRCS) $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) $(SRC_FILES) $(INCLUDES) -o run_tests

.PHONY: clean
clean:
	rm -f run_tests
