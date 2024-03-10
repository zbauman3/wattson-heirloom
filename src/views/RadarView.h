#include "../feedback/Leds.h"
#include "../feedback/LightRods.h"
#include "../models/State.h"
#include "../types.h"
#include "./BaseView.h"
#include <Arduino.h>

#ifndef RadarView_H
#define RadarView_H

#define PING_SIZE 16
#define CLOSE_PING_HEIGHT ((SCREEN_HEIGHT - 180) + PING_SIZE)
#define CLOSE_PING_WIDTH (CLOSE_PING_HEIGHT * 2)
#define CLOSE_PING_X1 ((SCREEN_WIDTH - CLOSE_PING_WIDTH) / 2)
#define CLOSE_PING_X2 (CLOSE_PING_X1 + CLOSE_PING_WIDTH)
#define CLOSE_PING_Y1 (SCREEN_HEIGHT - CLOSE_PING_HEIGHT)

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

  Leds *leds;
  LightRods *lightRods;

  void drawBackground();
  void drawPingCircle(int16_t x, int16_t y);
  void drawPings();
  bool drawWave();
  bool pingIsClose();

public:
  RadarView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr), Leds *ledsPtr,
            LightRods *lightRodsPtr);
  int runCoroutine() override;
  void cleanup() override;
};

#endif