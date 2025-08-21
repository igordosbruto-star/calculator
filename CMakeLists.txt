cmake_minimum_required(VERSION 3.10)
project(calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(core)
add_subdirectory(src/duke)
add_subdirectory(src/finance)

add_subdirectory(apps/admin)
add_subdirectory(apps/designer)
add_subdirectory(apps/production)
add_subdirectory(apps/sales)
