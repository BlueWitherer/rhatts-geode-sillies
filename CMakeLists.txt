cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(rhatt VERSION 1.0.0)

option(CW_TESTING "Enable local testing mode" ON)
option(CW_ENABLE_WEB "Enable web features" OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
endif()

target_link_libraries(${PROJECT_NAME} geode-sdk)

if(CW_TESTING)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CW_TESTING=1)
endif()

if(CW_ENABLE_WEB)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CW_ENABLE_WEB=1)

    CPMAddPackage("gh:GlobedGD/argon@1.5.1")
    target_link_libraries(${PROJECT_NAME} argon)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
