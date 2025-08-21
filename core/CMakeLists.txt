add_library(core_lib
    src/atomic_write.cpp
    src/core.cpp
    src/notifications.cpp
    src/paths.cpp
    src/persist.cpp
    src/persist_csv.cpp
    src/persist_json.cpp
    src/persist_xml.cpp
    src/reports.cpp
    src/settings.cpp
    ${CMAKE_SOURCE_DIR}/third_party/tinyxml2/tinyxml2.cpp
)

target_include_directories(core_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/nlohmann
    ${CMAKE_SOURCE_DIR}/third_party/tinyxml2
)
