# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build

# Include any dependencies generated for this target.
include CMakeFiles/output_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/output_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/output_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/output_server.dir/flags.make

CMakeFiles/output_server.dir/main.cpp.o: CMakeFiles/output_server.dir/flags.make
CMakeFiles/output_server.dir/main.cpp.o: /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/main.cpp
CMakeFiles/output_server.dir/main.cpp.o: CMakeFiles/output_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/output_server.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/output_server.dir/main.cpp.o -MF CMakeFiles/output_server.dir/main.cpp.o.d -o CMakeFiles/output_server.dir/main.cpp.o -c /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/main.cpp

CMakeFiles/output_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/output_server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/main.cpp > CMakeFiles/output_server.dir/main.cpp.i

CMakeFiles/output_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/output_server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/main.cpp -o CMakeFiles/output_server.dir/main.cpp.s

# Object files for target output_server
output_server_OBJECTS = \
"CMakeFiles/output_server.dir/main.cpp.o"

# External object files for target output_server
output_server_EXTERNAL_OBJECTS =

output_server: CMakeFiles/output_server.dir/main.cpp.o
output_server: CMakeFiles/output_server.dir/build.make
output_server: CMakeFiles/output_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable output_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/output_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/output_server.dir/build: output_server
.PHONY : CMakeFiles/output_server.dir/build

CMakeFiles/output_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/output_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/output_server.dir/clean

CMakeFiles/output_server.dir/depend:
	cd /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build /home/max/Документы/InfotecsEvents/Infotecs_TraineeC++_2024/output_server/build/CMakeFiles/output_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/output_server.dir/depend

