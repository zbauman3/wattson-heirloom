#include <Arduino.h>

#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_ADDR 0x50

// `address` is the actual address.
// `start` is the _first_ address that the buffer was pulled from
#define readEepromBuffer(bufferName, start, address) bufferName[address - start]

// `readFn` is the `Adafruit_EEPROM_I2C` `read` function
// `start` is the _first_ address that the buffer is pulled from
// `length` is the number of bytes to pull
#define eepromToBuffer(bufferName, readFn, start, length)                      \
  uint8_t bufferName[length];                                                  \
  readFn(start, bufferName, length)

// current length, but really LIGHTS can use all of `0x0-`
#define EEPROM_LIGHTS_MEM_LENGTH 5
#define EEPROM_LIGHTS_MEM_START 0x00
#define EEPROM_LIGHTS_MODE (EEPROM_LIGHTS_MEM_START + 0)
#define EEPROM_LIGHTS_BRIGHTNESS (EEPROM_LIGHTS_MEM_START + 1)
#define EEPROM_LIGHTS_SPEED (EEPROM_LIGHTS_MEM_START + 2)
#define EEPROM_LIGHTS_DIRECTION (EEPROM_LIGHTS_MEM_START + 3)
#define EEPROM_LIGHTS_COLOR (EEPROM_LIGHTS_MEM_START + 4)

#endif