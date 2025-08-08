# GraphGame

A lightweight clone of [Graphwar](https://www.graphwar.com/) built using SFML 3.0.0 for graphics and Boost for testing. 
This is simple strategy game in which you must hit enemies using mathematical functions - the trajectory of your shot is determined by the function you write.

## Screenshots

![Example 1](/Screenshots/Screenshot_from_2025-08-08_02-36-44.png)
![Example 2](/Screenshots/Screenshot_from_2025-08-08_02-36-56.png)

## Requirements

- A valid C++ compiler (clang or gcc) with C++23 support
- CMake ≥ v3.20
- SFML ≥ v3.0.0
- Boost ≥ v1.74.0 (needed only for testing)

## Building

### Linux (Debian/Ubuntu)

# Build SFML 3.0.0
```bash
git clone --depth=1 --branch 3.0.0 https://github.com/SFML/SFML.git SFML # Clone repository
cd SFML
mkdir build && cd build
cmake .. # Configure SFML build
make -j4 # Build SFML with 4 threads
```

# Build GraphGame
```bash
git clone --depth=1 https://github.com/itz-sqh/GraphGame # Clone repository
cd GraphGame
mkdir build && cd build # Create a directory for cmake
cmake .. # Configure project
make -j4 # Build the project
cd bin
./GraphGame # Run the game
```

### Windows (MinGW)

The game can also be built on Windows using CMake:

1. Install dependencies:
   - Get SFML 3.0.0 from the official [SFML website](https://www.sfml-dev.org/download/sfml/3.0.0), 
      but note, the build requires SFML to be installed in `C:\SFML` with that exact name!
   - Install CMake (via winget: `winget install cmake` for example)

2. Build the game:
```bash
git clone --depth=1 https://github.com/itz-sqh/GraphGame # Clone repository
cd GraphGame
cmake -S . -B build -G "MinGW Makefiles" && cmake --build build # Configure and build
cd build/bin # that will generate .exe in build/bin
GraphGame.exe # Run the game
```
