file(GLOB_RECURSE DUKE_SOURCES CONFIGURE_DEPENDS *.cpp)
list(REMOVE_ITEM DUKE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
list(REMOVE_ITEM DUKE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/gui/MainWindow.cpp)
list(REMOVE_ITEM DUKE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/gui/main_wx.cpp)

add_library(duke_lib ${DUKE_SOURCES})

target_include_directories(duke_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include/duke
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/third_party/nlohmann
)

target_link_libraries(duke_lib PUBLIC core_lib)
