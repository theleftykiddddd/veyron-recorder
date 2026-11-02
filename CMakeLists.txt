cmake_minimum_required(VERSION 3.21)
project(VeyronProyect VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(VEYRON_STANDALONE_TESTS "Build platform-neutral core tests without Geode" OFF)
set(VEYRON_CORE
    src/core/Macro.cpp
    src/core/WindowAnalyzer.cpp
    src/core/Recorder.cpp
    src/core/Replay.cpp
    src/core/FormatIO.cpp
)
if(VEYRON_STANDALONE_TESTS)
    add_library(veyron-core STATIC ${VEYRON_CORE})
    target_include_directories(veyron-core PUBLIC include)
    add_executable(veyron-core-tests tests/core_smoke.cpp)
    target_link_libraries(veyron-core-tests PRIVATE veyron-core)
    enable_testing()
    add_test(NAME veyron-core-tests COMMAND veyron-core-tests)
    return()
endif()

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK is not set. Install/configure Geode SDK or use -DVEYRON_STANDALONE_TESTS=ON for core tests.")
endif()
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
