cmake_minimum_required(VERSION 3.26)

project(APP
    VERSION 0.1
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# engine modules
add_subdirectory(core)
add_subdirectory(debug_utils)
add_subdirectory(graphics)
add_subdirectory(platform)

# third party
add_subdirectory(third_party)

# app
add_executable(APP src/main.cpp)

target_link_libraries(APP
    PRIVATE
        core
        debug_utils
        graphics
        platform
)