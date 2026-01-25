# ESP32 IoT Gateway – Features

## 1. Overview

This document describes the **functional features** of the ESP32 IoT Gateway firmware.

The firmware is intentionally designed to:
- Be **modular**
- Be **hardware-agnostic initially**
- Support **training, lab experiments, and PoCs**
- Scale toward **industrial-style IoT gateways**

Features are categorized as:
- Implemented (fully functional in code)
- Scaffolded (structure ready, hardware logic to be added later)

---

## 2. Core System Features

### 2.1 ESP-IDF Native Implementation

- Built entirely using **ESP-IDF (v5.x)**
- No Arduino framework
- Uses native ESP-IDF APIs for:
  - Wi-Fi
  - MQTT
  - FreeRTOS
  - Logging
  - menuconfig

This makes the project:
- Production-aligned
- Stable for long-running use
- Suitable for professional environments

---

### 2.2 Modular Firmware Architecture

The firmware is divided into logical modules:

- Wi-Fi management
- MQTT communication
- Sensor abstraction
- Actuator abstraction
- Protocol buses (I2C, SPI, CAN, UART)
- Payload construction (JSON)
- Configuration (menuconfig)

Each module:
- Has its own `.c` and `.h`
- Can be developed or replaced independently
- Does not directly depend on application logic

---

## 3. Networking & Communication Features

### 3.1 Wi-Fi (Station Mode)

**Status:** ✅ Implemented

- ESP32 connects as a Wi-Fi client (STA mode)
- Uses ESP-IDF event-driven Wi-Fi APIs
- Automatically reconnects on disconnection
- Wi-Fi credentials can be moved to menuconfig later

---

### 3.2 MQTT Communication

**Status:** ✅ Implemented

- Native ESP-IDF MQTT client
- Supports:
  - Publish (ESP32 → external systems)
  - Subscribe (external systems → ESP32)
- Fully bidirectional communication
- QoS configurable in code

MQTT is used as the **only communication backbone**, making the system:
- Lightweight
- Scalable
- Easy to integrate with cloud, local servers, or dashboards

---

## 4. Data Handling Features

### 4.1 JSON-Based Data Exchange

**Status:** ✅ Implemented

- All sensor data is packaged in **structured JSON**
- Uses `cJSON` (official ESP-IDF component)
- Clear separation of:
  - Device metadata
  - Sensor data
  - System status

Benefits:
- Language-independent
- Easy parsing on receivers
- Extensible without breaking compatibility

---

### 4.2 Structured Payload Design

Current payload structure includes:
- Device ID
- Uptime
- Sensor readings
- Wi-Fi and MQTT status

This design supports:
- Dashboards
- Databases
- Analytics pipelines
- Multi-device deployments

---

## 5. Sensor Features

### 5.1 Sensor Abstraction Layer

**Status:** ✅ Implemented (Mocked)

Sensors are not accessed directly by application code.
Instead, all sensor reads go through:
sensors_read_all()


This abstraction allows:
- Simulation without hardware
- Easy replacement with real drivers later
- Clean separation from MQTT and JSON logic

---

### 5.2 Supported Sensor Types (Logical)

#### Digital Sensors
- Temperature & Humidity (DHT11 / DHT22)
- PIR motion sensor
- Reed switch (door sensor)
- Flame sensor
- Rain sensor

#### Analog Sensors (via ADC / MCP3008)
- Soil moisture sensor
- LDR (light sensor)
- Gas sensor
- Sound sensor
- Potentiometer

#### Bus-Based Sensors (Planned)
- I2C sensors
- SPI sensors
- CAN-based industrial nodes

At this stage:
- Values are **simulated**
- Interfaces are **ready**
- No hardware dependency exists

---

## 6. Actuator Features

### 6.1 Actuator Abstraction

**Status:** ✅ Implemented (Command-driven)

Actuators are controlled exclusively through **JSON commands** received via MQTT.

Supported actuator types:
- LED
- Relay
- Buzzer
- DC Motor / Fan
- Servo motor

---

### 6.2 Command-Based Control

Actuators are controlled using a standard JSON schema:

```json
{
  "device_id": "esp32-gateway-01",
  "command": {
    "target": "relay",
    "action": "on",
    "value": 0
  }
}

Benefits:

No direct GPIO logic in MQTT layer

Clean command routing

Easy future expansion

7. Protocol Support
7.1 I2C Bus

Status: 🟡 Scaffolded

Framework in place

Intended for:

LCD (16x2 / 20x4)

I2C sensors

Hardware pins to be defined later

7.2 SPI Bus

Status: 🟡 Scaffolded

Framework in place

Intended for:

MCP3008 ADC

SPI sensors

Device attachment pending

7.3 CAN (TWAI)

Status: 🟡 Scaffolded

Uses ESP32 native TWAI driver

Intended for industrial CAN nodes

Requires external transceiver hardware

7.4 UART

Status: 🟡 Scaffolded

Intended for:

External modules

Debug or CLI interfaces

Ready for expansion

8. Configuration Features
8.1 menuconfig Integration

Status: ✅ Implemented

Configurable parameters include:

Device ID

MQTT broker URI

Publish & subscribe topics

Publish interval

Protocol enable/disable flags

This allows:

Same firmware for multiple deployments

Easy customization without code changes

9. Reliability & Safety Features

Heap-safe JSON handling

No memory leaks

Defensive NULL checks

Log-level consistency

Long-running stability

These features make the firmware suitable for:

24×7 operation

Lab environments

Field PoCs

10. Feature Summary Table
Feature Area	Status
ESP-IDF Native	✅ Implemented
Wi-Fi	✅ Implemented
MQTT	✅ Implemented
JSON Payload	✅ Implemented
Sensor Abstraction	✅ Implemented (Mock)
Actuator Control	✅ Implemented (Mock)
I2C	🟡 Scaffolded
SPI	🟡 Scaffolded
CAN (TWAI)	🟡 Scaffolded
UART	🟡 Scaffolded
menuconfig	✅ Implemented