# ESP32 IoT Gateway – System Architecture

## 1. Overview
This document explains the overall system architecture of the ESP32 IoT Gateway firmware.
It describes how different software modules interact, how data flows through the system,
and how the design supports scalability, testing, and future expansion.

---

## 2. High-Level Architecture

At a high level, the ESP32 IoT Gateway works as an edge device that connects
sensors and actuators to an MQTT-based communication layer.

```
+--------------------+
|   Sensors Layer    |
| (Digital / Analog) |
+---------+----------+
          |
          v
+--------------------+
|  Sensor Abstraction|
|  (sensors module)  |
+---------+----------+
          |
          v
+--------------------+
|  Payload Builder   |
|  (JSON creation)   |
+---------+----------+
          |
          v
+--------------------+
|     MQTT Client    |
| (Publish / Subscr) |
+----+----------+----+
     |          |
     v          v
External     Actuator
Systems      Abstraction
             (Commands)
```

---

## 3. Core Software Layers

### 3.1 Application Layer (`app_main.c`)
- Entry point of the firmware
- Controls initialization sequence
- Periodically triggers sensor reads
- Publishes data over MQTT
- Dispatches received commands

---

### 3.2 Networking Layer
#### Wi-Fi Module
- Handles Wi-Fi initialization
- Manages connection and reconnection
- Provides network availability for MQTT

#### MQTT Module
- Manages MQTT client lifecycle
- Publishes JSON sensor data
- Subscribes to command topics
- Forwards commands to actuator layer

---

### 3.3 Data Layer
#### Sensor Abstraction
- Collects data from all sensors
- Provides a unified data structure
- Supports mock data for simulation

#### Payload Builder
- Converts sensor data into structured JSON
- Adds device metadata and system status
- Ensures consistent data format

---

### 3.4 Actuator Layer
- Receives parsed command objects
- Routes commands based on target type
- Abstracts hardware control logic
- Supports future GPIO / PWM drivers

---

### 3.5 Protocol Layer
- Provides scaffolding for:
  - I2C
  - SPI
  - CAN (TWAI)
  - UART
- Keeps protocol initialization separate from logic
- Allows selective enablement via menuconfig

---

## 4. Configuration Architecture

- Uses ESP-IDF `menuconfig`
- Centralizes all configurable parameters:
  - Device ID
  - MQTT broker URI
  - Topics
  - Publish interval
  - Protocol enable flags
- Avoids hardcoded values in source code

---

## 5. Execution Flow

### 5.1 System Startup
1. ESP32 boots
2. `app_main()` is called
3. Wi-Fi initialization
4. MQTT initialization
5. Protocol scaffolding initialization

---

### 5.2 Periodic Data Flow
1. Sensors are read (mock or real)
2. Data stored in a unified structure
3. JSON payload is built
4. Payload published via MQTT
5. System waits for next cycle

---

### 5.3 Command Flow (Bidirectional)
1. MQTT command received
2. JSON command validated
3. Command parsed into internal structure
4. Actuator handler executes action
5. Status logged

---

## 6. Scalability & Extension Points

- New sensors can be added in `sensors` module
- New actuators can be added in `actuators` module
- New protocols can be implemented under `protocols`
- Payload structure can be extended without breaking compatibility

---

## 7. Design Goals Recap

- Modular and maintainable
- Hardware-agnostic during development
- Testable without physical devices
- Suitable for training and PoC usage
- Ready for future production enhancement

---

## 8. Next Document

Continue with:

**04_Prerequisites.md**

This document explains:
- Software requirements
- Toolchains
- System prerequisites
- Knowledge expectations
