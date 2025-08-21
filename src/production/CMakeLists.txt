add_library(production
    ModeloProducao.cpp
)

target_include_directories(production PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
