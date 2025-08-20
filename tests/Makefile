CXX = g++
CXXFLAGS = -std=c++17 -Wall -DUNIT_TEST

CORE_DIR = ../core
CALC_DIR = ../src/duke

LIB_CORE = $(CORE_DIR)/libcore.a
LIB_CALC = $(CALC_DIR)/libduke.a

CALC_SRCS := $(wildcard duke/*.cpp)
CORE_SRCS := $(wildcard core/*.cpp)
FIN_SRCS := $(wildcard finance/*.cpp)
FIN_LIB_SRCS := $(wildcard ../src/finance/*.cpp)

DES_SRCS := $(wildcard designer/*.cpp)
PROD_LIB_SRCS := $(wildcard ../src/production/*.cpp)

ADMIN_SRCS := $(wildcard admin/*.cpp)
ADMIN_APP_SRCS := ../apps/admin/AdminApp.cpp
PROD_SRCS := $(wildcard production/*.cpp)
PROD_APP_SRCS := ../apps/production/ProductionApp.cpp ../src/production/ModeloProducao.cpp
SALES_SRCS := $(wildcard sales/*.cpp)

.PHONY: all duke core finance designer admin production sales clean
all: duke core finance admin designer production sales

duke: $(LIB_CALC) $(LIB_CORE)
ifeq ($(strip $(CALC_SRCS)),)
        @echo "No DUKE tests"
else
	$(CXX) $(CXXFLAGS) -include duke/namespace.h $(CALC_SRCS) -I../include -I../include/duke -I../third_party -I$(CORE_DIR)/include $(LIB_CALC) $(LIB_CORE) -o duke/run_tests
	./duke/run_tests
endif

core: $(LIB_CORE)
ifeq ($(strip $(CORE_SRCS)),)
	@echo "No core tests"
else
	$(CXX) $(CXXFLAGS) $(CORE_SRCS) -I$(CORE_DIR)/include -I../third_party $(LIB_CORE) -o core/run_tests
	./core/run_tests
endif

finance:
ifeq ($(strip $(FIN_SRCS)),)
	@echo "No finance tests"
else
	$(CXX) $(CXXFLAGS) $(FIN_SRCS) $(FIN_LIB_SRCS) -I../include -I../include/duke -I../third_party -I../core/include -o finance/run_tests
	./finance/run_tests
endif
  
  # --- Alvos unitários -------------------------------------------------
production: $(LIB_CORE)
ifeq ($(strip $(PROD_SRCS)),)
		@echo "No production tests"
else
		@mkdir -p production
		$(CXX) $(CXXFLAGS) $(PROD_SRCS) $(PROD_APP_SRCS) \
		-Iproduction -I.. -I../include -I../include/duke -I../core/include \
		$(LIB_CORE) \
		-o production/run_tests
		./production/run_tests
endif

sales: $(LIB_CALC) $(LIB_CORE)
ifeq ($(strip $(SALES_SRCS)),)
	@echo "No sales tests"
else
	@mkdir -p sales
	$(CXX) $(CXXFLAGS) $(SALES_SRCS) \
	-I../include -I../include/duke -I../third_party -I$(CORE_DIR)/include \
	$(LIB_CALC) $(LIB_CORE) \
	-o sales/run_tests
	./sales/run_tests
endif


admin: $(LIB_CORE)
ifeq ($(strip $(ADMIN_SRCS)),)
		@echo "No admin tests"
else
		$(CXX) $(CXXFLAGS) $(ADMIN_SRCS) $(ADMIN_APP_SRCS) $(FIN_LIB_SRCS) -I.. -I../include -I../include/duke -I../third_party -I../core/include $(LIB_CORE) -o admin/run_tests
		./admin/run_tests
endif

designer:
ifeq ($(strip $(DES_SRCS)),)
	@echo "No designer tests"
else
	$(CXX) $(CXXFLAGS) $(DES_SRCS) ../apps/designer/DesignerApp.cpp $(PROD_LIB_SRCS) \
	-I../apps/designer -I../include -I../include/duke -I../third_party -o designer/run_tests
	./designer/run_tests
endif

$(LIB_CALC):
	$(MAKE) -C $(CALC_DIR) libduke.a

$(LIB_CORE):
	$(MAKE) -C $(CORE_DIR) libcore.a

clean:
	rm -f duke/run_tests core/run_tests finance/run_tests designer/run_tests admin/run_tests production/run_tests sales/run_tests

