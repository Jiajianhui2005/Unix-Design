cmake_minimum_required(VERSION 3.16)

project(HighPerformanceWebServer
    VERSION 0.2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(webserver
    src/main.cpp
    src/config/Config.cpp
    src/server/WebServer.cpp
)

target_include_directories(webserver PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(webserver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
