cmake_minimum_required(VERSION 3.0)
project(LLVM_Calculator_Project)

find_package(LLVM REQUIRED CONFIG)

set(CMAKE_CXX_COMPILER ${LLVM_TOOLS_BINARY_DIR}/clang++)

option(DEBUG_MODE "Enable debug mode" OFF)
if(DEBUG_MODE)
    add_compile_definitions(DEBUG_MODE)
endif()

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(calculator calculator/main.cpp calculator/calculator.cpp)

target_link_libraries(calculator ${LLVM_AVAILABLE_LIBS})