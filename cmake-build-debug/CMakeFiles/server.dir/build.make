# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/177/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/177/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dima/!Stuff/TP/trying to make engine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/src/Network/danya_server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Network/danya_server.cpp.o: ../src/Network/danya_server.cpp
CMakeFiles/server.dir/src/Network/danya_server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/src/Network/danya_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/Network/danya_server.cpp.o -MF CMakeFiles/server.dir/src/Network/danya_server.cpp.o.d -o CMakeFiles/server.dir/src/Network/danya_server.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/Network/danya_server.cpp"

CMakeFiles/server.dir/src/Network/danya_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Network/danya_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/Network/danya_server.cpp" > CMakeFiles/server.dir/src/Network/danya_server.cpp.i

CMakeFiles/server.dir/src/Network/danya_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Network/danya_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/Network/danya_server.cpp" -o CMakeFiles/server.dir/src/Network/danya_server.cpp.s

CMakeFiles/server.dir/src/Network/main_sever.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Network/main_sever.cpp.o: ../src/Network/main_sever.cpp
CMakeFiles/server.dir/src/Network/main_sever.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/Network/main_sever.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/Network/main_sever.cpp.o -MF CMakeFiles/server.dir/src/Network/main_sever.cpp.o.d -o CMakeFiles/server.dir/src/Network/main_sever.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/Network/main_sever.cpp"

CMakeFiles/server.dir/src/Network/main_sever.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Network/main_sever.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/Network/main_sever.cpp" > CMakeFiles/server.dir/src/Network/main_sever.cpp.i

CMakeFiles/server.dir/src/Network/main_sever.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Network/main_sever.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/Network/main_sever.cpp" -o CMakeFiles/server.dir/src/Network/main_sever.cpp.s

CMakeFiles/server.dir/src/models/model.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/model.cpp.o: ../src/models/model.cpp
CMakeFiles/server.dir/src/models/model.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/src/models/model.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/model.cpp.o -MF CMakeFiles/server.dir/src/models/model.cpp.o.d -o CMakeFiles/server.dir/src/models/model.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/model.cpp"

CMakeFiles/server.dir/src/models/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/model.cpp" > CMakeFiles/server.dir/src/models/model.cpp.i

CMakeFiles/server.dir/src/models/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/model.cpp" -o CMakeFiles/server.dir/src/models/model.cpp.s

CMakeFiles/server.dir/src/models/wall.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/wall.cpp.o: ../src/models/wall.cpp
CMakeFiles/server.dir/src/models/wall.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/src/models/wall.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/wall.cpp.o -MF CMakeFiles/server.dir/src/models/wall.cpp.o.d -o CMakeFiles/server.dir/src/models/wall.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/wall.cpp"

CMakeFiles/server.dir/src/models/wall.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/wall.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/wall.cpp" > CMakeFiles/server.dir/src/models/wall.cpp.i

CMakeFiles/server.dir/src/models/wall.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/wall.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/wall.cpp" -o CMakeFiles/server.dir/src/models/wall.cpp.s

CMakeFiles/server.dir/src/models/player.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/player.cpp.o: ../src/models/player.cpp
CMakeFiles/server.dir/src/models/player.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/src/models/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/player.cpp.o -MF CMakeFiles/server.dir/src/models/player.cpp.o.d -o CMakeFiles/server.dir/src/models/player.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/player.cpp"

CMakeFiles/server.dir/src/models/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/player.cpp" > CMakeFiles/server.dir/src/models/player.cpp.i

CMakeFiles/server.dir/src/models/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/player.cpp" -o CMakeFiles/server.dir/src/models/player.cpp.s

CMakeFiles/server.dir/src/models/mob.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/mob.cpp.o: ../src/models/mob.cpp
CMakeFiles/server.dir/src/models/mob.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/src/models/mob.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/mob.cpp.o -MF CMakeFiles/server.dir/src/models/mob.cpp.o.d -o CMakeFiles/server.dir/src/models/mob.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/mob.cpp"

CMakeFiles/server.dir/src/models/mob.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/mob.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/mob.cpp" > CMakeFiles/server.dir/src/models/mob.cpp.i

CMakeFiles/server.dir/src/models/mob.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/mob.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/mob.cpp" -o CMakeFiles/server.dir/src/models/mob.cpp.s

CMakeFiles/server.dir/src/models/map.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/map.cpp.o: ../src/models/map.cpp
CMakeFiles/server.dir/src/models/map.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/src/models/map.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/map.cpp.o -MF CMakeFiles/server.dir/src/models/map.cpp.o.d -o CMakeFiles/server.dir/src/models/map.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/map.cpp"

CMakeFiles/server.dir/src/models/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/map.cpp" > CMakeFiles/server.dir/src/models/map.cpp.i

CMakeFiles/server.dir/src/models/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/map.cpp" -o CMakeFiles/server.dir/src/models/map.cpp.s

CMakeFiles/server.dir/src/models/bullet.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/models/bullet.cpp.o: ../src/models/bullet.cpp
CMakeFiles/server.dir/src/models/bullet.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/src/models/bullet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/models/bullet.cpp.o -MF CMakeFiles/server.dir/src/models/bullet.cpp.o.d -o CMakeFiles/server.dir/src/models/bullet.cpp.o -c "/home/dima/!Stuff/TP/trying to make engine/src/models/bullet.cpp"

CMakeFiles/server.dir/src/models/bullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/models/bullet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dima/!Stuff/TP/trying to make engine/src/models/bullet.cpp" > CMakeFiles/server.dir/src/models/bullet.cpp.i

CMakeFiles/server.dir/src/models/bullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/models/bullet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dima/!Stuff/TP/trying to make engine/src/models/bullet.cpp" -o CMakeFiles/server.dir/src/models/bullet.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/Network/danya_server.cpp.o" \
"CMakeFiles/server.dir/src/Network/main_sever.cpp.o" \
"CMakeFiles/server.dir/src/models/model.cpp.o" \
"CMakeFiles/server.dir/src/models/wall.cpp.o" \
"CMakeFiles/server.dir/src/models/player.cpp.o" \
"CMakeFiles/server.dir/src/models/mob.cpp.o" \
"CMakeFiles/server.dir/src/models/map.cpp.o" \
"CMakeFiles/server.dir/src/models/bullet.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/src/Network/danya_server.cpp.o
server: CMakeFiles/server.dir/src/Network/main_sever.cpp.o
server: CMakeFiles/server.dir/src/models/model.cpp.o
server: CMakeFiles/server.dir/src/models/wall.cpp.o
server: CMakeFiles/server.dir/src/models/player.cpp.o
server: CMakeFiles/server.dir/src/models/mob.cpp.o
server: CMakeFiles/server.dir/src/models/map.cpp.o
server: CMakeFiles/server.dir/src/models/bullet.cpp.o
server: CMakeFiles/server.dir/build.make
server: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
server: /usr/lib/x86_64-linux-gnu/libsfml-window.so
server: /usr/lib/x86_64-linux-gnu/libsfml-system.so
server: /usr/lib/x86_64-linux-gnu/libsfml-network.so
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd "/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dima/!Stuff/TP/trying to make engine" "/home/dima/!Stuff/TP/trying to make engine" "/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug" "/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug" "/home/dima/!Stuff/TP/trying to make engine/cmake-build-debug/CMakeFiles/server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

