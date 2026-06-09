# Architecture

## Objective

Provide a maintainable and testable firmware architecture for STM32-based systems.

The architecture isolates hardware-specific code from portable application logic.

---

## Layer Overview

```text
app
 ↓
services
 ↓
core
 ↓
drivers
 ↓
platform
```

Each layer has a single responsibility.

---

## App

System entry point.

Responsibilities:

- system startup
- initialization
- application orchestration

Files:

```text
firmware/app/
```

---

## Services

Application-specific behavior.

Responsibilities:

- business logic
- use case implementation
- coordination between modules

Examples:

```text
sensor/
```

Rules:

- no register access
- no STM32 dependencies

---

## Core

Portable building blocks.

Responsibilities:

- reusable algorithms
- utility modules
- generic components

Examples:

```text
logger/
ringbuffer/
```

Rules:

- fully platform independent
- host testable

---

## Drivers

Peripheral abstraction layer.

Responsibilities:

- UART
- GPIO
- peripheral access

Examples:

```text
gpio/
uart/
```

Rules:

- no business logic
- minimal abstraction cost

---

## Platform (STM32F072)

STM32-specific implementation.

Responsibilities:

- startup code
- CMSIS integration
- clock configuration
- interrupt handling
- linker configuration

Structure:

```text
platform/stm32f072/
├── startup/
├── linker/
├── cmsis/
├── clock.cpp
└── interrupt.cpp
```

Contains:

- startup_stm32f072xb.s
- STM32F072RBTx_FLASH.ld
- CMSIS Core
- STM32 device headers

---

## Dependency Rules

Allowed:

```text
app      → services
services → core
drivers  → platform
```

Forbidden:

```text
core     → drivers
core     → platform

services → platform
services → registers

app      → registers
```

---

## Build Modes

### Firmware

```text
ANALYSIS=OFF
```

Builds:

- app
- services
- core
- drivers
- platform

Target:

- STM32F072

---

### Analysis

```text
ANALYSIS=ON
```

Builds:

- core
- services
- tests

Used by:

- GoogleTest
- clang-tidy
- cppcheck
- CodeQL

---

## Testing Strategy

Host-based testing.

Scope:

- core
- services

Benefits:

- fast execution
- deterministic results
- hardware-independent validation

---

## Quality Strategy

Static analysis:

| Tool | Purpose |
| -------- | ---------- |
| clang-format | formatting |
| clang-tidy | code quality |
| cppcheck | bug detection |
| CodeQL | security analysis |

CI automatically executes all checks.

---

## Summary

This architecture provides:

- clear separation of layers
- high testability
- STM32 isolation
- scalable firmware development
- CI/CD readiness
- security-oriented workflow
