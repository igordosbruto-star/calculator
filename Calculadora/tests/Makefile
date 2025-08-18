CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST -include namespace.h
CORE_DIR = ../../core
INCLUDES = -I../include -I../third_party -I$(CORE_DIR)/include

CORE_LIB = $(CORE_DIR)/libcore.a

TEST_SRCS = $(wildcard *.cpp)
SRC_FILES = ../src/Material.cpp ../src/Corte.cpp ../src/cli/args.cpp \
            ../src/cli/app.cpp ../src/core.cpp \
            ../src/plano_corte.cpp ../src/persist.cpp \
            ../src/persist_projeto.cpp \
            ../src/persist_tempo.cpp \
            ../src/domain/MaterialUnitario.cpp \
            ../src/domain/MaterialLinear.cpp \
            ../src/domain/MaterialCubico.cpp \
            ../src/domain/MaterialFactory.cpp \
            ../src/domain/Projeto.cpp \
            ../src/domain/Tempo.cpp \
            ../src/custo/EstimadorCusto.cpp \
            ../src/ui/Menu.cpp

run_tests: $(TEST_SRCS) $(SRC_FILES) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) $(SRC_FILES) $(INCLUDES) -L$(CORE_DIR) -lcore -o run_tests

$(CORE_LIB):
	$(MAKE) -C $(CORE_DIR)

.PHONY: clean
clean:
	rm -f run_tests
