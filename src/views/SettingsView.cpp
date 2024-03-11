#include "./SettingsView.h"
using namespace ace_routine;

SettingsView::SettingsView(State *statePtr, Screen *screenPtr,
                           SetActiveViewPtr(setActiveViewPtr),
                           Adafruit_EEPROM_I2C *eepromPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->eeprom = eepromPtr;

  this->shouldRender = false;
  this->screen = 0;
  this->lastEeprom = 0;
}

void SettingsView::setup() { this->lastEeprom = this->eeprom->read(0x00); }

void SettingsView::handleSelect() {
  switch (this->screen) {
  case 0:
  default:
    // this->screen = this->cursorIndex + 1;
    this->eeprom->write(0x00, this->cursorIndex + 1);
    this->lastEeprom = this->cursorIndex + 1;

    this->cursorIndex = 0;
    break;
  }
}

uint8_t SettingsView::getButtonCount() {
  switch (this->screen) {
  case 0:
  default:
    return 3;
  }
}

void SettingsView::drawMainMenu() {
  this->drawTitle("SETTINGS");

  this->canvas->setCursor(0, 0);
  this->canvas->setTextSize(2);
  this->canvas->setTextColor(0xFFFF, 0x0000);
  this->canvas->print("Last: ");
  this->canvas->print(this->lastEeprom);

  this->drawButton(0, this->cursorIndex == 0, "Test1");
  this->drawButton(1, this->cursorIndex == 1, "Test2");
  this->drawButton(2, this->cursorIndex == 2, "Test3");
}

int SettingsView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->changeToMenu()) {
      COROUTINE_YIELD();
    }
    this->shouldRender = this->updateCursor(this->getButtonCount());

    if (!this->shouldRender && this->didSelect()) {
      this->shouldRender = true;
      this->handleSelect();
      COROUTINE_YIELD();
    }

    if (this->isInitialRender || this->shouldRender) {
      this->clearMainCanvas();

      switch (this->screen) {
      case 0:
      default:
        this->drawMainMenu();
        break;
      }

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}