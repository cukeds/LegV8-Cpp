# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl"

# Include any dependencies generated for this target.
include CMakeFiles/arm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/arm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/arm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/arm.dir/flags.make

CMakeFiles/arm.dir/main.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/main.cpp.o: ../main.cpp
CMakeFiles/arm.dir/main.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/arm.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/main.cpp.o -MF CMakeFiles/arm.dir/main.cpp.o.d -o CMakeFiles/arm.dir/main.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/main.cpp"

CMakeFiles/arm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/main.cpp" > CMakeFiles/arm.dir/main.cpp.i

CMakeFiles/arm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/main.cpp" -o CMakeFiles/arm.dir/main.cpp.s

CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o: ../Components/ProgramCounter.cpp
CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o -MF CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o.d -o CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/ProgramCounter.cpp"

CMakeFiles/arm.dir/Components/ProgramCounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Components/ProgramCounter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/ProgramCounter.cpp" > CMakeFiles/arm.dir/Components/ProgramCounter.cpp.i

CMakeFiles/arm.dir/Components/ProgramCounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Components/ProgramCounter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/ProgramCounter.cpp" -o CMakeFiles/arm.dir/Components/ProgramCounter.cpp.s

CMakeFiles/arm.dir/Components/Processor.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Components/Processor.cpp.o: ../Components/Processor.cpp
CMakeFiles/arm.dir/Components/Processor.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/arm.dir/Components/Processor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Components/Processor.cpp.o -MF CMakeFiles/arm.dir/Components/Processor.cpp.o.d -o CMakeFiles/arm.dir/Components/Processor.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Processor.cpp"

CMakeFiles/arm.dir/Components/Processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Components/Processor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Processor.cpp" > CMakeFiles/arm.dir/Components/Processor.cpp.i

CMakeFiles/arm.dir/Components/Processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Components/Processor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Processor.cpp" -o CMakeFiles/arm.dir/Components/Processor.cpp.s

CMakeFiles/arm.dir/Components/RegisterBank.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Components/RegisterBank.cpp.o: ../Components/RegisterBank.cpp
CMakeFiles/arm.dir/Components/RegisterBank.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/arm.dir/Components/RegisterBank.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Components/RegisterBank.cpp.o -MF CMakeFiles/arm.dir/Components/RegisterBank.cpp.o.d -o CMakeFiles/arm.dir/Components/RegisterBank.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/RegisterBank.cpp"

CMakeFiles/arm.dir/Components/RegisterBank.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Components/RegisterBank.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/RegisterBank.cpp" > CMakeFiles/arm.dir/Components/RegisterBank.cpp.i

CMakeFiles/arm.dir/Components/RegisterBank.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Components/RegisterBank.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/RegisterBank.cpp" -o CMakeFiles/arm.dir/Components/RegisterBank.cpp.s

CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o: ../Components/Controls/Signal.cpp
CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o -MF CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o.d -o CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Controls/Signal.cpp"

CMakeFiles/arm.dir/Components/Controls/Signal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Components/Controls/Signal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Controls/Signal.cpp" > CMakeFiles/arm.dir/Components/Controls/Signal.cpp.i

CMakeFiles/arm.dir/Components/Controls/Signal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Components/Controls/Signal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/Controls/Signal.cpp" -o CMakeFiles/arm.dir/Components/Controls/Signal.cpp.s

CMakeFiles/arm.dir/Components/SignExtend.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Components/SignExtend.cpp.o: ../Components/SignExtend.cpp
CMakeFiles/arm.dir/Components/SignExtend.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/arm.dir/Components/SignExtend.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Components/SignExtend.cpp.o -MF CMakeFiles/arm.dir/Components/SignExtend.cpp.o.d -o CMakeFiles/arm.dir/Components/SignExtend.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/SignExtend.cpp"

CMakeFiles/arm.dir/Components/SignExtend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Components/SignExtend.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/SignExtend.cpp" > CMakeFiles/arm.dir/Components/SignExtend.cpp.i

CMakeFiles/arm.dir/Components/SignExtend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Components/SignExtend.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Components/SignExtend.cpp" -o CMakeFiles/arm.dir/Components/SignExtend.cpp.s

CMakeFiles/arm.dir/Display/Display.cpp.o: CMakeFiles/arm.dir/flags.make
CMakeFiles/arm.dir/Display/Display.cpp.o: ../Display/Display.cpp
CMakeFiles/arm.dir/Display/Display.cpp.o: CMakeFiles/arm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/arm.dir/Display/Display.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arm.dir/Display/Display.cpp.o -MF CMakeFiles/arm.dir/Display/Display.cpp.o.d -o CMakeFiles/arm.dir/Display/Display.cpp.o -c "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Display/Display.cpp"

CMakeFiles/arm.dir/Display/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm.dir/Display/Display.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Display/Display.cpp" > CMakeFiles/arm.dir/Display/Display.cpp.i

CMakeFiles/arm.dir/Display/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm.dir/Display/Display.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/Display/Display.cpp" -o CMakeFiles/arm.dir/Display/Display.cpp.s

# Object files for target arm
arm_OBJECTS = \
"CMakeFiles/arm.dir/main.cpp.o" \
"CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o" \
"CMakeFiles/arm.dir/Components/Processor.cpp.o" \
"CMakeFiles/arm.dir/Components/RegisterBank.cpp.o" \
"CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o" \
"CMakeFiles/arm.dir/Components/SignExtend.cpp.o" \
"CMakeFiles/arm.dir/Display/Display.cpp.o"

# External object files for target arm
arm_EXTERNAL_OBJECTS =

arm: CMakeFiles/arm.dir/main.cpp.o
arm: CMakeFiles/arm.dir/Components/ProgramCounter.cpp.o
arm: CMakeFiles/arm.dir/Components/Processor.cpp.o
arm: CMakeFiles/arm.dir/Components/RegisterBank.cpp.o
arm: CMakeFiles/arm.dir/Components/Controls/Signal.cpp.o
arm: CMakeFiles/arm.dir/Components/SignExtend.cpp.o
arm: CMakeFiles/arm.dir/Display/Display.cpp.o
arm: CMakeFiles/arm.dir/build.make
arm: /usr/lib/x86_64-linux-gnu/libsfml-system.so
arm: /usr/lib/x86_64-linux-gnu/libsfml-window.so
arm: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
arm: CMakeFiles/arm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable arm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/arm.dir/build: arm
.PHONY : CMakeFiles/arm.dir/build

CMakeFiles/arm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arm.dir/clean

CMakeFiles/arm.dir/depend:
	cd "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm" "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm" "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl" "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl" "/mnt/c/Users/Juan/Downloads/Cookie and Morts shit/University/Arq. De Computadoras/arm/cmake-build-wsl/CMakeFiles/arm.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/arm.dir/depend
