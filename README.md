_**Presentation & Media Controller**_

  Gesture and Voice-Based Smart Controller for Presentations and Media
  
  "Speak the word, wave the wrist — the slide steps forward; rotate your arm and the room obeys."
  
  A complete, buildable project using the Silicon Labs SiWx917 Dev Kit (BRD2605A) that combines sound and motion sensing for hands-free control of presentations and media through Bluetooth Low Energy (BLE) communication.

**Key Features**
  
  Voice and Sound Activation: Detects a wake word or clap to activate the device.
  
  Gesture-Based Control: Uses onboard IMU gestures (flick, rotate, shake) to navigate slides or control playback.
  
  BLE HID Output: Transmits standard Bluetooth keyboard or media commands such as Next, Previous, Play/Pause, and Volume Control.
  
  Context-Aware Operation: Ambient light sensor prevents false gesture triggers in unsuitable conditions.
  
  Optional Environmental Sensing: Temperature and humidity readings can be used for ambient logging or demonstration.
  
  User Feedback: Onboard LED or buzzer provides confirmation of detected actions.
  
  Self-Contained Design: Utilizes only onboard components of the SiWx917 Dev Kit; no external hardware required.

**Workflow**

  1. Wake and Intent Detection
  
  The dual ICS-43434 microphones detect a predefined keyword or clap.
  
  Upon detection, the device wakes and enters gesture recognition mode.
  
  2. Gesture Recognition
  
  The ICM-40627 6-axis IMU analyzes motion patterns such as:
  
  Flick – Advance slide or skip forward
  
  Rotate – Adjust volume or toggle screen
  
  Shake – Pause media or end presentation
  
  3. Context Filtering
  
  The VEML6035 ambient light sensor ensures gestures are only processed under valid lighting conditions.
  
  Optional Si7021 sensor data may be used for environmental context or data logging.
  
  4. Action Execution
  
  Valid gestures are converted to BLE HID commands and sent to a connected host device (laptop, tablet, or display).
  
  Common mappings include “Right Arrow,” “Left Arrow,” “Volume Up/Down,” or “Play/Pause.”
  
  5. Feedback and Standby
  
  The onboard LED or buzzer confirms successful action recognition.
  
  Device returns to a low-power standby mode after inactivity.

**Applications**

  Presentation Control: Enables presenters to navigate slides and toggle screen states using gestures or voice.
  
  Media Playback: Provides intuitive control of media content over BLE.
  
  Accessibility Aid: Offers an alternative interface for users unable to handle small remote devices.
  
  Demonstration Platform: Useful for showcasing sensor fusion, BLE HID implementation, and edge intelligence.
  
  Educational Use: Serves as a teaching tool for IoT, embedded systems, and human–machine interaction.

**Hardware Summary**

  Development Kit: SiWx917 Dev Kit (BRD2605A)
  
  Onboard Components Utilized:
  
  ICS-43434 Digital Microphones (I²S) – Wake-word or clap detection
  
  ICM-40627 6-Axis IMU (SPI) – Gesture detection
  
  VEML6035 Ambient Light Sensor (I²C) – Context filtering
  
  Si7021 Temperature and Humidity Sensor (I²C, optional) – Environmental sensing
  
  Onboard LEDs / Buzzer – User feedback
