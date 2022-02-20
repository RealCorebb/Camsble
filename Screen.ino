
// ------------------------- Screen -_,-

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 42, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_input_bits);
}
void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 42, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_schedule_bits);
}
void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 42, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_remote_bits);
}
FrameCallback frames[] = { drawFrame1,drawFrame2,drawFrame3 };
int frameCount = 3;
//

void initScreen(){
  ui.setTargetFPS(60);
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, frameCount);
  ui.setTimePerTransition(280);
  ui.disableAutoTransition();
  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();
}

void tickScreen(){
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    Serial.println(analogRead(4));
    delay(remainingTimeBudget);
  }
}