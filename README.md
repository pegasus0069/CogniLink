# CogniLink: Neuro-Assistive Communicator

> An open-source, patient-centric Augmentative and Alternative Communication (AAC) prototype for people with severe motor and speech impairments.

![Status](https://img.shields.io/badge/Status-Feature%20Complete-brightgreen)
![Hardware](https://img.shields.io/badge/Hardware-M5StickC-blue)
![Interface](https://img.shields.io/badge/Interface-Web%20UI%20%7C%20WebSockets-orange)
![License](https://img.shields.io/badge/License-GPLv3-blue.svg)

## Table of Contents

1. [Overview](#overview)
2. [Problem Statement](#problem-statement)
3. [Current Implementation and Scope](#current-implementation-and-scope)
4. [Features](#features)
5. [System Architecture](#system-architecture)
6. [Hardware Requirements](#hardware-requirements)
7. [Software Requirements](#software-requirements)
8. [Libraries](#libraries)
9. [Project Structure](#project-structure)
10. [Installation and Upload](#installation-and-upload)
11. [First-Time Wi-Fi Setup](#first-time-wi-fi-setup)
12. [Bluetooth Pairing](#bluetooth-pairing)
13. [Opening the Communicator](#opening-the-communicator)
14. [Step-by-Step User Guide](#step-by-step-user-guide)
15. [English and Bengali Support](#english-and-bengali-support)
16. [Text-to-Speech Behavior](#text-to-speech-behavior)
17. [M5StickC Controls](#m5stickc-controls)
18. [Device Display and Status](#device-display-and-status)
19. [Power Management](#power-management)
20. [Wi-Fi Reset and Recovery](#wi-fi-reset-and-recovery)
21. [Firmware Technical Reference](#firmware-technical-reference)
22. [WebSocket Data](#websocket-data)
23. [Troubleshooting](#troubleshooting)
24. [Safety and Limitations](#safety-and-limitations)
25. [Future Work](#future-work)
26. [License](#license)

## Overview

CogniLink is a bridge between a person's intentions and the outside world. Its long-term vision is a wearable neuro-assistive system that can safely interpret brainwave activity and translate a user's intended communication into text or spoken audio. Instead of requiring a keyboard or speech, a user could communicate thoughts, needs, and commands through an accessible interface.

The current repository implements the first assistive-control prototype of that vision. An **M5StickC** worn on a finger uses gyroscope movement and a physical button as an accessible Bluetooth mouse. A companion web interface turns those inputs into a bilingual communication dashboard with an on-screen keyboard, medical phrases, and text-to-speech.

> **Important implementation status:** The current code does not read EEG or other brainwave signals. It uses the M5StickC IMU, physical buttons, Bluetooth HID, Wi-Fi, and browser audio. EEG/BCI integration is future work.

## Problem Statement

Severe medical conditions and physical trauma can leave individuals with sharp, active minds but little or no ability to speak or control their muscles. This includes people living with:

- Amyotrophic Lateral Sclerosis (ALS) / Motor Neurone Disease (MND)
- Parkinson's disease
- Spinal Muscular Atrophy (SMA)
- Cerebral Palsy (CP)
- Severe Spinal Cord Injuries (SCI)
- Traumatic brain injuries that result in paralysis and loss of speech

These conditions can trap people in their own bodies, making it difficult to communicate basic needs, ask for help, or share thoughts with loved ones and caregivers. CogniLink is intended to support independence and connection by providing a low-effort communication path that can be adapted as a user's physical abilities change.

## Current Implementation and Scope

The current system uses a calibrated gyroscope as the input method:

1. The M5StickC is mounted securely on a finger or another controllable body location.
2. The wearer tilts or rotates the device.
3. The IMU readings are converted into cursor movement.
4. The M5StickC exposes itself as a Bluetooth HID mouse named **CogniLink Finger**.
5. `BtnA` acts as the left mouse button.
6. The browser interface displays a large accessible keyboard and communication controls.
7. The user's selections are displayed and spoken.

The project is therefore an assistive mouse and AAC communicator prototype today. The neuro-assistive and brainwave-translation description represents the project's future direction, not a capability currently present in this repository.

## Features

### Hardware and firmware

- M5StickC ESP32 firmware written for the Arduino ecosystem
- IMU initialization and startup calibration
- Gyroscope deadzone filtering to reduce accidental cursor movement
- Configurable movement sensitivity in firmware
- Bluetooth Low Energy HID mouse output
- Physical left-click input through `BtnA`
- Wi-Fi provisioning through WiFiManager
- Captive-portal QR code shown on the M5StickC display
- Embedded HTTP server for the web communicator
- WebSocket server for live device data
- Battery-voltage estimation and Bluetooth battery-level reporting
- On-device display with Wi-Fi, IP address, BLE, battery, and button status
- Automatic display dimming and screen shutoff during inactivity
- Five-second Wi-Fi credential reset using `BtnB`

### Web communicator

- English and Bengali/Bangla communication modes
- English alphabet, numbers, punctuation, and symbols
- Bengali consonants, vowels, vowel signs, and Bengali numerals
- Large on-screen controls designed for cursor or dwell-style access
- Text output area with large, readable text
- Character-by-character speech feedback
- Full-sentence speech output
- Quick medical-needs phrase tray
- Five-second hover-to-trigger dwell activation
- Immediate click activation for every medical phrase
- Automatic three-second clearing after speech or a medical phrase
- Cloud and System text-to-speech options
- Offline system voice selection by language and preferred gender
- Light and dark themes
- Browser and operating-system detection
- Connection indicator and live battery percentage
- Responsive layout with large buttons and high-visibility colors
- Custom assistive cursor graphics

## System Architecture

```text
                    Gyroscope movement
                            |
                            v
                      +-----------+
                      | M5StickC |
                      | IMU       |
                      +-----------+
                       |         |
             BLE HID   |         | Wi-Fi
             mouse     |         |
                       v         v
                 +----------+  +------------------+
                 | Host OS  |  | HTTP :80        |
                 | cursor   |  | WebSocket :81   |
                 +----------+  +--------+---------+
                                         |
                                         v
                              Embedded browser UI
                                         |
                         +---------------+---------------+
                         |                               |
                  On-screen AAC                    Text-to-speech
                  keyboard/phrases                 cloud or system
```

The firmware serves the page stored in `INDEX_HTML` from `index.h`. The browser uses the same device hostname for the WebSocket connection and connects to port `81`.

## Hardware Requirements

1. **M5StickC** ESP32-based development board with:
   - 6-axis IMU
   - 160x80 LCD
   - Wi-Fi
   - Bluetooth
   - `BtnA` and `BtnB`
   - Battery and power-management hardware
2. **USB data cable** suitable for programming the M5StickC
3. **Wearable mount, finger strap, or custom holder**
4. **Computer, tablet, or phone** with:
   - A modern browser with JavaScript and WebSocket support
   - Bluetooth HID mouse support
   - Audio output for text-to-speech
5. A Wi-Fi network for normal operation

The wearable must be comfortable and must not restrict circulation or movement.

## Software Requirements

- Arduino IDE
- ESP32 board support package for Arduino
- USB serial drivers appropriate for the M5StickC and operating system
- A modern web browser such as Chrome, Edge, Firefox, or Safari
- A browser/OS with English or Bengali speech voices for offline TTS

## Libraries

Install these libraries through the Arduino IDE Library Manager:

- `M5StickC` by M5Stack
- `HijelHID_BLEMouse`
- `WiFiManager` by tzapu
- `WebSockets` by Markus Sattler

The firmware also includes these libraries from the ESP32 Arduino core:

- `WiFi.h`
- `WebServer.h`

## Project Structure

```text
CogniLink/
├── m5stickc/
│   ├── m5stickc.ino   # ESP32 firmware and device runtime
│   └── index.h         # Embedded HTML, CSS, and JavaScript UI
├── LICENSE             # GNU General Public License v3.0
└── README.md           # Project documentation
```

### Firmware responsibilities

[`m5stickc/m5stickc.ino`](m5stickc/m5stickc.ino) handles:

- M5StickC initialization
- IMU calibration and gyroscope sampling
- Wi-Fi connection and captive-portal setup
- HTTP server on port 80
- WebSocket server on port 81
- BLE mouse initialization and movement
- Button handling
- Battery estimation
- Device LCD rendering
- Power-saving behavior

### Interface responsibilities

[`m5stickc/index.h`](m5stickc/index.h) contains the complete embedded web page:

- HTML layout
- CSS themes and controls
- English/Bengali keyboard definitions
- Medical phrase definitions
- TTS selection and fallback
- Dwell-click behavior
- WebSocket status and battery handling

## Installation and Upload

### 1. Install Arduino IDE

Download and install Arduino IDE on the development computer.

### 2. Install ESP32 board support

In Arduino IDE:

1. Open **File > Preferences**.
2. Add the Espressif ESP32 Boards Manager URL if it is not already present.
3. Open **Tools > Board > Boards Manager**.
4. Search for **esp32**.
5. Install the ESP32 package by Espressif Systems.

### 3. Install the libraries

Open **Sketch > Include Library > Manage Libraries**, search for each library in the [Libraries](#libraries) section, and install it.

### 4. Open the firmware

Open:

```text
m5stickc/m5stickc.ino
```

Keep `index.h` in the same folder as the `.ino` file. The firmware includes it with:

```cpp
#include "index.h"
```

### 5. Connect the M5StickC

1. Connect the M5StickC with a USB data cable.
2. Wait for the serial port to appear.
3. In Arduino IDE, choose the correct port under **Tools > Port**.

### 6. Select the board

Select the M5StickC-compatible ESP32 board profile available in your installed board package. If the board is not detected, check the USB driver, cable, and port selection.

### 7. Upload

1. Compile with **Verify**.
2. Fix any missing-library errors before continuing.
3. Click **Upload**.
4. If Arduino IDE asks for bootloader mode, follow its instruction and press the M5StickC reset/boot control as required.
5. Wait for the upload to finish.

## First-Time Wi-Fi Setup

The firmware calls `WiFiManager::autoConnect("CogniLink_Setup")`.

1. Power on or reset the M5StickC.
2. Keep the device still while **Calibrating IMU...** is displayed.
3. If saved Wi-Fi credentials work, the device connects automatically.
4. If no saved network is available, the device starts the `CogniLink_Setup` access point.
5. On a phone or computer, open the Wi-Fi list.
6. Connect to **CogniLink_Setup**.
7. Wait for the captive portal to open. If it does not, open a browser and visit a common address such as `192.168.4.1`.
8. Use the portal to scan or select a network.
9. Enter the network password if required.
10. Save the configuration.
11. Wait for the M5StickC to reconnect and restart its normal services.

During configuration, the device display shows:

```text
1. Scan QR
2. Sign In
3. Add WiFi
```

It also displays a QR code representing the setup network. The firmware currently creates a no-password QR string for the temporary setup access point; the target home network still uses the credentials entered in WiFiManager.

## Bluetooth Pairing

The firmware starts a BLE mouse with:

```text
Device name: CogniLink Finger
Manufacturer: CogniLink
```

Pair it once with the computer, tablet, or phone that will display the communicator:

1. Open the host device's Bluetooth settings.
2. Turn Bluetooth on.
3. Find **CogniLink Finger**.
4. Select it and complete pairing.
5. Open a text field or a blank area where cursor movement can be tested.
6. Tilt the M5StickC gently.
7. Press `BtnA` to test a left click.

The M5StickC display shows **BLE: Connected** after pairing and **BLE: Disconnected** otherwise. The firmware also updates the BLE mouse battery level when pairing is active.

## Opening the Communicator

After Wi-Fi connects:

1. Read the IP address from the M5StickC display.
2. On a device connected to the same Wi-Fi network, open:

```text
http://<M5StickC-IP>/
```

For example:

```text
http://192.168.1.42/
```

The firmware serves the embedded `INDEX_HTML` page at `/` using HTTP port `80`.

When the page loads, it opens:

```text
ws://<M5StickC-IP>:81/
```

The status indicator should change from **CogniLink Disconnected** to **CogniLink Linked**.

## Step-by-Step User Guide

### 1. Prepare the device

1. Secure the M5StickC so it can be tilted safely and comfortably.
2. Confirm that the wearable does not cause pressure, pain, or restricted circulation.
3. Power on the device.
4. Place the wearable in its intended neutral position.
5. Keep it completely still during calibration.

Calibration begins after startup and collects 150 gyroscope samples at 10 ms intervals. The average of those samples becomes the movement offset.

### 2. Confirm status

Check the M5StickC LCD:

- Wi-Fi SSID
- Local IP address
- BLE connection state
- Battery percentage
- Animated cyan activity line
- Orange `BtnA` indicator while the button is pressed

Then check the browser:

- The connection indicator is green and says **CogniLink Linked**.
- The battery percentage is visible in the top status bar.

### 3. Move the cursor

1. Hold the M5StickC in its calibrated neutral position.
2. Tilt it gently left, right, forward, or backward.
3. Use small, controlled movements.
4. Return toward neutral to stop moving.

The firmware applies a `1.2` gyroscope deadzone. Movement below that threshold is ignored. Movement above it is multiplied by the `0.6` sensitivity value and sent as BLE mouse movement.

### 4. Select a control

1. Tilt the device until the assistive cursor rests over a button.
2. Press and release `BtnA`.
3. The browser activates the focused/hovered control.

The cursor is styled as a large targeting ring, and buttons provide visual hover and active feedback.

### 5. Compose text

1. Choose the language with the language button.
2. Select the required keyboard tab.
3. Move to a character.
4. Press `BtnA`.
5. The character appears in the large output area.
6. The character is spoken immediately as feedback.
7. Continue selecting characters.
8. Select the space key between words.

Use **Del** to remove the last character and **Clear** to remove the entire message.

### 6. Speak a completed message

1. Compose the message.
2. Confirm the text shown in the output area.
3. Press **Speak**.
4. The complete text is spoken using the selected TTS engine.
5. The display is automatically cleared after approximately three seconds.

### 7. Use a medical phrase

1. Scroll to **Quick Medical Needs**.
2. Choose the current language.
3. Either:
   - Press `BtnA` while the cursor is over a phrase, or
   - Hold the cursor over the phrase for five seconds.
4. The short phrase label appears in the output area.
5. The full sentence is spoken.
6. The output clears after approximately three seconds.

The dwell progress bar fills while the cursor remains over the phrase. Moving away resets the progress.

### 8. Change settings

1. Select the gear icon in the top status bar.
2. Choose **Light** or **Dark** theme.
3. Choose **Female** or **Male** voice where matching voices exist.
4. Choose **Cloud** or **System** TTS.
5. Close the menu by selecting outside it.

Unavailable voice or TTS options are disabled automatically.

## English and Bengali Support

Language support is implemented in the embedded web application in [`m5stickc/index.h`](m5stickc/index.h). The interface starts in English and switches between English and Bengali using the **Switch to বাংলা / Switch to English** button.

### English

- **ABC / 123** tab:
  - Digits `1` through `0`
  - Uppercase letters `QWERTY`, `ASDF`, and `ZXCVBNM`
  - Comma, period, and question mark
- **Symbols** tab:
  - Exclamation mark, at sign, hash, dollar, percent, caret, ampersand, asterisk, and parentheses
  - Hyphen, underscore, equals, plus, brackets, braces, backslash, and pipe
  - Semicolon, colon, apostrophe, quotation mark, comma, period, angle brackets, slash, and question mark
- English space, delete, clear, and speak controls
- TTS language code: `en`
- Offline fallback locale: `en-US`

### Bengali (Bangla)

- **কখগ (Consonants)** tab with Bengali consonants and signs
- **অআ & ১২৩ (Vowels/Numbers)** tab with:
  - Bengali numerals `০` through `৯`
  - Bengali vowels
  - Bengali vowel signs
- Bengali space control labeled **স্পেস (SPACE)**
- TTS language code: `bn`
- Offline fallback locale: `bn-BD`
- Browser voice detection recognizes voices whose language contains `bn` or whose name contains `bangla` or `bengali`

Switching language also:

1. Changes the language button label.
2. Selects the English `alpha` tab or Bengali `cons` tab by default.
3. Rebuilds the keyboard.
4. Rebuilds the medical phrase tray.
5. Updates available voice and engine settings.
6. Forces offline speech on Android when Bengali is selected.

### Medical phrases

The medical tray contains eight English and eight Bengali entries. Each has a short button label and a full spoken sentence.

| English button | Spoken English |
| --- | --- |
| I need suction | I need suction to clear my throat. |
| I am in pain | I am in pain, please help me. |
| I can't breathe | I am having trouble breathing. |
| Adjust position | Please adjust my sitting position. |
| I want Water | I am thirsty, I need water. |
| Call Nurse | Please call the nurse immediately. |
| YES | Yes. |
| NO | No. |

| Bengali button | Spoken Bengali |
| --- | --- |
| সাকশন দরকার | আমার সাকশন দরকার। |
| ব্যথা করছে | আমার খুব ব্যথা করছে। |
| শ্বাসকষ্ট হচ্ছে | আমার শ্বাস নিতে কষ্ট হচ্ছে। |
| অবস্থান বদলান | আমাকে একটু সোজা করে দিন। |
| পানি খাব | আমি পানি খাবো। |
| নার্সকে ডাকুন | দয়া করে নার্সকে ডাকুন। |
| হ্যাঁ | হ্যাঁ। |
| না | না। |

## Text-to-Speech Behavior

The interface supports two TTS paths:

### Cloud mode

When **Cloud** is selected and the browser is online:

1. The selected text is URL-encoded.
2. The interface requests Google Translate TTS using `tl=en` or `tl=bn`.
3. Audio is played in the browser.
4. If playback fails, the interface falls back to System speech.

Cloud speech uses a slower playback rate for complete phrases and a slightly faster rate for individual characters.

### System mode

When **System** is selected, offline, or cloud playback is unavailable:

1. The browser's `speechSynthesis` API is used.
2. Voices are filtered for the current language.
3. The preferred gender is used when a matching voice is found.
4. If no matching voice is found, the first language voice is used.
5. If no voice is installed, the utterance still receives the relevant locale (`en-US` or `bn-BD`).

Cloud mode is disabled automatically when the browser is offline. System mode is used automatically on Android for Bengali because the code specifically routes that combination to offline speech.

## M5StickC Controls

| Control | Action |
| --- | --- |
| Gyroscope tilt | Moves the paired Bluetooth cursor |
| `BtnA` press | Sends BLE left-button press/release and activates the hovered web control |
| `BtnB` held for less than five seconds | Shows Wi-Fi reset progress; releasing cancels the reset |
| `BtnB` held for at least five seconds | Erases Wi-FiManager settings and restarts the device |

While `BtnB` is held, normal cursor processing is paused and the screen shows **Wipe WiFi Data?**, **Keep holding button...**, and a progress bar. If the screen was asleep, the firmware wakes it during this operation.

## Device Display and Status

The firmware uses a 160x80 sprite and rotates the LCD before normal operation. The normal display shows:

- `WiFi:` followed by the connected SSID, shortened to ten characters plus `..` when necessary
- The local IP address
- `BLE: Connected` or `BLE: Disconnected`
- `Bat:<percentage>%`
- A moving cyan waveform-like line
- An orange circle when `BtnA` is pressed

Battery color thresholds on the device are:

- Green: 50% or higher
- Orange: 20% to 49%
- Red: below 20%

The browser uses the same low-battery thresholds for its battery indicator.

## Power Management

The firmware tracks movement and `BtnA` activity:

1. On activity, the screen returns to brightness `30`.
2. After more than 30 seconds without movement or button activity, brightness changes to `9`.
3. After more than 60 seconds, brightness changes to `0`.
4. The device continues handling Wi-Fi, WebSockets, and BLE while the LCD is off.
5. New movement or `BtnA` activity wakes the display to brightness `30`.

The initial screen brightness is `20`. `BtnB` reset handling can also wake the screen temporarily.

## Wi-Fi Reset and Recovery

Use the Wi-Fi reset only when the saved network is unavailable, incorrect, or needs to be replaced:

1. Make sure the device is powered on.
2. Press and hold `BtnB`.
3. Keep holding while the display shows **Wipe WiFi Data?** and the red progress bar advances.
4. Continue for the full five seconds.
5. Wait for **WIPING WIFI DATA...**.
6. The firmware calls `wifiManager.resetSettings()` and restarts the ESP32.
7. Repeat [First-Time Wi-Fi Setup](#first-time-wi-fi-setup).

Releasing `BtnB` before five seconds cancels the operation and preserves the saved credentials. The reset process is available even when the normal screen is asleep.

## Firmware Technical Reference

### Services and ports

| Service | Port | Purpose |
| --- | ---: | --- |
| HTTP server | 80 | Serves `INDEX_HTML` at `/` |
| WebSocket server | 81 | Broadcasts sensor and battery JSON |
| Bluetooth HID | N/A | Exposes `CogniLink Finger` as a BLE mouse |

### Startup sequence

When `setup()` runs, the firmware:

1. Calls `M5.begin()`.
2. Initializes the IMU with `M5.IMU.Init()`.
3. Sets initial screen brightness to `20`.
4. Rotates the display.
5. Shows the calibration message.
6. Waits one second.
7. Collects 150 gyroscope samples with a 10 ms delay between samples.
8. Averages `gx`, `gy`, and `gz` into offset values.
9. Starts WiFiManager with the `CogniLink_Setup` fallback access point.
10. Creates a 160x80 LCD sprite.
11. Registers the HTTP root route.
12. Starts HTTP and WebSocket services.
13. Starts the BLE mouse.
14. Initializes the inactivity timer.

If WiFiManager cannot connect, the firmware waits three seconds and restarts the ESP32.

### Main loop

The firmware loop:

1. Updates M5StickC button state.
2. Handles HTTP clients.
3. Processes WebSocket traffic.
4. Checks for the `BtnB` Wi-Fi reset hold.
5. Reads the IMU.
6. Subtracts the calibration offsets.
7. Updates the battery estimate.
8. Applies smart sleep/wake logic.
9. Sends gyroscope, button, and battery data over WebSockets.
10. Moves the BLE cursor and handles `BtnA` clicks when paired.
11. Draws the LCD when brightness is above zero.
12. Delays for 20 ms before the next iteration.

The nominal loop delay is approximately 20 ms, or about 50 iterations per second, although actual timing also includes display, networking, and Bluetooth work.

### Motion processing

The firmware constants are:

```cpp
const float sensitivity = 0.6;
const float deadzone = 1.2;
```

After offsets are removed:

- `gz` controls horizontal cursor movement.
- `gx` controls vertical cursor movement.
- Values inside the deadzone do not move the cursor.
- Values outside the deadzone are multiplied by sensitivity.
- The resulting movement is inverted before `bleMouse.move(...)`.
- `gy` is calibrated and streamed but is not used for cursor movement.

## WebSocket Data

The firmware broadcasts a JSON message on port `81` containing:

```json
{
  "gx": 0.00,
  "gy": 0.00,
  "click": false,
  "bat": 87
}
```

Fields:

- `gx`: calibrated gyroscope value used for vertical motion
- `gy`: value placed in the `gy` JSON field by the firmware's sensor payload
- `click`: whether `BtnA` is currently pressed
- `bat`: estimated battery percentage clamped from 0 to 100

The browser currently uses `bat` to update the battery display and uses WebSocket open/close events to update the connection label. BLE cursor movement is performed by the operating system through the paired HID mouse.

## Troubleshooting

### The M5StickC does not appear as a serial port

1. Use a USB data cable rather than a charge-only cable.
2. Try another USB port.
3. Install the appropriate USB-to-serial driver.
4. Close other serial-monitor applications.
5. Reopen Arduino IDE after installing the driver.

### Compilation reports a missing header

Check that the required libraries are installed and that the selected ESP32 board package is active. The common headers are:

```text
M5StickC.h
HijelHID_BLEMouse.h
WiFi.h
WebServer.h
WebSocketsServer.h
WiFiManager.h
```

### The cursor drifts

1. Restart the device.
2. Keep the M5StickC completely still during **Calibrating IMU...**.
3. Mount the device securely so the neutral position does not change.
4. Avoid touching or moving it during calibration.

### Cursor movement is too fast or too slow

Adjust `sensitivity` in `m5stickc.ino` and upload the firmware again. Change it carefully because the value affects all cursor movement.

### The browser cannot open the device page

1. Confirm the device display shows a Wi-Fi SSID and IP address.
2. Confirm the browser device is connected to the same network.
3. Open `http://<device-ip>/`, not `https://`.
4. Check that the IP was not changed by the router.
5. Reconnect Wi-Fi or repeat the provisioning process.
6. Check whether a guest network blocks local device-to-device traffic.

### The page loads but says “CogniLink Disconnected”

1. Confirm port `81` is reachable on the local network.
2. Reload the page.
3. Check that the device has not restarted.
4. Confirm the browser is not blocking mixed or local WebSocket connections.
5. Check whether the router isolates wireless clients.

### Bluetooth pairing fails

1. Remove any old **CogniLink Finger** pairing.
2. Restart the M5StickC.
3. Confirm the display changes to **BLE: Connected** after pairing.
4. Move the device closer to the host.
5. Ensure another host is not already connected.

### Bengali speech is silent

1. Install or enable a Bengali/Bangla speech voice in the operating system.
2. Open the settings menu and select **System**.
3. Confirm the browser has a voice whose language contains `bn`, or whose name contains `Bangla` or `Bengali`.
4. On Android, Bengali is intentionally routed to System/offline speech.
5. Confirm the device volume and browser audio permission.

### The display turns off

This is expected after 60 seconds of inactivity. Tilt the device or press `BtnA` to wake it. The Wi-Fi, WebSocket, and BLE services continue running while the LCD is off.

### Wi-Fi credentials must be changed

Hold `BtnB` continuously for at least five seconds. Releasing it before five seconds cancels the reset. After a successful reset, the device restarts and opens the `CogniLink_Setup` provisioning flow.

## Safety and Limitations

CogniLink is an experimental assistive-technology project and is **not a medical device**. It must not replace professional assessment, prescribed communication equipment, emergency services, or caregiver support.

- Do not rely on the prototype as the only emergency communication channel.
- Test all medical phrases with the intended user and caregiver.
- Verify that spoken phrases are understandable at the selected volume.
- Keep the wearable comfortable and check skin and circulation regularly.
- Do not expose Wi-Fi setup credentials or the local device page to an untrusted network.
- Cloud TTS sends selected text to an external Google Translate endpoint when Cloud mode is active and the browser is online.
- Network loss, browser restrictions, missing voices, battery depletion, or Bluetooth disconnection can interrupt communication.
- A caregiver or clinician should supervise testing and determine whether the interaction method is appropriate.

## Future Work

Potential future improvements include:

- EEG/BCI input and signal-processing research
- Better offline Bengali speech support
- Persistent language, theme, voice, and engine preferences
- Caregiver-configurable phrase sets
- More input methods for users with different motor abilities
- Adjustable sensitivity and deadzone from the web interface
- Improved IMU calibration and drift correction
- Stronger local-network security and authentication
- More detailed connection and sensor diagnostics
- Medical-device validation and usability studies

## License

This project is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for details.
