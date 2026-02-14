# Native C++ Library

A simple C++ library with CMake build system demonstrating native code compilation.

## Features

- Modern C++17
- CMake build system
- Simple calculator library
- Automated testing

## Building

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Run demo
./demo

# Run tests
ctest
```

## Library API

The library provides a simple Calculator class with basic operations:
- `add(a, b)` - Addition
- `subtract(a, b)` - Subtraction
- `multiply(a, b)` - Multiplication
- `divide(a, b)` - Division
