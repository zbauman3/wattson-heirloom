#include "./Screen.h"

Screen::Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr)
    : tft(Adafruit_ILI9341(PinDefs::screenCS, PinDefs::screenDC)) {
  this->mcp = mcpPtr;
  this->state = statePtr;
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
