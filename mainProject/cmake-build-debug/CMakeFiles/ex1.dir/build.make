# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/code/Thesis/mainProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/code/Thesis/mainProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex1.dir/flags.make

CMakeFiles/ex1.dir/main.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/main.cpp.o -c /mnt/c/code/Thesis/mainProject/main.cpp

CMakeFiles/ex1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/main.cpp > CMakeFiles/ex1.dir/main.cpp.i

CMakeFiles/ex1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/main.cpp -o CMakeFiles/ex1.dir/main.cpp.s

CMakeFiles/ex1.dir/EuropeanOption.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/EuropeanOption.cpp.o: ../EuropeanOption.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex1.dir/EuropeanOption.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/EuropeanOption.cpp.o -c /mnt/c/code/Thesis/mainProject/EuropeanOption.cpp

CMakeFiles/ex1.dir/EuropeanOption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/EuropeanOption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/EuropeanOption.cpp > CMakeFiles/ex1.dir/EuropeanOption.cpp.i

CMakeFiles/ex1.dir/EuropeanOption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/EuropeanOption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/EuropeanOption.cpp -o CMakeFiles/ex1.dir/EuropeanOption.cpp.s

CMakeFiles/ex1.dir/Calibration.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/Calibration.cpp.o: ../Calibration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex1.dir/Calibration.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/Calibration.cpp.o -c /mnt/c/code/Thesis/mainProject/Calibration.cpp

CMakeFiles/ex1.dir/Calibration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/Calibration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/Calibration.cpp > CMakeFiles/ex1.dir/Calibration.cpp.i

CMakeFiles/ex1.dir/Calibration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/Calibration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/Calibration.cpp -o CMakeFiles/ex1.dir/Calibration.cpp.s

CMakeFiles/ex1.dir/SPXOption.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/SPXOption.cpp.o: ../SPXOption.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ex1.dir/SPXOption.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/SPXOption.cpp.o -c /mnt/c/code/Thesis/mainProject/SPXOption.cpp

CMakeFiles/ex1.dir/SPXOption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/SPXOption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/SPXOption.cpp > CMakeFiles/ex1.dir/SPXOption.cpp.i

CMakeFiles/ex1.dir/SPXOption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/SPXOption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/SPXOption.cpp -o CMakeFiles/ex1.dir/SPXOption.cpp.s

CMakeFiles/ex1.dir/VIXOption.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/VIXOption.cpp.o: ../VIXOption.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ex1.dir/VIXOption.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/VIXOption.cpp.o -c /mnt/c/code/Thesis/mainProject/VIXOption.cpp

CMakeFiles/ex1.dir/VIXOption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/VIXOption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/VIXOption.cpp > CMakeFiles/ex1.dir/VIXOption.cpp.i

CMakeFiles/ex1.dir/VIXOption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/VIXOption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/VIXOption.cpp -o CMakeFiles/ex1.dir/VIXOption.cpp.s

CMakeFiles/ex1.dir/Faddeeva.cc.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/Faddeeva.cc.o: ../Faddeeva.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ex1.dir/Faddeeva.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/Faddeeva.cc.o -c /mnt/c/code/Thesis/mainProject/Faddeeva.cc

CMakeFiles/ex1.dir/Faddeeva.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/Faddeeva.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/code/Thesis/mainProject/Faddeeva.cc > CMakeFiles/ex1.dir/Faddeeva.cc.i

CMakeFiles/ex1.dir/Faddeeva.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/Faddeeva.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/code/Thesis/mainProject/Faddeeva.cc -o CMakeFiles/ex1.dir/Faddeeva.cc.s

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles/ex1.dir/main.cpp.o" \
"CMakeFiles/ex1.dir/EuropeanOption.cpp.o" \
"CMakeFiles/ex1.dir/Calibration.cpp.o" \
"CMakeFiles/ex1.dir/SPXOption.cpp.o" \
"CMakeFiles/ex1.dir/VIXOption.cpp.o" \
"CMakeFiles/ex1.dir/Faddeeva.cc.o"

# External object files for target ex1
ex1_EXTERNAL_OBJECTS =

ex1: CMakeFiles/ex1.dir/main.cpp.o
ex1: CMakeFiles/ex1.dir/EuropeanOption.cpp.o
ex1: CMakeFiles/ex1.dir/Calibration.cpp.o
ex1: CMakeFiles/ex1.dir/SPXOption.cpp.o
ex1: CMakeFiles/ex1.dir/VIXOption.cpp.o
ex1: CMakeFiles/ex1.dir/Faddeeva.cc.o
ex1: CMakeFiles/ex1.dir/build.make
ex1: CMakeFiles/ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ex1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex1.dir/build: ex1

.PHONY : CMakeFiles/ex1.dir/build

CMakeFiles/ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex1.dir/clean

CMakeFiles/ex1.dir/depend:
	cd /mnt/c/code/Thesis/mainProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/code/Thesis/mainProject /mnt/c/code/Thesis/mainProject /mnt/c/code/Thesis/mainProject/cmake-build-debug /mnt/c/code/Thesis/mainProject/cmake-build-debug /mnt/c/code/Thesis/mainProject/cmake-build-debug/CMakeFiles/ex1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex1.dir/depend
