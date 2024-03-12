#include "./LightRods.h"
using namespace ace_routine;

LightRods::LightRods(State *statePtr)
    : neopixels(Adafruit_NeoPixel(NEOPIXEL_COUNT, PinDefs::neopixels,
                                  NEO_GRB + NEO_KHZ800)) {
  this->state = statePtr;
  this->routine = 0;
  this->routineVariation = 0;
  this->rainbowHue = 0;
  this->rainbowSpeed = 0;
  this->rainbowDirection = false;
}

void LightRods::begin() {
  this->neopixels.begin();
  this->neopixels.setBrightness(30);
  this->off();
}

uint32_t LightRods::adjustColorByPower(uint8_t r, uint8_t g, uint8_t b,
                                       float percent) {
  if (this->state->mcp_plug) {
    return neopixels.Color(r, g, b);
  }

  return neopixels.Color(LightRods::adjustBrightness(r, percent),
                         LightRods::adjustBrightness(g, percent),
                         LightRods::adjustBrightness(b, percent));
}

int LightRods::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == LIGHTS_PATTERN_RADAR) {
      this->i = 0;
      while (this->i < NEOPIXEL_COUNT + 5) {
        if (this->routineVariation == 1) {
          this->neopixels.setPixelColor(
              i, this->adjustColorByPower(255, 100, 0, 0.166));
        } else {
          this->neopixels.setPixelColor(
              i, this->adjustColorByPower(0, 180, 255, 0.166));
        }
        this->neopixels.setPixelColor(i - 5,
                                      this->adjustColorByPower(0, 0, 0, 0.166));
        this->neopixels.show();
        COROUTINE_DELAY(50);
        i++;
      }

      this->off();
      this->routine = 0;
    } else if (this->routine == LIGHTS_PATTERN_RAINBOW) {
      // Hue of first pixel runs 5 complete loops through the color wheel.
      // Color wheel has a range of 65536 but it's OK if we roll over.
      this->neopixels.rainbow(this->rainbowHue, 1, 255, this->routineVariation,
                              true);
      this->neopixels.show();
      if (this->rainbowSpeed == 0) {
        COROUTINE_YIELD();
      } else {
        COROUTINE_DELAY(this->rainbowSpeed);
      }
      this->rainbowHue =
          this->rainbowHue + (this->rainbowDirection ? 256 : -256);
    }

    COROUTINE_YIELD();
  }
}

void LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

bool LightRods::changeRoutine(uint8_t which, bool restart) {
  bool isChange = this->routine != which;
  this->routine = which;
  if (isChange || restart) {
    this->off();
    this->reset();
    return true;
  }
  return false;
}

void LightRods::clear() {
  this->routine = 0;
  this->routineVariation = 0;
  this->off();
  this->reset();
}

void LightRods::radarPulse(bool danger) {
  this->routineVariation = danger ? 1 : 0;
  this->changeRoutine(LIGHTS_PATTERN_RADAR, true);
}

void LightRods::rainbow(uint8_t brightness, uint16_t speed, bool direction) {
  this->routineVariation = brightness;
  this->rainbowSpeed = speed;
  this->rainbowDirection = direction;
  if (this->changeRoutine(LIGHTS_PATTERN_RAINBOW, false)) {
    this->rainbowHue = 0;
  }
}

void LightRods::solid(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness,
                      uint8_t portion) {
  this->routine = 0;
  this->routineVariation = 0;
  this->reset();

  float percent = LightRods::brightnessToPercent(brightness);

  uint32_t adjustedColor =
      neopixels.Color(LightRods::adjustBrightness(r, percent),
                      LightRods::adjustBrightness(g, percent),
                      LightRods::adjustBrightness(b, percent));

  if (portion == 2) {
    this->neopixels.fill(adjustedColor);
  } else {
    for (uint8_t i = 0; i < NEOPIXEL_COUNT; i++) {
      if ((portion == 0 && i < NEOPIXEL_COUNT / 2) ||
          (portion == 1 && i >= NEOPIXEL_COUNT / 2)) {
        this->neopixels.setPixelColor(i, adjustedColor);
      } else {
        this->neopixels.setPixelColor(i, neopixels.Color(0, 0, 0));
      }
    }
  }
  this->neopixels.show();
}

uint8_t LightRods::adjustBrightness(uint8_t color, float percent) {
  return max((uint8_t)ceil(color * percent), (uint8_t)0);
}

float LightRods::brightnessToPercent(uint8_t brightness) {
  return (float)brightness / (float)255;
}
