# STM32 Tuto PoMad

Implementation of the series of PoMad tutorials to get familiar with STM32 micro-controller architecture and programming adapted to my firmware architecture and available tools.

---

## Purpose

This project provides a solid foundation to build reliable embedded systems with STM32.

Key goals:

- Separate business logic from hardware
- Enable fast and reproducible testing
- Improve code quality with static analysis
- Support scalable and maintainable design

---

## Project Structure

```
. ├── firmware/
  |   ├── app/        # Entry point (main)  
  |   ├── core/       # Hardware-independent modules
  |   │   ├── logger/
  |   │   ├── ringbuffer/
  |   │   └── utils/
  |   ├── services/   # Business logic 
  |   │   └── sensor/ 
  |   ├── drivers/    # Hardware interfaces
  |   │   ├── gpio/
  |   │   └── uart/
  |   └── platform/   # Target-specific implementation
  |       └── stm32f072/ 
  |           ├── startup/ 
  |           ├── linker/ 
  |           ├── cmsis/ 
  |           └── clock / interrupt 
  ├── tests/          # Unit tests (host execution) 
  ├── scripts/        # Build, analysis and tooling scripts
  └── cmake/          # Toolchain configuration
```

---

## Build

### Firmware (cross-compilation)

```bash
./scripts/build.sh
```

Outputs:  

  - .elf
  - .bin
  - .hex

---

### Tests (host)

```bash
cmake -B build/tests -DANALYSIS=ON -DTESTS=ON
cmake --build build/tests
ctest --test-dir build/tests
```

Testing:

  - Framework: GoogleTest  
  - Scope: core and services  
  - Runs on host (no hardware required)  

---

### Static Analysis

#### clang-tidy

```bash
./scripts/clang-tidy.sh
```

Scope:

  - core
  - services

#### cppcheck

```bash
./scripts/cppcheck.sh
```

Scope:

  - core
  - services
  - tests

---

### CodeQL

```bash
./scripts/codeql.sh
```

Focus:

  - security vulnerabilities
  - memory issues
  - unsafe patterns

---

### CI/CD

GitHub Actions pipeline includes:

#### Analysis job

  - clang-tidy
  - cppcheck
  - unit tests (ASAN / UBSAN)

#### Firmware job

  - cross-compilation
  - generation of .elf, .bin, .hex

#### CodeQL job

  - advanced security analysis
  - Caching is used to speed up builds.

---

## Development Workflow

### Format code

```bash
./scripts/clang-format.sh
```

### Run all static analysis

```bash
./scripts/static_analysis.sh
```

### Run tests

```bash
ctest --test-dir build/tests
```

---

## Design Principles

- Clear separation of layers
- Hardware-independent core logic
- Minimal coupling
- Testability first
- Static analysis integration

---

## Roadmap

  - Power optimization strategies
  - Communication stack integration
  - RTOS support
  - Security improvements

---

## License

MIT

---