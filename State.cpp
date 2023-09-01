#include "./State.h"
#include <Arduino.h>

State::State() { this->interrupt = {.type = STATE_INTR_EMPTY}; };