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
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
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

uint32_t LightRods::getTriggerColor(uint8_t intensity, float percent) {
  uint8_t realRed, realGreen, realBlue;
  switch (this->state->eepromState.lights_theme) {
  case 1: // Green
    realRed = 0;
    realGreen = intensity;
    realBlue = 0;
    break;
  case 2: // Blue
    realRed = 0;
    realGreen = 0;
    realBlue = intensity;
    break;
  case 3: // Cyan
    realRed = 0;
    realGreen = intensity;
    realBlue = intensity;
    break;
  case 4: // Magenta
    realRed = intensity;
    realGreen = 0;
    realBlue = intensity;
    break;
  case 5: // Yellow
    realRed = intensity;
    realGreen = intensity;
    realBlue = 0;
    break;
  case 6: // White
    realRed = intensity;
    realGreen = intensity;
    realBlue = intensity;
    break;
  case 0: // Red
  default:
    realRed = intensity;
    realGreen = 0;
    realBlue = 0;
    break;
  }

  return this->adjustColorByPower(realRed, realGreen, realBlue, percent);
}

int LightRods::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == LIGHTS_PATTERN_RADAR) {

      for (this->i = 0; this->i < (NEOPIXEL_COUNT / 2) + 5; this->i++) {
        if (this->i < (NEOPIXEL_COUNT / 2)) {
          this->neopixels.setPixelColor(
              this->i, this->getTriggerColor(
                           this->routineVariation == 1 ? 255 : 125, 0.332));
          this->neopixels.setPixelColor(
              NEOPIXEL_COUNT - (this->i + 1),
              this->getTriggerColor(this->routineVariation == 1 ? 255 : 125,
                                    0.332));
        }
        this->neopixels.setPixelColor(this->i - 5,
                                      this->adjustColorByPower(0, 0, 0, 1));

        this->neopixels.setPixelColor((NEOPIXEL_COUNT - (this->i + 1)) + 5,
                                      this->adjustColorByPower(0, 0, 0, 1));

        this->neopixels.show();
        COROUTINE_DELAY(50);
      }

      this->clear();
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
    } else if (this->routine == LIGHTS_PATTERN_TRIGGER_INIT) {
      for (this->i = 0; this->i < 3; this->i++) {
        this->neopixels.clear();

        for (this->j = this->i; this->j < NEOPIXEL_COUNT; this->j += 3) {
          this->neopixels.setPixelColor(this->j,
                                        this->getTriggerColor(125, 0.166));
        }

        this->neopixels.show();
        COROUTINE_DELAY(50);
      }
    } else if (this->routine == LIGHTS_PATTERN_TRIGGER_LOWPOWER) {
      this->neopixels.clear();

      for (this->i = 0; this->i < NEOPIXEL_COUNT / 2; this->i++) {
        this->neopixels.setPixelColor(this->i,
                                      this->getTriggerColor(125, 0.332));

        this->neopixels.setPixelColor(NEOPIXEL_COUNT - (this->i + 1),
                                      this->getTriggerColor(125, 0.332));

        this->neopixels.show();
        COROUTINE_DELAY(20);
      }

      for (this->i = 125; this->i <= 245; this->i += 10) {
        this->neopixels.fill(this->getTriggerColor(this->i, 0.332));
        this->neopixels.show();
        COROUTINE_DELAY(15);
      }

      for (this->i = 255; this->i > 100; this->i -= 15) {
        this->neopixels.fill(this->getTriggerColor(this->i, 0.332));
        this->neopixels.show();
        COROUTINE_DELAY(10);
      }

      this->clear();
    } else if (this->routine == LIGHTS_PATTERN_TRIGGER_BUILD) {
      this->neopixels.clear();

      for (this->i = 0; this->i < NEOPIXEL_COUNT / 2; this->i++) {
        this->neopixels.setPixelColor(this->i,
                                      this->getTriggerColor(125, 0.332));

        this->neopixels.setPixelColor(NEOPIXEL_COUNT - (this->i + 1),
                                      this->getTriggerColor(125, 0.332));

        this->neopixels.show();
        COROUTINE_DELAY(100);
      }

      while (true) {
        for (this->i = 125; this->i <= 245; this->i += 10) {
          this->neopixels.fill(this->getTriggerColor(this->i, 0.332));
          this->neopixels.show();
          COROUTINE_DELAY(25);
        }

        for (this->i = 255; this->i >= 145; this->i -= 10) {
          this->neopixels.fill(this->getTriggerColor(this->i, 0.332));
          this->neopixels.show();
          COROUTINE_DELAY(25);
        }

        COROUTINE_YIELD();
      }
    } else if (this->routine == LIGHTS_PATTERN_TRIGGER_HIGHPOWER) {
      for (this->j = 0; this->j < 5; this->j++) {
        if (this->j % 2 == 0) {
          for (this->k = 0; this->k < 2; this->k++) {
            this->neopixels.clear();
            for (this->i = 0; this->i < NEOPIXEL_COUNT / 2; this->i++) {
              this->neopixels.setPixelColor(this->i,
                                            this->getTriggerColor(255, 0.332));

              this->neopixels.setPixelColor(NEOPIXEL_COUNT - (this->i + 1),
                                            this->getTriggerColor(255, 0.332));

              this->neopixels.show();
              COROUTINE_DELAY(8);
            }
          }
        } else {
          this->neopixels.clear();

          for (this->i = 0; this->i < 3; this->i++) {
            this->neopixels.clear();

            for (this->k = this->i; this->k < NEOPIXEL_COUNT; this->k += 3) {
              this->neopixels.setPixelColor(this->k,
                                            this->getTriggerColor(255, 0.332));
            }

            this->neopixels.show();
            COROUTINE_DELAY(50);
          }
        }
      }

      for (this->i = 255; this->i >= 10; this->i -= 10) {
        this->neopixels.fill(this->getTriggerColor(this->i, 0.332));
        this->neopixels.show();
        COROUTINE_DELAY(50);
      }

      this->clear();
    }

    COROUTINE_YIELD();
  }
}

