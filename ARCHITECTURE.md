# Firmware Architecture

## Objective

Provide a clear, modular, and testable architecture for embedded systems.

The design separates hardware-dependent code from portable logic to improve:

- maintainability
- testability
- scalability

---

## Layered Architecture

app ↓ services ↓ core ↓ drivers ↓ platform

Each layer has a single responsibility.

---

## Core

- Hardware-independent
- Fully testable on host
- No external dependencies

Examples:
- ringbuffer
- logger

---

## Services

- Business logic layer
- Uses core modules
- No direct hardware access

Example:
- sensor abstraction

---

## Drivers

- Low-level hardware access
- Encapsulates peripherals

Examples:
- UART
- GPIO

Constraints:
- no business logic
- minimal complexity

---

## Platform

- Target-specific implementation
- Not portable

Contains:
- startup code
- linker script
- interrupt handling
- hardware initialization

---

## App

- Entry point (`main.cpp`)
- Coordinates system behavior

---

## Data Flow

Input → Service → Core → Driver → Hardware

---

## Build Modes

### Firmware Mode

ANALYSIS=OFF

- Full build
- Includes platform and drivers
- Target: embedded device

---

### Analysis Mode

ANALYSIS=ON

Builds only:
- core
- services
- tests (optional)

Used for:
- unit testing
- clang-tidy
- cppcheck
- CodeQL

---

## Testing Strategy

- Scope: core and services
- Executed on host
- Independent from hardware

Benefits:
- fast execution
- deterministic results
- CI-friendly

---

## Static Analysis Strategy

| Tool       | Scope                  |
|------------|------------------------|
| clang-tidy | core, services         |
| cppcheck   | core, services, tests  |
| CodeQL     | core, services         |

---

## Key Design Choices

### Separation of concerns

- Core does not depend on drivers
- Services do not access hardware directly
- Platform is isolated

### Hardware abstraction

- Drivers isolate hardware details
- Higher layers remain portable

### Testability

- Most code runs without hardware
- Enables CI integration

---

## Summary

This architecture ensures:

- clean structure
- strong testability
- portability
- readiness for industrial workflows


---