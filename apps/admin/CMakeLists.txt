cmake_minimum_required(VERSION 3.10)

project(duke_admin_app)

add_executable(duke_admin main.cpp AdminApp.cpp)

target_include_directories(duke_admin PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/finance/include
)

target_link_libraries(duke_admin PRIVATE core duke finance)

