
// ------------------------- Screen -_,-

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 30, y + 14, Mode_Logo_width, Mode_Logo_height, Mode_input_bits);
  display->setFont(ArialMT_Plain_16);
  display->drawString(84,24,String(triggerCount));
  display->drawString(96, 30,String(triggerTimes));
  display->setFont(ArialMT_Plain_24);
  display->drawString(89,23,String("/"));
  switch (inputMode) {
        case 0:
          display->drawXbm(x + 34, y + 18, subMode_Logo_width, subMode_Logo_height, Falling_bits);
          break;
        case 1:
          display->drawXbm(x + 34, y + 18, subMode_Logo_width, subMode_Logo_height, Rising_bits);
          break;
        case 2:
          display->drawXbm(x + 34, y + 18, subMode_Logo_width, subMode_Logo_height, Low_bits);
          break;
        case 3:
          display->drawXbm(x + 34, y + 18, subMode_Logo_width, subMode_Logo_height, High_bits);
          break;
        case 4:
          display->drawXbm(x + 34, y + 18, subMode_Logo_width, subMode_Logo_height, Change_bits);
          break;
  }
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
  display->drawString(98, 54, batteryStatus);
  if(shutterCount<10){
    display->drawXbm(32, 56, Icon_width, Icon_height, Camera_bits);  
    display->drawString(46, 54,String(shutterCount));
  }
  else{
    display->drawString(42, 54,String(shutterCount));
  }
  if(isBLEEnable == 1){
    display->drawXbm(32, 10, Icon_width, Icon_height, BLE_bits); 
  }
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
  Serial.print("UI Trans to");
  Serial.println(mode);
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
