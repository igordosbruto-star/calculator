cmake_minimum_required(VERSION 3.10)

project(duke_sales_app)

# Build the sales app.  It links against the core and finance libraries
# defined in the existing project.  Adapt the path names to match the
# actual location of these libraries in your repository.

add_executable(duke_sales main.cpp SalesApp.cpp)

target_include_directories(duke_sales PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/third_party/DUKE/include
    ${CMAKE_SOURCE_DIR}/finance/include
)

target_link_libraries(duke_sales PRIVATE core duke finance)

