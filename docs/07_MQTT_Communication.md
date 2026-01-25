# ESP32 IoT Gateway – MQTT Communication

## 1. Purpose of This Document

This document explains the **MQTT communication design** used by the ESP32 IoT Gateway.
It defines:
- MQTT roles and responsibilities
- Topic structure
- Payload direction
- Message formats
- Error-handling expectations

This document is **ESP32-focused** and does not include receiver-side code.

---

## 2. Why MQTT Is Used

MQTT is chosen because it is:
- Lightweight
- Event-driven
- Widely supported
- Suitable for constrained devices like ESP32

MQTT enables:
- Loose coupling between ESP32 and receivers
- Easy integration with local or cloud systems
- Bidirectional communication

---

## 3. MQTT Roles in This Project

### 3.1 ESP32 Role
The ESP32 acts as:
- **MQTT Publisher** (sensor & status data)
- **MQTT Subscriber** (control commands)

### 3.2 External Systems Role
External systems (dashboard, server, cloud) act as:
- **MQTT Subscribers** (to receive data)
- **MQTT Publishers** (to send commands)

---

## 4. MQTT Broker Assumptions

The firmware is broker-agnostic.
It can work with:
- Public brokers (for testing)
- Local brokers (Mosquitto)
- Cloud brokers

Broker URI is configured via `menuconfig`.

Example:
```
mqtt://test.mosquitto.org
```

---

## 5. MQTT Topic Design

### 5.1 Publish Topic (ESP32 → External Systems)

**Purpose:** Sensor data and system status  
**Direction:** ESP32 → MQTT Broker → Subscribers  

Configured via:
```
CONFIG_MQTT_PUB_TOPIC
```

Default:
```
iot/esp32/data
```

---

### 5.2 Subscribe Topic (External Systems → ESP32)

**Purpose:** Actuator control commands  
**Direction:** Publishers → MQTT Broker → ESP32  

Configured via:
```
CONFIG_MQTT_SUB_TOPIC
```

Default:
```
iot/esp32/cmd
```

---

## 6. Message Payloads

### 6.1 Publish Payload (Sensor Data)

The ESP32 publishes **structured JSON**.

Example:
```json
{
  "device": {
    "id": "esp32-gateway-01",
    "uptime_sec": 120
  },
  "sensors": {
    "temperature": 26,
    "humidity": 58,
    "motion": 0,
    "soil_moisture": 420
  },
  "status": {
    "wifi": "connected",
    "mqtt": "connected"
  }
}
```

Responsibilities:
- ESP32 ensures valid JSON
- Receivers parse fields as needed
- Unknown fields should be ignored safely

---

### 6.2 Subscribe Payload (Command JSON)

Commands sent to ESP32 must follow the **defined schema**.

Example:
```json
{
  "device_id": "esp32-gateway-01",
  "command": {
    "target": "relay",
    "action": "on",
    "value": 0
  }
}
```

---

## 7. Command Validation Rules

ESP32 enforces:
- Valid JSON
- Required fields present
- Correct data types
- Unknown fields ignored

Invalid messages are:
- Logged
- Safely discarded
- Never crash the firmware

---

## 8. Quality of Service (QoS)

Current design:
- Publish QoS: 1
- Subscribe QoS: 0 or 1 (configurable in code)

Rationale:
- Ensures delivery without excessive overhead
- Suitable for lab and PoC environments

---

## 9. Error Handling & Reliability

### 9.1 Connection Loss
- Wi-Fi reconnects automatically
- MQTT reconnects automatically
- Publish attempts are guarded

### 9.2 Invalid Payloads
- Logged as warnings or errors
- Ignored without system reset

---

## 10. Security Considerations (Future)

Current implementation:
- Plain MQTT (no TLS)

Planned extensions:
- MQTT over TLS
- Authentication
- Broker-side ACLs

---

## 11. Testing Expectations

MQTT behavior can be tested using:
- MQTT Explorer
- Node-RED
- CLI MQTT clients

ESP32 logs should confirm:
- Connection events
- Publish events
- Received command handling

---

## 12. Next Document

Continue with:

📄 **08_Data_Flow.md**

This document explains:
- End-to-end data movement
- Timing behavior
- Interaction between modules
