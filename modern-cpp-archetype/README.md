# Modern C++ Application Archetype

A modern C++ application template using vcpkg for dependency management and CMake for building.

## Features

- Modern C++20 standard
- vcpkg for package management
- CMake build system
- Pre-configured DevContainer for development
- VSCode integration with tasks and debugging
- Example dependencies (fmt, spdlog)

## Prerequisites

- Docker (for DevContainer)
- Visual Studio Code with Remote-Containers extension
- OR: CMake 3.20+, C++20 compiler, and vcpkg

## Quick Start

### Using DevContainer (Recommended)

1. Open the project in Visual Studio Code
2. Click "Reopen in Container" when prompted
3. Wait for the container to build
4. Run the build task: `Ctrl+Shift+B` or `Cmd+Shift+B`

### Manual Build

1. Install vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=/path/to/vcpkg
```

2. Configure and build:
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -GNinja
cmake --build build
```

3. Run the application:
```bash
./build/ModernCppApplication
```

## Project Structure

```
modern-cpp-archetype/
├── .devcontainer/          # DevContainer configuration
│   ├── devcontainer.json   # VSCode DevContainer settings
│   └── Dockerfile          # Container definition
├── .vscode/                # VSCode configuration
│   ├── settings.json       # Editor settings
│   ├── tasks.json          # Build tasks
│   └── launch.json         # Debug configuration
├── include/                # Header files
├── src/                    # Source files
│   └── main.cpp           # Application entry point
├── CMakeLists.txt         # CMake build configuration
├── vcpkg.json             # vcpkg manifest file
├── .gitignore             # Git ignore patterns
├── LICENSE                # MIT License
└── README.md              # This file
```

## Adding Dependencies

To add new dependencies, edit `vcpkg.json`:

```json
{
  "dependencies": [
    "fmt",
    "spdlog",
    "boost-asio"  // Add new dependency here
  ]
}
```

Then update `CMakeLists.txt` to find and link the package:

```cmake
find_package(Boost REQUIRED COMPONENTS asio)
target_link_libraries(ModernCppApplication PRIVATE Boost::asio)
```

## Development

### Building

Use the VSCode task `CMake: Build` or run:
```bash
cmake --build build
```

### Debugging

Press `F5` in VSCode or use the Debug panel to start debugging.

### Cleaning

Use the VSCode task `CMake: Clean` or run:
```bash
cmake --build build --target clean
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

Sergio Martínez (@Neirth)
