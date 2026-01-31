# AGENTS.md - NEOws C++ Project Guide

This document provides essential information for agentic coding agents working on the NEOws (NASA Near Earth Object Web Service) C++ visualization project.

## Build System Commands

This project uses CMake with Catch2 for testing and C++23 standard.

### Essential Build Commands
```bash
# Configure and build the project
cmake -B build -S .
cmake --build build

# Alternative: Use make directly (if already configured)
make -j$(nproc)

# Clean build artifacts
make clean
# or
rm -rf build
```

### Test Commands
```bash
# Run all tests
make test
# or
ctest

# Run tests with verbose output
ctest -V

# Run specific test by name
ctest -R "Test Name"

# Run specific test by number
ctest -I ,,1  # Run test #1 only
ctest -I ,,2  # Run test #2 only

# Run tests and show output on failure
ctest --output-on-failure

# Available tests:
# Test #1: Santiy Check
# Test #2: Asteroid Position
```

### Build Targets
```bash
# Build main executable
make Main

# Build test executable
make Tests

# Build all targets
make all
```

## Code Style Guidelines

### File Organization
- **Source files**: Located in `src/` directory with appropriate subdirectories
- **Header files**: Co-located with corresponding `.cpp` files
- **Tests**: Located in `tests/` directory
- **External dependencies**: Managed via CMake FetchContent (nlohmann/json, raylib, cpp-httplib, catch2)

### Naming Conventions
- **Classes**: PascalCase (e.g., `Neo`, `NeosCurrier`, `Menu`)
- **Functions**: PascalCase for public methods (e.g., `SetID()`, `GetRenderPosition()`)
- **Variables**: snake_case for member variables (e.g., `render_index`, `window_size`)
- **Private members**: snake_case with no prefix (e.g., `position`, `render_radius`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `Minimal`, `Full` for enum values)

### Import/Include Style
```cpp
// #pragma once for header guards
#pragma once

// System includes first, sorted alphabetically
#include <memory>
#include <string>
#include <vector>

// External library includes next
#include <raylib.h>
#include <nlohmann/json.hpp>

// Local includes last, use relative paths
#include "CloseApproach.hpp"
#include "Diameter.hpp"
```

### Formatting and Indentation
- **Indentation**: 2 spaces (no tabs)
- **Brace style**: Allman style (braces on new line)
- **Line length**: Prefer under 120 characters
- **Spacing**: Single space around operators, after commas, before opening braces

### Type System
```cpp
// Use modern C++ types
#include <cstdint>
int64_t id;          // For JSON IDs
std::string name;    // For strings
std::unique_ptr<T> ptr;  // For ownership
std::shared_ptr<T> shared;  // For shared ownership
std::vector<T> collection; // For collections

// Use const references for getters
const std::string &GetName() const;
const Vector3 &GetRenderPosition() const;

// Use std::optional for nullable values (when implemented)
std::optional<Diameter> GetDiameter() const;
```

### Error Handling
```cpp
// Use exceptions for error conditions
if (ivalue < std::numeric_limits<int>::min() || 
    ivalue > std::numeric_limits<int>::max()) {
    throw std::runtime_error("ID is out of range");
}

// Use bounds checking with .at() for vector access
return this->neos.at(this->render_index);

// Use null checks for pointers
if (!model || model->meshCount == 0) {
    std::cerr << "Failed to load model!" << std::endl;
    return -1;
}
```

### Memory Management
```cpp
// Prefer smart pointers over raw pointers
std::unique_ptr<Diameter> diameter;
std::vector<std::unique_ptr<CloseApproach>> close_approach;

// Use std::shared_ptr for shared ownership
std::shared_ptr<Neo> currentNeo;

// Avoid manual new/delete in modern code
```

