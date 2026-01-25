# ESP32 IoT Gateway – Testing and Simulation

## 1. Purpose of This Document

This document explains **how to test and simulate the complete ESP32 IoT Gateway**
*without using physical hardware*.

It is designed for:
- Training labs
- Demonstrations
- Proof-of-Concept (PoC) reviews
- Early-stage development and debugging

The goal is to **show the complete data flow visually and logically**:
- Sensor data generation
- JSON payload creation
- MQTT publish
- Command injection
- Actuator response

---

## 2. Testing Philosophy

The firmware is intentionally designed to support:
- Mock sensor data
- Mock actuator execution
- Real MQTT communication

This allows:
- End-to-end validation
- GUI-based demonstrations
- Debugging before hardware arrives

---

## 3. What Can Be Tested Without Hardware

| Feature | Testable |
|------|--------|
| ESP-IDF build | ✅ |
| Wi-Fi logic | ✅ (compile-level) |
| MQTT publish | ✅ |
| MQTT subscribe | ✅ |
| JSON payload format | ✅ |
| Sensor logic | ✅ (mock values) |
| Actuator routing | ✅ (log-based) |
| Protocol scaffolding | ✅ |

---

## 4. Required Testing Tools

### 4.1 MQTT Broker
- Public broker (example):
  ```
  mqtt://test.mosquitto.org
  ```
- Or local Mosquitto broker

---

### 4.2 MQTT GUI Tool (Highly Recommended)

**MQTT Explorer**
- Cross-platform GUI
- Real-time topic visualization
- JSON viewer

Used to:
- View published sensor data
- Send command JSON to ESP32

---

### 4.3 Optional Visualization Tools

- Node-RED (flow-based GUI)
- Web dashboards (future)
- JSON viewers

---

## 5. Simulating Sensor Data

### 5.1 How Sensor Simulation Works

- Sensor values are generated in:
  ```
  sensors_read_all()
  ```
- Values are hardcoded or algorithmic
- No GPIO or bus access is required

Example:
```c
data.temperature = 26;
data.humidity = 58;
```

---

### 5.2 Demonstration Use Case

1. Modify mock sensor values
2. Rebuild firmware
3. Observe new values in MQTT Explorer
4. Explain how real sensors would replace mocks

---

## 6. Testing MQTT Publish Flow (GUI-Based)

### 6.1 Steps

1. Build firmware:
   ```
   idf.py build
   ```
2. (Later) Flash firmware to ESP32
3. ESP32 publishes JSON to:
   ```
   iot/esp32/data
   ```

---

### 6.2 What to Observe in MQTT Explorer

- Topic appears in real time
- JSON payload is readable
- Fields update periodically
- Device ID matches configuration

---

## 7. Testing MQTT Subscribe & Actuator Flow

### 7.1 Sending Command JSON

Using MQTT Explorer, publish to:
```
iot/esp32/cmd
```

Example payload:
```json
{
  "device_id": "esp32-gateway-01",
  "command": {
    "target": "led",
    "action": "on"
  }
}
```

---

### 7.2 Observing ESP32 Behavior

- ESP32 log shows:
  - Command received
  - Target identified
  - Action executed (mock)
- No hardware is required

---

## 8. Bidirectional Flow Demonstration (End-to-End)

### Demonstration Script

1. ESP32 publishes sensor data
2. MQTT Explorer displays JSON
3. User sends command JSON
4. ESP32 processes command
5. Actuator handler logs execution

This demonstrates:
- Full duplex MQTT communication
- Clean separation of concerns
- Real-world IoT gateway behavior

---

## 9. Timing & Stress Testing

### 9.1 Publish Interval Testing

- Modify publish interval in `menuconfig`
- Observe frequency change in MQTT Explorer

---

### 9.2 Long-Run Stability Testing

- Run firmware for extended time
- Observe:
  - No crashes
  - No memory growth
  - Stable publish behavior

---

## 10. Testing Without Flashing (Development Phase)

Even without flashing:
- Code builds verify correctness
- Logic review confirms behavior
- Simulation prepares for hardware phase

---

## 11. Common Testing Mistakes

- Forgetting to save `menuconfig`
- Publishing invalid JSON commands
- Expecting GPIO changes without hardware
- Confusing publish vs subscribe topics

---

## 12. Training & Demo Tips

- Use MQTT Explorer for live demos
- Explain logs alongside GUI
- Show JSON schema visually
- Modify mock values live for effect

---

## 13. Summary

- Full system behavior can be demonstrated without hardware
- GUI tools make data flow visible
- Testing approach is training-friendly and professional
- Hardware integration becomes straightforward later

---

## 14. Next Document

Continue with:

📄 **10_Hardware_Integration.md**

This document will include:
- Pin mapping tables
- Wiring diagrams
- Electrical considerations
- Sensor-specific notes
