#include "CountCapture.h"

CountCapture::CountCapture(int maxCount, unsigned long duration, unsigned long delay, int eepromAddress)
  : _maxCount(maxCount), _duration(duration), _delay(delay), _eepromAddress(eepromAddress), _count(0), _startTime(0) {}

void CountCapture::begin() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  if (!EEPROM.begin(sizeof(_count))) {
    Serial.println("Failed to initialize EEPROM");
    return;
  }
  
  // Read the count from EEPROM
  EEPROM.get(_eepromAddress, _count);
  Serial.print("Initial count: ");
  Serial.println(_count);
  
  // Delay for the specified time
  Serial.print("Delaying for ");
  Serial.print(_delay);
  Serial.println(" milliseconds...");
  delay(_delay);
  
  // Increment the count
  _count++;
  Serial.print("Count incremented. New count: ");
  Serial.println(_count);
  
  // Store the updated count in EEPROM
  EEPROM.put(_eepromAddress, _count);
  if (EEPROM.commit()) {
    Serial.println("Count stored in EEPROM");
  } else {
    Serial.println("Error storing count in EEPROM");
  }
  
  // Start the timer
  _startTime = millis();
  Serial.println("Timer started");
}

bool CountCapture::update() {
  // Check if the specified duration has passed
  if (millis() - _startTime > _duration) {
    Serial.print(_duration);
    Serial.println(" milliseconds passed");
    // Reset the count to 0 in EEPROM
    _count = 0;
    EEPROM.put(_eepromAddress, _count);
    if (EEPROM.commit()) {
      Serial.println("Count reset to 0 in EEPROM");
    } else {
      Serial.println("Error resetting count in EEPROM");
    }
    _startTime = millis();  // Reset the timer
    Serial.println("Timer reset");
  }
  
  // Check if the count reaches the maximum count
  if (_count == _maxCount) {
    Serial.println("Hit our Target Count!");
    // Reset the count to 0 in EEPROM
    _count = 0;
    EEPROM.put(_eepromAddress, _count);
    if (EEPROM.commit()) {
      Serial.println("Count reset to 0 in EEPROM");
    } else {
      Serial.println("Error resetting count in EEPROM");
    }
    return true;  // Return true to indicate that the maximum count has been reached
  }
  
  return false;  // Return false if the maximum count has not been reached
}
