cmake_minimum_required(VERSION 3.10)

project(duke_production_app)

add_executable(duke_production
    main.cpp
    ProductionApp.cpp
    ${PROJECT_SOURCE_DIR}/../../src/production/ModeloProducao.cpp
)

target_include_directories(duke_production PRIVATE
    ${PROJECT_SOURCE_DIR}/../../core/include
    ${PROJECT_SOURCE_DIR}/../../include
)

target_link_libraries(duke_production PRIVATE core_lib duke_lib finance_lib)

