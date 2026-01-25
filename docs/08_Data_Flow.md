# ESP32 IoT Gateway – Data Flow

## 1. Purpose of This Document

This document explains the **end-to-end data flow** inside the ESP32 IoT Gateway firmware.
It focuses on:
- How data moves between modules
- Timing and execution sequence
- Bidirectional flow (data publish and command receive)
- Error and edge-case handling

This document is ESP32-side only.

---

## 2. High-Level Data Flow Overview

The ESP32 IoT Gateway handles **two primary data flows**:

1. **Upstream Flow** – Sensor data sent from ESP32 to external systems
2. **Downstream Flow** – Command data sent from external systems to ESP32

Both flows operate independently but share the same MQTT infrastructure.

---

## 3. Upstream Data Flow (ESP32 → MQTT)

### 3.1 Logical Flow

```
[ Sensors ]
     ↓
[ sensors_read_all() ]
     ↓
[ sensor_data_t structure ]
     ↓
[ payload_build() ]
     ↓
[ JSON string ]
     ↓
[ mqtt_publish() ]
     ↓
[ MQTT Broker ]
     ↓
[ External Subscribers ]
```

---

### 3.2 Step-by-Step Explanation

1. **Sensor Sampling**
   - `sensors_read_all()` is called periodically
   - Digital, analog, and bus-based sensors are read
   - In current stage, values are simulated

2. **Data Aggregation**
   - All sensor values are stored in a single `sensor_data_t` structure
   - Ensures consistency across payloads

3. **Payload Construction**
   - `payload_build()` converts sensor data into structured JSON
   - Adds:
     - Device ID
     - Uptime
     - System status

4. **MQTT Publish**
   - JSON payload is published to the configured MQTT topic
   - QoS ensures reliable delivery
   - Memory is freed after publish

---

## 4. Downstream Data Flow (MQTT → ESP32)

### 4.1 Logical Flow

```
[ External Publisher ]
          ↓
[ MQTT Broker ]
          ↓
[ MQTT Subscribe Callback ]
          ↓
[ JSON Validation ]
          ↓
[ Actuator Command Parsing ]
          ↓
[ execute_actuator_command() ]
```

---

### 4.2 Step-by-Step Explanation

1. **Command Publish**
   - External system publishes command JSON to subscribe topic

2. **MQTT Reception**
   - ESP32 MQTT client receives message asynchronously
   - Callback is triggered by ESP-IDF event loop

3. **JSON Parsing & Validation**
   - Payload is parsed using `cJSON`
   - Required fields are validated
   - Invalid messages are discarded safely

4. **Command Routing**
   - Command target and action are extracted
   - Routed to actuator abstraction layer

5. **Actuator Execution**
   - Actuator handler logs or executes action
   - Real hardware drivers can be added later

---

## 5. Timing & Execution Model

### 5.1 Main Loop Timing

- Data publishing is **periodic**
- Interval is configurable via `menuconfig`

Example:
```
Publish interval = 1000 ms
```

---

### 5.2 Asynchronous Command Handling

- MQTT command reception is **event-driven**
- Commands can arrive at any time
- Command handling does not block sensor publishing

---

## 6. Error Handling in Data Flow

### 6.1 Sensor Errors
- Sensor failures are isolated
- Missing values do not crash the system
- Defaults or last-known values can be used

---

### 6.2 Payload Errors
- JSON build failures are detected
- Publishing is skipped safely
- Errors are logged

---

### 6.3 MQTT Errors
- Publish failures are logged
- Reconnection handled automatically
- No blocking behavior in main loop

---

## 7. Memory Safety in Data Flow

- JSON strings are dynamically allocated
- Memory is freed immediately after use
- No long-lived heap allocations in loop
- Prevents memory fragmentation

---

## 8. Data Flow Scalability

The current design supports:
- Adding new sensors without payload rewrite
- Adding new actuators without MQTT changes
- Multiple ESP32 devices using unique device IDs
- Future cloud or database integration

---

## 9. Example End-to-End Scenario

### Example: Sensor Update

1. ESP32 reads temperature = 26°C
2. JSON payload created
3. Payload published to MQTT
4. External system receives and displays data

---

### Example: Actuator Command

1. User sends:
```json
{
  "device_id": "esp32-gateway-01",
  "command": {
    "target": "relay",
    "action": "on"
  }
}
```
2. ESP32 receives command
3. Command parsed and validated
4. Relay handler invoked

---

## 10. Summary

- Data flow is clean and predictable
- Upstream and downstream flows are independent
- MQTT acts as the central message bus
- Design is robust, testable, and extensible

---

## 11. Next Document

Continue with:

📄 **09_Testing_And_Simulation.md**

This document explains:
- How to simulate sensors
- How to test MQTT communication
- How to visualize data using GUI tools
- How to test bidirectional flow without hardware
