# Top‑level CMakeLists for building DUKE ERP apps

cmake_minimum_required(VERSION 3.10)

project(duke_apps)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectories for each app.  Each app will be built into its own
# executable.  These directories contain their own CMakeLists that link
# against the core libraries.
add_subdirectory(sales)
add_subdirectory(production)
add_subdirectory(admin)
add_subdirectory(designer)

