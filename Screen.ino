
// ------------------------- Screen -_,-

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 30, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_input_bits);
  display->setFont(ArialMT_Plain_16);
  display->drawString(84,23,String(triggerCount));
  display->drawString(96, 29,String(triggerTimes));
  display->setFont(ArialMT_Plain_24);
  display->drawString(89,22,String("/"));
}
void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 30, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_schedule_bits);
  display->setFont(ArialMT_Plain_24);
  display->drawString(92, 23,String(leftSec));
}
void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 42, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_remote_bits);
}
void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(Open_Sans_Regular_8);
  display->drawString(100, 54,readBattery());
}
FrameCallback frames[] = { drawFrame1,drawFrame2,drawFrame3 };
int frameCount = 3;
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;
//



void initScreen(){
  Serial.println("Init Screen");
  ui.setTargetFPS(60);
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, frameCount);
  ui.setOverlays(overlays, overlaysCount);
  ui.setTimePerTransition(280);
  ui.disableAutoTransition();
  // Initialising the UI will init the display too.
  ui.init();
  ui.transitionToFrame(mode);
  display.flipScreenVertically();
  hasScreen = 1;
}

void reconnectScreen(){
  Serial.println("Reconnect Screen");
  //ui.end();
 // ui.init();
  display.resetDisplay();
}

void tickScreen(){
  if(hasScreen == 1){
    int remainingTimeBudget = ui.update();
    if (remainingTimeBudget > 0) {
      // You can do some work here
      // Don't do stuff if you are below your
      // time budget.
      //Serial.println(remainingTimeBudget);
     // delay(remainingTimeBudget);
    }
  }
}