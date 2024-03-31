# MIPS Emulator

Developed a comprehensive MIPS (Microprocessor without Interlocked Pipelined Stages) emulator using C++ to simulate the functionality of a MIPS processor. The emulator includes an assembler that translates MIPS assembly code into machine code and executes the instructions, mimicking the behavior of a real MIPS processor.

## MIPS Emulator Design Document


### Introduction 
This MIPS Emulator is a software project that aims to simulate the functionality of a MIPS processor. It provides a complete environment for executing MIPS assembly code, including an assembler to translate the code into machine code and an emulator to execute the instructions. The emulator mimics the behavior of a real MIPS processor by maintaining the state of registers, memory, and program counter, and performing the necessary operations defined by the MIPS instruction set architecture (ISA).
### System Architecture 
#### 2.1 Overview 
The MIPS Emulator consists of several key components that work together to provide the emulation functionality:
##### Assembler: Responsible for translating MIPS assembly code into machine code.
##### Emulator: Executes the machine code instructions and maintains the processor state.
##### Memory: Represents the MIPS memory hierarchy and provides read/write operations.
##### Registers: Represents the MIPS register set, including general-purpose and special-purpose registers.
##### Instructions: Defines the MIPS instruction set and provides functions for executing each instruction.
##### Cache: Simulates the behavior of instruction and data caches to improve emulator performance.
#### 2.2 Component Details 
##### 2.2.1 Assembler 
The assembler component is responsible for translating MIPS assembly code into machine code. It performs the following tasks:
Parses the assembly code and identifies labels, directives, and instructions.
Handles data directives such as .word, .byte, and .asciiz to define and initialize data in memory.
Generates machine code for each instruction based on the MIPS ISA.
Resolves labels and calculates memory addresses for branch and jump instructions.
Reports errors and provides informative error messages with line numbers for debugging.
##### 2.2.2 Emulator 
The emulator component is the core of the MIPS Emulator. It executes the machine code instructions and maintains the processor state. The emulator performs the following tasks:
Fetches instructions from memory based on the program counter (PC).
Decodes the instructions to determine the operation and operands.
Executes the instructions by performing the necessary operations on registers and memory.
Updates the program counter (PC) to point to the next instruction.
Handles branch and jump instructions by modifying the PC accordingly.
Interacts with the memory and register components to read and write data.
##### 2.2.3 Memory 
The memory component represents the MIPS memory hierarchy. It provides read and write operations at both byte and word levels. The memory is implemented as a large byte array, and the emulator uses memory addressing to access specific locations. The memory component supports the following operations:
Reading a byte or word from a specific memory address.
Writing a byte or word to a specific memory address.
Initializing memory with data specified by the assembler directives.
##### 2.2.4 Registers 
The registers component represents the MIPS register set, including general-purpose registers and special-purpose registers. It provides functions for accessing and modifying register values. The registers are implemented as an array, with each index corresponding to a specific register. The register component supports the following operations:
Reading the value of a specific register.
Writing a value to a specific register.
Handling special-purpose registers such as the program counter (PC) and the HI/LO registers used for multiplication and division.
##### 2.2.5 Instructions 
The instructions component defines the MIPS instruction set and provides functions for executing each instruction. It includes the implementation of various instruction types, such as R-type, I-type, and J-type instructions. The instruction execution process involves the following steps:
Decoding the instruction to determine the operation and operands.
Retrieving the necessary values from registers or memory.
Performing the specified operation on the operands.
Storing the result back in registers or memory.
Updating the program counter (PC) based on the instruction type.
##### 2.2.6 Cache 
The cache component simulates the behavior of instruction and data caches to improve the emulator's performance. It implements a basic cache structure with configurable size, block size, and associativity. The cache component performs the following tasks:
Checking if a requested memory address is present in the cache (cache hit).
Fetching data from the main memory and storing it in the cache on a cache miss.
Replacing cache blocks based on a replacement policy (e.g., random replacement).
Updating the cache contents when writing data to memory.
### Instruction Execution Flow 
The instruction execution flow in the MIPS Emulator follows the fetch-decode-execute cycle:
#### Fetch: The emulator fetches the instruction pointed to by the program counter (PC) from memory. It first checks if the instruction is present in the cache. If it's a cache hit, the instruction is retrieved from the cache. Otherwise, it's fetched from the main memory and stored in the cache.
#### Decode: The fetched instruction is decoded to determine the operation and operands. The opcode and other fields of the instruction are extracted and used to identify the specific instruction type (R-type, I-type, or J-type).
#### Execute: Based on the decoded instruction, the emulator performs the corresponding operation. This may involve reading values from registers, performing arithmetic or logical operations, accessing memory, or updating the program counter (PC). The execution process varies depending on the instruction type:
###### R-type instructions: The values from the specified registers are read, the operation is performed, and the result is stored back in the destination register.
###### I-type instructions: The value from the specified register and the immediate value are used to perform the operation, and the result is stored in the destination register or used for memory access.
###### J-type instructions: The program counter (PC) is updated based on the target address specified in the instruction.
#### Writeback: If the instruction involves writing a result back to a register or memory, the writeback stage is performed. The result is stored in the appropriate register or memory location.
#### PC Update: After executing the instruction, the program counter (PC) is updated to point to the next instruction. For normal instructions, the PC is incremented by 4 (since MIPS instructions are 4 bytes long). For branch or jump instructions, the PC is updated based on the target address.
### Memory Hierarchy 
The MIPS Emulator simulates the memory hierarchy, including main memory and caches. The memory component represents the main memory, which is a large byte array. The cache component simulates the behavior of instruction and data caches to improve the emulator's performance.
#### Main Memory: The main memory is accessed using byte-level and word-level read and write operations. The memory addresses are used to specify the location of data in memory.
#### Caches: The cache component implements a basic cache structure with configurable size, block size, and associativity. When the emulator requests data from memory, it first checks if the data is present in the cache. If it's a cache hit, the data is retrieved from the cache. Otherwise, it's fetched from the main memory and stored in the cache for future access. The cache replacement policy (e.g., random replacement) is used to evict cache blocks when the cache is full.

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
