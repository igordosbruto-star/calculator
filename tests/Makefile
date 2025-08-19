CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST

CORE_DIR = ../core
CALC_DIR = ../DUKE

LIB_CORE = $(CORE_DIR)/libcore.a
LIB_CALC = $(CALC_DIR)/libduke.a

CALC_SRCS := $(wildcard duke/*.cpp)
CORE_SRCS := $(wildcard core/*.cpp)

.PHONY: all duke core clean

all: duke core

duke: $(LIB_CALC) $(LIB_CORE)
ifeq ($(strip $(CALC_SRCS)),)
        @echo "No DUKE tests"
else
	$(CXX) $(CXXFLAGS) -include duke/namespace.h \
		$(CALC_SRCS) -I$(CALC_DIR)/include -I$(CALC_DIR)/third_party -I$(CORE_DIR)/include \
		$(LIB_CALC) $(LIB_CORE) -o duke/run_tests
	./duke/run_tests
endif

core: $(LIB_CORE)
ifeq ($(strip $(CORE_SRCS)),)
	@echo "No core tests"
else
	$(CXX) $(CXXFLAGS) $(CORE_SRCS) -I$(CORE_DIR)/include \
		$(LIB_CORE) -o core/run_tests
	./core/run_tests
endif

$(LIB_CALC):
	$(MAKE) -C $(CALC_DIR) libduke.a

$(LIB_CORE):
	$(MAKE) -C $(CORE_DIR) libcore.a

clean:
	rm -f duke/run_tests core/run_tests
