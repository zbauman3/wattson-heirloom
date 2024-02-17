#include "../models/State.h"
#include "../types.h"
#include "./BaseView.h"
#include <Arduino.h>

#ifndef RadarView_H
#define RadarView_H

#define PING_SIZE 16

class RadarPing : public ace_routine::Coroutine {
private:
  Coord pingEnd;
  Coord pingMoveAmt;

public:
  Coord pingCurrent;

  RadarPing();

  int runCoroutine() override;
};

class RadarView : public BaseView {
private:
  RadarPing ping1;
  RadarPing ping2;
  RadarPing ping3;
  int16_t waveRadius;

  void drawBackground();
  void drawPingCircle(int16_t x, int16_t y);
  void drawPings();
  void drawWave();

public:
  RadarView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
};

#endif