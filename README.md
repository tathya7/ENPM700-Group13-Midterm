[![codecov](https://codecov.io/gh/mun0404/ENPM700-Group13-Midterm/graph/badge.svg?token=2W1XS59EG6)](https://codecov.io/gh/mun0404/ENPM700-Group13-Midterm)

# Midterm Project

ENPM808X - Mohammed Munawwar and Tathya Bhatt

# Human Detection and Avoidance

Phase 0 video: [Link](https://drive.google.com/file/d/1VtF8H3G0kN9BVF_SDWpRZ3BodRa7rdug/view?usp=sharing)<br>


## Standard install via command-line

```bash
# Download the code:
  git clone https://github.com/TommyChangUMD/cpp-boilerplate-v2
  cd cpp-boilerplate-v2
# Configure the project and generate a native build system:
  # Must re-run this command whenever any CMakeLists.txt file has been changed.
  cmake -S ./ -B build/
# Compile and build the project:
  # rebuild only files that are modified since the last build
  cmake --build build/
  # or rebuild everything from scracth
  cmake --build build/ --clean-first
  # to see verbose output, do:
  cmake --build build/ --verbose
# Run program:
  ./build/app/shell-app
# Run tests:
  cd build/; ctest; cd -
  # or if you have newer cmake
  ctest --test-dir build/
# Build docs:
  cmake --build build/ --target docs
  # open a web browser to browse the doc
  open docs/html/index.html
# Clean
  cmake --build build/ --target clean
# Clean and start over:
  rm -rf build/
```
