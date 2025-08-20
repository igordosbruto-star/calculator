cmake_minimum_required(VERSION 3.10)

project(duke_production_app)

add_executable(duke_production main.cpp ProductionApp.cpp)

target_include_directories(duke_production PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/DUKE/include
    ${CMAKE_SOURCE_DIR}/finance/include
)

target_link_libraries(duke_production PRIVATE core duke finance)

