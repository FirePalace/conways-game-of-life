# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.

project ("conways-game-of-life")

# Include sub-projects.
add_subdirectory ("conways-game-of-life")