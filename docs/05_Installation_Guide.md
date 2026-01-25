# ESP32 IoT Gateway – Installation Guide

## 1. Purpose of This Document
This document provides **step-by-step installation instructions** for setting up
the ESP32 IoT Gateway development environment **from scratch**.

It is written for:
- First-time ESP-IDF users
- Students and trainees
- Engineers setting up a new system

---

## 2. Pre-Installation Checklist

Before starting, ensure:
- Stable internet connection
- At least 5–8 GB free disk space
- Administrator rights on the system
- A supported OS (Windows 10/11, macOS, or Linux)

---

## 3. Installing ESP-IDF (Recommended Method)

### 3.1 Windows Installation (Recommended for Beginners)

1. Download the **ESP-IDF Tools Installer** from Espressif official site.
2. Run the installer as Administrator.
3. Select:
   - ESP-IDF v5.x
   - Python (auto-managed)
   - ESP-IDF Tools
4. Choose installation path (default recommended):
   ```
   C:\esp
   ```
5. Complete installation and reboot if prompted.

---

### 3.2 macOS Installation

1. Install dependencies using Homebrew:
   ```
   brew install cmake ninja dfu-util python
   ```
2. Clone ESP-IDF:
   ```
   git clone -b v5.x https://github.com/espressif/esp-idf.git
   ```
3. Run install script:
   ```
   ./install.sh
   ```
4. Activate environment:
   ```
   source export.sh
   ```

---

### 3.3 Linux Installation (Ubuntu Example)

1. Install dependencies:
   ```
   sudo apt install git cmake ninja-build python3 python3-pip
   ```
2. Clone ESP-IDF:
   ```
   git clone -b v5.x https://github.com/espressif/esp-idf.git
   ```
3. Install ESP-IDF:
   ```
   ./install.sh
   ```
4. Activate environment:
   ```
   source export.sh
   ```

---

## 4. Verify ESP-IDF Installation

Run the following command in terminal:
```
idf.py --version
```

Expected output:
```
ESP-IDF v5.x
```

---

## 5. Install Visual Studio Code

1. Download VS Code from official website.
2. Install and launch VS Code.
3. Install **ESP-IDF Extension** from Extensions Marketplace.
4. Restart VS Code.

---

## 6. Configure ESP-IDF Extension in VS Code

1. Open **ESP-IDF Command Prompt** (Windows) or terminal with ESP-IDF environment.
2. Launch VS Code using:
   ```
   code
   ```
3. Run:
   ```
   ESP-IDF: Configure ESP-IDF Extension
   ```
4. Select:
   - Use existing ESP-IDF
   - Confirm paths
5. Finish configuration.

---

## 7. Project Setup

1. Navigate to workspace directory:
   ```
   cd C:\esp
   ```
2. Clone or copy the ESP32 IoT Gateway project.
3. Open project in VS Code:
   ```
   code .
   ```

---

## 8. Build the Project

In VS Code terminal:
```
idf.py build
```

Expected result:
```
Build complete.
```

---

## 9. menuconfig Setup

Open configuration menu:
```
idf.py menuconfig
```

Navigate to:
```
ESP32 IoT Gateway Configuration
```

Set:
- Device ID
- MQTT broker URI
- Publish interval
- Enable/disable protocols

Save and exit.

---

## 10. Flashing Firmware (Later Stage)

When hardware is available:
```
idf.py flash monitor
```

> Flashing is not required for initial development and simulation.

---

## 11. Common Issues & Fixes

### idf.py not recognized
- Ensure ESP-IDF environment is activated
- Use ESP-IDF Command Prompt on Windows

### Build errors
- Run:
  ```
  idf.py fullclean
  idf.py build
  ```

---

## 12. Next Document

Continue with:

📄 **06_Project_Structure.md**

This document explains:
- Folder layout
- Module responsibilities
- Where to add new code
