# ESP32 IoT Gateway – Project Structure

## 1. Purpose of This Document

This document explains the **project folder structure** of the ESP32 IoT Gateway firmware.
It is intended to help new developers, students, and trainers quickly understand:

- Where each feature is implemented
- How modules are separated
- Where to add new functionality safely

The structure follows **ESP-IDF best practices** and real-world firmware organization.

---

## 2. Top-Level Directory Structure

```
esp32_iot_gateway/
├── CMakeLists.txt
├── sdkconfig
├── sdkconfig.defaults
├── main/
│   ├── app_main.c
│   ├── CMakeLists.txt
│   ├── Kconfig
│   ├── wifi/
│   ├── mqtt/
│   ├── sensors/
│   ├── payload/
│   ├── actuators/
│   └── protocols/
└── docs/
```

---

## 3. Top-Level Files Explained

### 3.1 `CMakeLists.txt`
- Root build configuration file
- Tells ESP-IDF how to build the project
- Should rarely be modified

---

### 3.2 `sdkconfig`
- Auto-generated configuration file
- Created when `menuconfig` is saved
- **Do not edit manually**

---

### 3.3 `sdkconfig.defaults`
- Optional default configuration values
- Used to pre-load menuconfig settings
- Helpful for training and mass deployment

---

## 4. `main/` Directory (Core Firmware)

The `main/` folder contains **all application logic**.

---

### 4.1 `app_main.c`
- Entry point of the firmware
- Contains `app_main()`
- Responsibilities:
  - System initialization
  - Periodic task execution
  - High-level control flow

> This file should remain clean and short.

---

### 4.2 `Kconfig`
- Defines custom menuconfig options
- Allows runtime configuration without code changes
- Examples:
  - Device ID
  - MQTT broker
  - Publish interval
  - Protocol enable/disable flags

---

### 4.3 `main/CMakeLists.txt`
- Lists source files for compilation
- Registers include directories
- Must be updated when new modules are added

---

## 5. Module-Level Structure

Each module follows the pattern:

```
module_name/
├── module_name.c
└── module_name.h
```

---

### 5.1 `wifi/`
**Purpose:** Network connectivity

- Initializes Wi-Fi in STA mode
- Handles reconnection logic
- Abstracts ESP-IDF Wi-Fi APIs

Additions:
- Advanced Wi-Fi handling
- Credential management

---

### 5.2 `mqtt/`
**Purpose:** Messaging layer

- Initializes MQTT client
- Publishes JSON payloads
- Subscribes to command topics
- Routes commands to actuators

Additions:
- TLS support
- Broker failover
- QoS tuning

---

### 5.3 `sensors/`
**Purpose:** Sensor abstraction

- Collects all sensor data
- Returns unified sensor structure
- Currently mock-based

Additions:
- DHT drivers
- ADC (MCP3008) drivers
- I2C/SPI/CAN sensor drivers

---

### 5.4 `payload/`
**Purpose:** Data formatting

- Builds structured JSON payloads
- Adds metadata and status
- Ensures consistent format

Additions:
- Payload compression
- Versioning
- Encryption hooks

---

### 5.5 `actuators/`
**Purpose:** Command-based control

- Parses incoming command JSON
- Routes commands to actuator handlers
- Hardware logic abstracted

Additions:
- GPIO drivers
- PWM logic
- Servo control

---

### 5.6 `protocols/`
**Purpose:** Communication bus scaffolding

Contains:
- `i2c_bus`
- `spi_bus`
- `can_bus`
- `uart_bus`

Responsibilities:
- Bus initialization
- Protocol separation
- Hardware readiness

Additions:
- Real driver installs
- Error handling
- Bus multiplexing

---

## 6. `docs/` Directory

Contains all project documentation:

```
docs/
├── 01_Project_Overview.md
├── 02_Features.md
├── 03_System_Architecture.md
├── 04_Prerequisites.md
├── 05_Installation_Guide.md
├── 06_Project_Structure.md
├── 07_MQTT_Communication.md
├── 08_Data_Flow.md
├── 09_Testing_And_Simulation.md
└── 10_Hardware_Integration.md
```

Each document focuses on **one concern only**, reducing confusion.

---

## 7. Where to Add New Code (Guidelines)

| Task | Location |
|----|----|
| New sensor | `main/sensors/` |
| New actuator | `main/actuators/` |
| New protocol | `main/protocols/` |
| Change payload format | `main/payload/` |
| Change timing / flow | `app_main.c` |
| New configuration | `main/Kconfig` |

---

## 8. Design Rules to Follow

- Do not mix hardware code with MQTT logic
- Do not hardcode configuration values
- Keep `app_main.c` minimal
- Use abstraction layers
- Update documentation when adding modules

---

## 9. Next Document

Continue with:

📄 **07_MQTT_Communication.md**

This document explains:
- MQTT topics
- Payload direction
- Command structure
- Expected sender/receiver behavior
