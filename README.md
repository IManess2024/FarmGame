# SFML Template

Minimal SFML project with:

- `main.cpp`
- `CMakeLists.txt`
- automatic SFML download through CMake `FetchContent`

## Requirements

- CMake 3.28 or newer
- a C++17 compiler
- Git

On Linux, SFML also needs system packages. The official SFML docs recommend installing the required development packages first.

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run

On macOS or Linux:

```bash
./build/bin/sfml_template
```

On Windows:

```powershell
.\build\bin\Debug\sfml_template.exe
```

## Notes

- SFML is fetched from `https://github.com/SFML/SFML.git`
- This template is pinned to SFML `3.1.0`
- To use more SFML modules later, add them in `target_link_libraries(...)`

## References

- SFML CMake template tutorial: https://www.sfml-dev.org/tutorials/3.0/getting-started/cmake/
- Official SFML CMake template repo: https://github.com/SFML/cmake-sfml-project