### Function Design
```cpp
// Use descriptive PascalCase function names
void SetRenderPosition(Vector3 position);
void DrawNeos();
void UpdateNeosPosition(double time, float startTime, double angleRadians);

// Getters should be const where possible
const std::string &GetName() const;
float GetRenderRadius() const;

// Use references for large objects to avoid copies
void DisplayMinimalMenu(const std::shared_ptr<Neo> &currentNeo);
```

## Project-Specific Guidelines

### File Access Policy
**CRITICAL**: Agents have different access levels based on file type:

- **🔒 READ-ONLY FILES**: All source code files (`.cpp`, `.hpp`) are READ-ONLY
  - Agents can read but cannot directly edit source files
  - Any proposed code changes must be presented to the user for review and approval
  - No automatic code generation or modification without explicit user consent

- **📝 EDITABLE FILES**: Markdown documents (`.md`) are fully editable by agents
  - Agents can freely read, edit, and modify documentation files
  - Includes `README.md`, `PROJECT_ISSUES.md`, `AGENTS.md`, etc.
  - Documentation updates can be made autonomously without user approval

### Hand-Critten Code Policy
**IMPORTANT**: This project is exclusively hand-written code. The source code (`.cpp`, `.hpp`) files are maintained by human developers only. Agents should:
1. **Analyze** source code for issues, patterns, and improvements
2. **Propose** changes through markdown documentation updates
3. **Present** specific code modifications to the user for consideration
4. **Never** directly edit `.cpp` or `.hpp` files without explicit permission

### NASA API Integration
- API key should be loaded from `.env` file
- Use cpp-httplib for HTTP requests
- Implement proper error handling and timeouts
- API integration currently commented out in main.cpp

### Rendering Pipeline
- Uses raylib for 3D graphics
- Main executable: `Main` target
- Asteroid models loaded from `assets/Asteroid.glb`
- 60 FPS target with `SetTargetFPS(60)`

### Testing Strategy
- Use Catch2 testing framework
- Test executable: `Tests` target
- Current tests are placeholder - need comprehensive unit tests
- Test naming: `[flag]` tags for categorization

### Dependencies via CMake
```cmake
# External libraries managed via FetchContent
- nlohmann/json (v3.11.3)
- cpp-httplib (v0.18.1) 
- raylib (master branch)
- catch2 (v3.7.1)
```

### Compiler Settings
- **C++ Standard**: C++23
- **Compiler warnings**: `-Wall -Werror -fdiagnostics-color=always`
- **Build type**: Configure with `-DCMAKE_BUILD_TYPE=Debug` for development

### Code Review Checklist
- [ ] All includes properly ordered
- [ ] Smart pointers used correctly
- [ ] Error handling implemented
- [ ] Memory safety verified
- [ ] Tests pass
- [ ] Code follows naming conventions
- [ ] No commented-out code left in final implementation

### Common Patterns to Follow
```cpp
// JSON parsing with error checking
void SetID(nlohmann::json &id_json) {
    using integer = nlohmann::json::number_integer_t;
    auto ivalue = id_json.get<integer>();
    if (ivalue < std::numeric_limits<int>::min() || 
        ivalue > std::numeric_limits<int>::max()) {
        throw std::runtime_error("ID is out of range");
    }
    this->id = id_json.get<int64_t>();
}

// Bounds-checked vector access
std::shared_ptr<Neo> &GetSelectedNeo() {
    return this->neos.at(this->render_index);
}

// Resource loading with error checking
Model asteroidModel = LoadModel("assets/Asteroid.glb");
if (asteroidModel.meshCount == 0) {
    std::cerr << "Failed to load asteroid model!" << std::endl;
    return -1;
}
```

## Development Workflow

1. **Before making changes**: Run `make test` to ensure existing tests pass
2. **After making changes**: Build with `make Main && make Tests`
3. **Test your changes**: Run `ctest -V` for verbose test output
4. **Style check**: Ensure code follows the guidelines above
5. **Present to user**: All code changes must be approved before commit

Remember: This is a hand-crafted C++ project. Prioritize code quality, safety, and maintainability over rapid development.