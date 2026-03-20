# Conway's Game of Life

An interactive implementation of Conway's Game of Life built with C++ and SDL3. This project features a real-time
cellular automaton simulation with camera controls, pattern placement, and support for both native desktop and web
platforms via Emscripten.

## Overview

Conway's Game of Life is a zero-player game that simulates cellular automata on a two-dimensional grid. Each cell can be
either alive or dead, and the state evolves according to simple rules:

- A live cell with 2 or 3 live neighbors survives to the next generation
- A dead cell with exactly 3 live neighbors becomes alive
- All other cells die or remain dead

This implementation provides an interactive interface for exploring these patterns with smooth camera controls and a
variety of pre-built patterns.

## Requirements

- CMake 3.16 or higher
- C++20 compatible compiler (GCC, Clang, or MSVC)
- SDL3 (included as a vendored dependency)

For web builds:

- Emscripten SDK

## Building

### Native Build

1. Clone the repository:

```bash
git clone <repository-url>
cd conways-game-of-life
```

2. Create a build directory:

```bash
mkdir build
cd build
```

4. Clone SDL 3

```bash
mkdir -p vendored
cd vendored
```

```bash
git clone https://github.com/libsdl-org/SDL.git SDL3
```

3. Configure and build:

```bash
cmake ..
cmake --build .
```

The executable will be located in `build/<config>/conways-game-of-life` (or `conways-game-of-life.exe` on Windows).

## Controls

### Mouse

- **Left Click**: Place or remove a cell at the cursor position
- **Right Click + Drag**: Pan the camera
- **Mouse Wheel**: Zoom in and out

### Keyboard

- **Space**: Advance simulation by one generation
- **R**: Rotate the currently selected pattern (if any)
- **1-8**: Select a predefined pattern (1-8)
- **9**: Deselect pattern

### Patterns

The following patterns are available:

1. Glider
2. Acorn
3. Heavyweight Spaceship (HWSS)
4. Gosper Glider Gun
5. Pulsar
6. Pentadecathlon
7. Prime Calculator
8. Turing Machine

## Architecture

The project uses a sparse grid implementation where only active cells are stored in memory. This allows for efficient
simulation of large patterns without memory constraints. The implementation uses:

- `std::unordered_set<Cell>` for storing active cells
- Separate sets for tracking potential cells that may become active
- Viewport culling to only render visible cells
- Camera system for world-to-screen coordinate transformation

## Project Structure

```
conways-game-of-life/
├── CMakeLists.txt              # Top-level CMake configuration
├── conways-game-of-life/
│   ├── CMakeLists.txt          # Project-specific CMake configuration
│   ├── main.cpp                # Application entry point
│   ├── game.h                  # Game class header
│   ├── game.cpp                # Game class implementation
│   ├── cell.h                  # Cell structure and hash set definitions
│   ├── cell.cpp                # Cell implementation
│   ├── camera.h                # Camera and coordinate transformation
│   ├── common.h                # Common constants and forward declarations
│   └── patterns/
│       ├── pattern.h           # Pattern class header
│       ├── pattern.cpp         # Pattern implementations and loading
│       └── rle/                # Run length encoded patterns
└── vendored/
    └── SDL/                    # SDL3 source code
```

## License

This project is licensed under the MIT License. See the LICENSE.txt file for details.

## Acknowledgments

- The (p,p+8) prime calculator was created by Nathaniel Johnston. It is based on the cousin prime calculator, which is based on Dean Hickerson's primer pattern. Constructed on August 2, 2009 with calcyman.

- The Turing Machine was designed by Paul Rendell April 2, 2000. http://rendell-attic.org/gol/tm.htm