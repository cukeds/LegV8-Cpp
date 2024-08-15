# LegV8-Cpp

LegV8-Cpp is a comprehensive simulation of the LegV8 processor, designed to replicate the architecture and execution flow described in "Computer Organization and Design: The Hardware/Software Interface, ARM® Edition" by David A. Patterson and John L. Hennessy. This project is aimed at both students seeking a deeper understanding of CPU design and educators looking for a practical tool to enhance their teaching.
Features

    Instruction Set Coverage: Supports approximately 20% of the LegV8 instruction set, focusing on essential instructions needed for basic computing tasks. The project aims to cover all instructions in the future.
    Execution Flow: Simulates the execution flow as described in the reference textbook, providing an accurate representation of CPU operations.
    Interactive Environment: Users can load .s files, which are dynamically translated into machine code, and execute them within the simulated processor.
    Configurable Components: While the processor's core architecture (register size, count, memory word size) is fixed, users can configure the memory size and display dimensions.
    Debugging Support: Although no built-in metrics are provided, users can enable detailed debug output with the -d flag or add custom debugging statements to trace the processor's behavior.
    Educational Focus: The simulator is designed to teach various aspects of CPU design, excluding pipelining, which has not yet been implemented.

Getting Started

    Clone the Repository:

    sh

    git clone https://github.com/cukeds/LegV8-Cpp.git

    Build Instructions:
    Follow the instructions in CMakeLists.txt to build the project using CMake.

    Running the Simulation:
    Execute the compiled binary with the -s flag to specify the .s file to load. For example:
    arm.exe -s test.s
    Accepted flags:
    1. -d for debug
    2. -w for display width in pixels (square display)
    3. -o for optimization
    4. -s for source file
    5. -m for memory size in words

Dependencies

    C++
    CMake
    SFML (for the display interface)

Debugging

To enable detailed debugging:

    Uncomment the relevant debug statements in the code.
    Run the simulation with the -d flag to view step-by-step execution details.

Contributing

Contributions are welcome! Whether you're a student, educator, or enthusiast, feel free to fork the repository, create a new branch, and submit a pull request.

# License

This project is licensed under the MIT License.