cmake_minimum_required(VERSION 3.10)

project(duke_designer_app)

add_executable(duke_designer main.cpp DesignerApp.cpp)

target_include_directories(duke_designer PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/DUKE/include
    ${CMAKE_SOURCE_DIR}/finance/include
)

target_link_libraries(duke_designer PRIVATE core duke finance)

