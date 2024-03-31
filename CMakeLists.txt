cmake_minimum_required(VERSION 3.0)
project(mips-emulator)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(mips-emulator
    src/main.cpp
    src/emulator.cpp
    src/assembler.cpp
    src/memory.cpp
    src/registers.cpp
    src/instructions.cpp
    src/cache.cpp
    src/utils.cpp
)