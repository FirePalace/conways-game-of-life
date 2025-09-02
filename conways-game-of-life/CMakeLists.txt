# CMakeList.txt : CMake project for conways-game-of-life, include source and define
# project specific logic here.
#


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
# Add source to this project's executable.
add_executable (conways-game-of-life "main.cpp" "game.cpp"    "common.h" "coordinate.h" "coordinate.cpp")

target_link_libraries(conways-game-of-life PRIVATE SDL3::SDL3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET conways-game-of-life PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
