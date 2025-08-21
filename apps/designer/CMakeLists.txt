cmake_minimum_required(VERSION 3.10)

project(duke_designer_app)

add_executable(duke_designer
    main.cpp
    DesignerApp.cpp
    ${PROJECT_SOURCE_DIR}/../../src/production/ModeloProducao.cpp
)

target_include_directories(duke_designer PRIVATE
    ${PROJECT_SOURCE_DIR}/../../core/include
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../finance/include
    ${PROJECT_SOURCE_DIR}/../../include
)

target_link_libraries(duke_designer PRIVATE core duke finance)

