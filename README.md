# CountCapture Library

The CountCapture library is an Arduino library that allows you to capture a specified number of counts within a given time duration. It provides an easy way to track and store counts across power cycles using the ESP32's EEPROM.

I've developed this library to capture 3 resets within 15 seconds to enable Wi-Fi provisioning on my ESP32 which doesn't have a Real-Time Clock (RTC) and no access to Network Time Protocol (NTP). This library simplifies the process of counting and persisting the counts across power cycles, making it convenient to trigger specific actions based on the number of counts within a specified time window.

## To-Do
- Change storage from eeprom to NVS.

## Features

- Capture a specified number of counts within a given time duration
- Store the count value in EEPROM for persistence across power cycles
- Customizable maximum count, duration, delay, and EEPROM address
- Simple and intuitive API

## Installation

1. Download the CountCapture library as a ZIP file from the GitHub repository.
2. In the Arduino IDE, go to Sketch -> Include Library -> Add .ZIP Library.
3. Select the downloaded ZIP file and click "Open".
4. The CountCapture library should now be installed and ready to use.

## Usage

1. Include the CountCapture library in your Arduino sketch:
   ```cpp
   #include <CountCapture.h> 

2. Create an instance of the CountCapture class, specifying the desired parameters:
   ```cpp
   CountCapture countCapture(maxCount, duration, delay, eepromAddress);
   ```

- maxCount: The maximum count to reach (default: 3)
- duration: The time duration in milliseconds (default: 15000)
- delay: The initial delay in milliseconds (default: 2000)
- eepromAddress: The EEPROM address to store the count (default: 0)


3. In the setup() function, call the begin() method to initialize the CountCapture instance:
```cpp
void setup() {
  countCapture.begin();
}
```
4. In the loop() function, call the update() method to update the count and check if the maximum count has been reached:
```cpp
void loop() {
  bool maxCountReached = countCapture.update();
  
  if (maxCountReached) {
    // Maximum count reached, perform desired actions
    // ...
  }
}
```
5. Upload the sketch to your ESP32 board and observe the serial monitor for debugging messages.
