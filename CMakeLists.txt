cmake_minimum_required(VERSION 4.2.1)
project(BG_LimitOrderBook LANGUAGES CXX)

# 1. Ensure C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. High-Performance Compiler Flags
if(MSVC)
    add_compile_options(/W4 /OX /Oi)
else()
    add_compile_options(
        -Wall -Wextra -Wpedantic -Wshadow
        -O3                 # Maximum optimization
        -march=native       # Optimize for YOUR specific CPU (M1/M2/Intel)
        -flto               # Link Time Optimization (huge for inlining)
        -fomit-frame-pointer # Frees up a register for data
    )
endif()

# 3. Project Structure
# We'll use a header-only approach for the core LOB to maximize inlining,
# but we'll still define an include directory.
include_directories(include)

# 4. Executables
add_executable(BG_LOB 
    src/main.cpp
)

# 5. Link-Time Optimization (LTO)
# This allows the compiler to inline functions across different .cpp files.
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if(supported)
    set_property(TARGET BG_LOB PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    message(STATUS "LTO/IPO is enabled for maximum performance.")
endif()
