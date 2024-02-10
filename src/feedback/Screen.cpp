#include "./Screen.h"

Screen *screenPtr;
void setActiveViewCallback(uint8_t view) { screenPtr->setActiveView(view); }

Screen::Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr,
               Joystick *joystickPtr)
    : tft(Adafruit_ILI9341(PinDefs::screenCS, PinDefs::screenDC)),
      debugView(statePtr, &this->tft, joystickPtr, &setActiveViewCallback),
      radarView(statePtr, &this->tft, joystickPtr, &setActiveViewCallback) {
  this->mcp = mcpPtr;
  this->joystick = joystickPtr;
  this->state = statePtr;

  screenPtr = this;
}

void Screen::begin() {
  this->mcp->pinMode(PinDefs::mcp_screenDimmer, OUTPUT);
  this->setBrightness(LOW);

  // give TFT time to boot
  delay(250);
  this->tft.begin();
  this->tft.setRotation(3);

  DEBUG_BLOCK({
    // give TFT time to init
    delay(250);
    // read diagnostics
    uint8_t x = this->tft.readcommand8(ILI9341_RDMODE);
    DEBUG("Display Power Mode: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDMADCTL);
    DEBUG("MADCTL Mode: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDPIXFMT);
    DEBUG("Pixel Format: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDIMGFMT);
    DEBUG("Image Format: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDSELFDIAG);
    DEBUG("Self Diagnostic: 0x");
    DEBUG_LN(x, HEX);
  });
}

void Screen::loop() {
  // Switching view happens inside the views `loop` fn.
  // This means that passing in `viewChanged` then
  // then setting it to `false` at the end of this fn
  // immediately overrides the `true` inside `setActiveView`
  bool didChangeView = this->state->viewChanged;
  this->state->viewChanged = false;

  switch (this->state->activeView) {
  case STATE_VIEW_RADAR:
    this->radarView.loop(didChangeView);
    break;

  default:
  case STATE_VIEW_DEBUG:
    this->debugView.loop(didChangeView);
    break;
  }
}

void Screen::setBrightness(unsigned char brightness) {
  this->mcp->digitalWrite(PinDefs::mcp_screenDimmer, brightness);
  this->state->screenBrightness = brightness;
}

void Screen::toggleBrightness() {
  if (this->state->screenBrightness == LOW) {
    this->setBrightness(HIGH);
  } else {
    this->setBrightness(LOW);
  }
}

void Screen::setActiveView(uint8_t view) {
  this->state->activeView = view;
  this->state->viewChanged = true;
}