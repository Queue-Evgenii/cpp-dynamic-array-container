# DynamicArray (C++)

A simple, self-implemented dynamic array (similar to `std::vector`) in C++, designed for learning and extensibility purposes.

## ✨ Features

- Dynamic resizing with automatic capacity doubling
- Basic array operations:
  - `push` / `pop`
  - `unshift` / `shift`
  - `find` / `findIndex`
- Copy/move constructors and assignment operators
- Bounds-checked access via `operator[]`
- Template-based for any data type

## 📁 Project Structure
```text
.
├── src/
│ ├── main.cpp # Example usage and test
│ ├── array.h # Array class (templated)
├── Makefile # For building the project
├── Dockerfile # For building the project
└── README.md
```

## 🛠️ Build & Run

### 🔧 Native (on your system)

```bash
make
./app
```

### 🐳 With Docker

```bash
docker build -t dynamic-array .
docker run --rm dynamic-array
```