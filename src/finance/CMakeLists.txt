add_library(finance_lib
    Repo.cpp
    Report.cpp
    Serialize.cpp
    SupplierRepo.cpp
)

target_include_directories(finance_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/third_party/nlohmann
)

target_link_libraries(finance_lib PUBLIC core_lib)
