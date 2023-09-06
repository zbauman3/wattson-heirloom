#include "./State.h"
#include <Arduino.h>

State::State() { this->interrupt = {.type = STATE_INTR_EMPTY}; };

bool State::hasInterrupt() { return this->interrupt.type != STATE_INTR_EMPTY; };