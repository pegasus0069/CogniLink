# CogniLink: Neuro-Assistive Communicator

> An open-source, patient-centric Augmentative and Alternative Communication (AAC) system engineered for patients with severe motor impairments (such as ALS or advanced paralysis).

![CogniLink Banner](https://img.shields.io/badge/Status-Feature%20Complete-brightgreen)
![Platform](https://img.shields.io/badge/Hardware-M5StickC-blue)
![Interface](https://img.shields.io/badge/UI-WebSockets%20%7C%20Responsive-orange)
![License](https://img.shields.io/badge/License-GPLv3-blue.svg)

## 📄 License
This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.

---

## 🌟 Overview

**CogniLink** bridges the gap between hardware sensors and software accessibility. By mounting an **M5StickC** micro-controller module onto a patient's finger, it acts as a **wearable gyroscope mouse** controlled via subtle hand tilting. The companion **Web UI** provides an assistive communication dashboard featuring bilingual support (English and Bengali), custom dwell-clicking (hover-to-trigger) for medical needs, and multi-stage power saving.

---

## ✨ Key Features

- **Gesture Mouse Control:** Uses the M5StickC IMU gyroscope to translate tiny finger movements into smooth on-screen cursor navigation.
- **Bilingual AAC (English & Bangla):** Fully localized virtual keyboards, character maps, and text outputs supporting both English and Bengali scripts.
- **Smart TTS Engine:** Dynamically routes through browser speech synthesis, system offline voices, or Google Cloud fallback depending on device availability and active OS (Android, Windows, macOS, Linux).
- **Quick Medical Tray:** Permanent, fast-access emergency phrases (*"I need suction", "I am in pain", "I can't breathe"*, etc.) located at the base of the screen.
- **Dwell-Clicking (Hover-to-Trigger):** Patients can rest their cursor over a medical phrase for 5 seconds to automatically trigger speech without requiring a physical mouse click.
- **Adaptive UI & Custom Assistive Cursor:** Soothing dark/light beige themes with glowing targeting-ring cursors designed to minimize visual fatigue.
- **Smart Wi-Fi Provisioning (`WiFiManager`):** Automatically generates an on-screen QR code for zero-friction home network pairing, with a hardware reset button for mobile deployment.
- **Two-Stage Power Conservation:** Automatically dims the M5StickC screen after 30 seconds of inactivity and turns it off after 60 seconds while keeping Bluetooth/Wi-Fi active.

---

## 🛠️ Hardware Requirements

1. **M5StickC** (ESP32-based IoT Development Board)
2. **Wearable Mount / Ring Strap** (to secure the M5StickC to the patient's finger)

---

## 💻 Software & Library Dependencies

To compile and upload the firmware using the **Arduino IDE**, ensure you have installed the following libraries via the Library Manager:

- `M5StickC` (by M5Stack)
- `HijelHID_BLEMouse` (Bluetooth HID Mouse library)
- `WiFiManager` (by tzapu - for captive portal Wi-Fi configuration)
- `WebSockets` (by Markus Sattler)

---

## 📂 Project Structure

```text
CogniLink-AAC/
├── M5StickC_Mouse.ino      # Main C++ firmware handling IMU, BLE, Wi-Fi, and Power saving
├── index.h                 # Embedded HTML/CSS/JS Web UI dashboard
└── README.md               # Project documentation
