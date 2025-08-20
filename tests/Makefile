	CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST

CORE_DIR = ../core
CALC_DIR = ../DUKE

LIB_CORE = $(CORE_DIR)/libcore.a
LIB_CALC = $(CALC_DIR)/libduke.a

CALC_SRCS := $(wildcard duke/*.cpp)
CORE_SRCS := $(wildcard core/*.cpp)
FIN_SRCS := $(wildcard finance/*.cpp)
FIN_LIB_SRCS := $(wildcard ../src/finance/*.cpp)
DES_SRCS := $(wildcard designer/*.cpp)
PROD_LIB_SRCS := $(wildcard ../src/production/*.cpp)

.PHONY: all duke core finance designer clean
all: duke core finance designer

duke: $(LIB_CALC) $(LIB_CORE)
ifeq ($(strip $(CALC_SRCS)),)
	@echo "No DUKE tests"
else
	$(CXX) $(CXXFLAGS) -include duke/namespace.h \
		$(CALC_SRCS) -I$(CALC_DIR)/include -I../include -I../third_party -I$(CORE_DIR)/include \
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

finance:
ifeq ($(strip $(FIN_SRCS)),)
	@echo "No finance tests"
else
	$(CXX) $(CXXFLAGS) $(FIN_SRCS) $(FIN_LIB_SRCS) -I../include -I../third_party -I../core/include -o finance/run_tests
	./finance/run_tests
endif

designer:
ifeq ($(strip $(DES_SRCS)),)
	@echo "No designer tests"
else
	$(CXX) $(CXXFLAGS) $(DES_SRCS) ../apps/designer/DesignerApp.cpp $(PROD_LIB_SRCS) \
	-I../apps/designer -I../include -I../third_party -o designer/run_tests
	./designer/run_tests
endif

$(LIB_CALC):
	$(MAKE) -C $(CALC_DIR) libduke.a

$(LIB_CORE):
	$(MAKE) -C $(CORE_DIR) libcore.a

clean:
	rm -f duke/run_tests core/run_tests finance/run_tests designer/run_tests
