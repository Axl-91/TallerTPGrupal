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
CMAKE_SOURCE_DIR = /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build

# Include any dependencies generated for this target.
include src/collisions/CMakeFiles/collisions.dir/depend.make

# Include the progress variables for this target.
include src/collisions/CMakeFiles/collisions.dir/progress.make

# Include the compile flags for this target's objects.
include src/collisions/CMakeFiles/collisions.dir/flags.make

src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.o: ../src/collisions/Quadtree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/Quadtree.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Quadtree.cpp

src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/Quadtree.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Quadtree.cpp > CMakeFiles/collisions.dir/Quadtree.cpp.i

src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/Quadtree.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Quadtree.cpp -o CMakeFiles/collisions.dir/Quadtree.cpp.s

src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.o: ../src/collisions/QuadNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/QuadNode.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/QuadNode.cpp

src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/QuadNode.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/QuadNode.cpp > CMakeFiles/collisions.dir/QuadNode.cpp.i

src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/QuadNode.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/QuadNode.cpp -o CMakeFiles/collisions.dir/QuadNode.cpp.s

src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.o: ../src/collisions/Rectangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/Rectangle.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Rectangle.cpp

src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/Rectangle.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Rectangle.cpp > CMakeFiles/collisions.dir/Rectangle.cpp.i

src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/Rectangle.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Rectangle.cpp -o CMakeFiles/collisions.dir/Rectangle.cpp.s

src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.o: ../src/collisions/Collidable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/Collidable.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collidable.cpp

src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/Collidable.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collidable.cpp > CMakeFiles/collisions.dir/Collidable.cpp.i

src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/Collidable.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collidable.cpp -o CMakeFiles/collisions.dir/Collidable.cpp.s

src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.o: ../src/collisions/Collectible.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/Collectible.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collectible.cpp

src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/Collectible.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collectible.cpp > CMakeFiles/collisions.dir/Collectible.cpp.i

src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/Collectible.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Collectible.cpp -o CMakeFiles/collisions.dir/Collectible.cpp.s

src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.o: ../src/collisions/CollectWeapon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/CollectWeapon.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectWeapon.cpp

src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/CollectWeapon.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectWeapon.cpp > CMakeFiles/collisions.dir/CollectWeapon.cpp.i

src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/CollectWeapon.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectWeapon.cpp -o CMakeFiles/collisions.dir/CollectWeapon.cpp.s

src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.o: ../src/collisions/CollectHeal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/CollectHeal.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectHeal.cpp

src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/CollectHeal.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectHeal.cpp > CMakeFiles/collisions.dir/CollectHeal.cpp.i

src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/CollectHeal.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectHeal.cpp -o CMakeFiles/collisions.dir/CollectHeal.cpp.s

src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.o: ../src/collisions/CollectAmmo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/CollectAmmo.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectAmmo.cpp

src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/CollectAmmo.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectAmmo.cpp > CMakeFiles/collisions.dir/CollectAmmo.cpp.i

src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/CollectAmmo.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/CollectAmmo.cpp -o CMakeFiles/collisions.dir/CollectAmmo.cpp.s

src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.o: ../src/collisions/Immovable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/Immovable.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Immovable.cpp

src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/Immovable.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Immovable.cpp > CMakeFiles/collisions.dir/Immovable.cpp.i

src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/Immovable.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/Immovable.cpp -o CMakeFiles/collisions.dir/Immovable.cpp.s

src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.o: src/collisions/CMakeFiles/collisions.dir/flags.make
src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.o: ../src/collisions/ImmovableWall.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.o"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/ImmovableWall.cpp.o -c /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/ImmovableWall.cpp

src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/ImmovableWall.cpp.i"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/ImmovableWall.cpp > CMakeFiles/collisions.dir/ImmovableWall.cpp.i

src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/ImmovableWall.cpp.s"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions/ImmovableWall.cpp -o CMakeFiles/collisions.dir/ImmovableWall.cpp.s

# Object files for target collisions
collisions_OBJECTS = \
"CMakeFiles/collisions.dir/Quadtree.cpp.o" \
"CMakeFiles/collisions.dir/QuadNode.cpp.o" \
"CMakeFiles/collisions.dir/Rectangle.cpp.o" \
"CMakeFiles/collisions.dir/Collidable.cpp.o" \
"CMakeFiles/collisions.dir/Collectible.cpp.o" \
"CMakeFiles/collisions.dir/CollectWeapon.cpp.o" \
"CMakeFiles/collisions.dir/CollectHeal.cpp.o" \
"CMakeFiles/collisions.dir/CollectAmmo.cpp.o" \
"CMakeFiles/collisions.dir/Immovable.cpp.o" \
"CMakeFiles/collisions.dir/ImmovableWall.cpp.o"

# External object files for target collisions
collisions_EXTERNAL_OBJECTS =

src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/Quadtree.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/QuadNode.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/Rectangle.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/Collidable.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/Collectible.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/CollectWeapon.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/CollectHeal.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/CollectAmmo.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/Immovable.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/ImmovableWall.cpp.o
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/build.make
src/collisions/libcollisions.so: src/collisions/CMakeFiles/collisions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library libcollisions.so"
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/collisions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/collisions/CMakeFiles/collisions.dir/build: src/collisions/libcollisions.so

.PHONY : src/collisions/CMakeFiles/collisions.dir/build

src/collisions/CMakeFiles/collisions.dir/clean:
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions && $(CMAKE_COMMAND) -P CMakeFiles/collisions.dir/cmake_clean.cmake
.PHONY : src/collisions/CMakeFiles/collisions.dir/clean

src/collisions/CMakeFiles/collisions.dir/depend:
	cd /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/src/collisions /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions /home/axel/Descargas/Taller/TallerTPGrupal/ClientePrueba/build/src/collisions/CMakeFiles/collisions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/collisions/CMakeFiles/collisions.dir/depend
