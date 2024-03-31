# README.md

# MIPS Emulator

A MIPS emulator implemented in C++.

## Features

- Supports a subset of MIPS instructions
- Assembles MIPS assembly code into machine code
- Executes MIPS machine code
- Provides a memory and register model

## Getting Started

### Prerequisites

- C++ compiler with C++11 support
- CMake

### Building

1. Clone the repository:

   ```
   git clone https://github.com/momo774/mips-emulator.git
   ```

2. Navigate to the project directory:

   ```
   cd mips-emulator
   ```

3. Create a build directory and navigate to it:

   ```
   mkdir build
   cd build
   ```

4. Generate the build files using CMake:

   ```
   cmake ..
   ```

5. Build the project:
   ```
   make
   ```

### Running

1. After building the project, navigate to the `build` directory:

   ```
   cd build
   ```

2. Run the MIPS emulator with an assembly code file:
   ```
   ./mips-emulator ../examples/example1.asm
   ```

## Examples

Example MIPS assembly code files can be found in the `examples` directory.
