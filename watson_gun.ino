#include "./src/config/Macros.h"
#include "./src/config/PinDefs.h"
#include "./src/controllers/Interrupts.h"
#include "./src/controllers/Joystick.h"
#include "./src/controllers/Rotary.h"
#include "./src/feedback/Leds.h"
#include "./src/feedback/LightRods.h"
#include "./src/feedback/Screen.h"
#include "./src/feedback/Vibration.h"
#include "./src/models/State.h"
#include "./src/views/ViewManager.h"
#include <AceRoutine.h>
#include <Adafruit_EEPROM_I2C.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Adafruit_MCP23X17 mcp;
Adafruit_EEPROM_I2C eeprom;
State state;
LightRods lightRods(&state);
Joystick joystick(&state);
Leds leds(&mcp);
Rotary rotary(&state);
Screen screen(&mcp);
Vibration vibration;
Interrupts inter(&state, &mcp, &rotary);
ViewManager viewManager(&state, &screen, &joystick, &leds, &lightRods,
                        &vibration, &eeprom);

void setup() {
  // call immediately to prevent initial Vibration
  // still needed after pulldown resistor?
  vibration.begin();

  // ESP32-s2 has different pins for the i2c headers/stemmaQT.
  // We want to use stemmaQT, so we need to set the pins here.
  Wire.setPins(PinDefs::i2cSda, PinDefs::i2cScl);

  DEBUG_INIT(9600);
  DEBUG_LN("Started!");

  if (!mcp.begin_I2C(MCP23XXX_ADDR, &Wire)) {
    DEBUG_LN("Error beginning MCP23017.");
    INFINITE_LOOP;
  }

  if (!eeprom.begin(EEPROM_ADDR)) {
    DEBUG_LN("Error beginning EEPROM I2C.");
    INFINITE_LOOP;
  }

  if (!rotary.begin()) {
    INFINITE_LOOP;
  }

  lightRods.begin();
  screen.begin();
  joystick.begin();
  leds.begin();
  inter.begin();
}

void loop(void) {
  inter.loop();
  leds.loop();
  lightRods.runCoroutine();
  viewManager.loop();
  vibration.runCoroutine();
}