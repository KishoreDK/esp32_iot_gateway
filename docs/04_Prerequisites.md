# ESP32 IoT Gateway – Prerequisites

## 1. Purpose of This Document
This document lists all prerequisites required before starting development,
build, testing, or training with the ESP32 IoT Gateway project.

It is intended for **new users**, **students**, **trainers**, and **engineers**
who are setting up the environment from scratch.

---

## 2. Supported Operating Systems

The project supports development on the following operating systems:

- Windows 10 / Windows 11 (recommended for beginners)
- macOS (Intel or Apple Silicon)
- Linux (Ubuntu 20.04+ recommended)

> The ESP-IDF framework behaves consistently across platforms.

---

## 3. Hardware Prerequisites

### 3.1 Mandatory Hardware (Later Stage)
- ESP32 DevKit (30-pin or equivalent)
- USB cable (data capable)

> Hardware is **not required** for initial code development, build, and simulation.

---

### 3.2 Optional Hardware (Future Integration)
- Sensors (DHT, PIR, Gas, LDR, etc.)
- MCP3008 ADC
- Relay modules
- Servo motor
- CAN transceiver
- I2C LCD (16x2 / 20x4)

These are **not required** at the current stage.

---

## 4. Software Prerequisites

### 4.1 ESP-IDF Framework
- ESP-IDF version: **v5.x**
- Installed using official Espressif installer or setup scripts

ESP-IDF includes:
- Toolchain (Xtensa)
- Python environment
- Build system (CMake + Ninja)
- ESP-IDF components

---

### 4.2 Python
- Python 3.x (managed automatically by ESP-IDF)
- No separate Python installation required if ESP-IDF installer is used

---

### 4.3 Development Tools

Required tools:
- Visual Studio Code
- ESP-IDF VS Code Extension

Optional tools:
- Git (for version control)
- MQTT Explorer (for testing & visualization)
- Node-RED (for GUI simulation)

---

## 5. Knowledge Prerequisites

Before working on this project, users should have:

### 5.1 Mandatory Knowledge
- Basic C programming
- Basic understanding of:
  - Functions
  - Structures
  - Header/source files

---

### 5.2 Recommended Knowledge
- Basic ESP32 concepts
- MQTT fundamentals (publish / subscribe)
- JSON basics
- Embedded system workflow

> Deep protocol or hardware knowledge is **not required** initially.

---

## 6. Network Prerequisites

- Access to a Wi-Fi network
- Access to an MQTT broker:
  - Public broker (for testing)
  - Local broker (optional)

> Internet access is required only for installation and public MQTT usage.

---

## 7. Folder & Disk Requirements

- Minimum free disk space: **5–8 GB**
- Write permission to installation directories
- Stable filesystem (avoid network drives)

---

## 8. Environment Expectations

Before proceeding:
- ESP-IDF should be properly installed
- `idf.py` command should work in terminal
- VS Code should open projects from ESP-IDF environment

Verification command:
```
idf.py --version
```

---

## 9. What You Do NOT Need (At This Stage)

- Raspberry Pi
- Cloud account
- Custom hardware
- Paid tools
- External dashboards

These will be discussed later if required.

---

## 10. Next Document

Continue with:

📄 **05_Installation_Guide.md**

This document explains:
- ESP-IDF installation from scratch
- Environment setup
- Project build steps
- Common mistakes and fixes