bool LightRods::changeRoutine(uint8_t which, bool restart) {
  bool isChange = this->routine != which;
  this->routine = which;

  if (this->routine == LIGHTS_PATTERN_TRIGGER_INIT ||
      this->routine == LIGHTS_PATTERN_TRIGGER_BUILD ||
      this->routine == LIGHTS_PATTERN_TRIGGER_HIGHPOWER ||
      this->routine == LIGHTS_PATTERN_TRIGGER_LOWPOWER) {
    this->state->isInTriggerRoutine = true;
  }

  if (isChange || restart) {
    this->neopixels.fill(neopixels.Color(0, 0, 0));
    this->neopixels.show();
    this->reset();
    return true;
  }
  return false;
}

void LightRods::clear() {
  this->state->isInTriggerRoutine = false;
  this->routine = 0;
  this->routineVariation = 0;
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
  this->reset();
}

void LightRods::radarPulse(bool danger) {
  if (this->state->isInTriggerRoutine) {
    return;
  }

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

void LightRods::triggerInit() {
  this->changeRoutine(LIGHTS_PATTERN_TRIGGER_INIT, false);
}

void LightRods::triggerBuild() {
  this->changeRoutine(LIGHTS_PATTERN_TRIGGER_BUILD, false);
}

void LightRods::triggerHighPower() {
  this->changeRoutine(LIGHTS_PATTERN_TRIGGER_HIGHPOWER, false);
}

void LightRods::triggerLowPower() {
  this->changeRoutine(LIGHTS_PATTERN_TRIGGER_LOWPOWER, false);
}

uint8_t LightRods::adjustBrightness(uint8_t color, float percent) {
  return max((uint8_t)ceil(color * percent), (uint8_t)0);
}

float LightRods::brightnessToPercent(uint8_t brightness) {
  return (float)brightness / (float)255;
}
