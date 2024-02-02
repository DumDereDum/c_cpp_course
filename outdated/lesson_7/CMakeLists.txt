cmake_minimum_required(VERSION 3.0)
project(CalculatorProject)

option(DEBUG_MODE "Enable debug mode" OFF)
if(DEBUG_MODE)
    add_compile_definitions(DEBUG_MODE)
endif()

# add_executable(calculator calculator/main.cpp calculator/calculator.cpp)
file(GLOB MY_SOURCE_FILES "calculator/*.cpp")
add_executable(calculator ${MY_SOURCE_FILES})

target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/calculator)

