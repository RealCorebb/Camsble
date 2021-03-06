// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
#include <Ticker.h>
#include "Button2.h"

Preferences preferences;

#define shutterS1 10
#define shutterS2 5

#define BUTTON_A_PIN  1
#define BUTTON_B_PIN  0
#define INPUT_PIN  3

#define MAXPAGE 2
//------------------------------- GLOBAL -_,-
int mode;
int triggerTimes;
int triggerDelay;
int interVal;
int interValSwitch;
int bShutter;
int inputMode;
int hasScreen = 0;
int leftSec = 0;
int shutterCount = 0;
int isBLEEnable = 0;
byte counter = 0;
int changeInterValStep = 0;

Ticker delayTimer;
Ticker triggerTimer;
Ticker scheduleTimer;
Ticker batteryTimer;
Ticker cinterValTimer;

Button2 buttonA, buttonB;
//EasyButton inputScreen(7,35,false,true);

#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "images.h"
#include "fonts.h"
SSD1306Wire display(0x3c, 7, 6);
OLEDDisplayUi ui ( &display );
// -------------------------
#include <NeoPixelBus.h>
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(1, 8);
#define colorSaturation 128
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor purple(90, 28, 117);
RgbColor yellow(117, 116, 19);
RgbColor white(colorSaturation);
RgbColor black(0);
//-------------------

void setup() {
  //setCpuFrequencyMhz(80);
  Serial.println("initScreen Done");
  strip.Begin();
  strip.SetPixelColor(0, blue);
  strip.Show();

  Serial.println("Setup...");
  Serial.begin(115200);
  
  pinMode(shutterS1,OUTPUT);
  pinMode(shutterS2,OUTPUT);
  pinMode(INPUT_PIN,INPUT_PULLUP);

  digitalWrite(shutterS1,HIGH);
  digitalWrite(shutterS2,HIGH);

  preferences.begin("camsble", false);
  mode = preferences.getInt("mode", 0);
  triggerTimes = preferences.getInt("triggerTimes", 1);
  triggerDelay = preferences.getInt("triggerDelay", 0);
  interVal = preferences.getInt("interVal", 5000);
  interValSwitch = preferences.getInt("interValSwitch", 1);
  bShutter = preferences.getInt("bShutter", 0);
  inputMode = preferences.getInt("inputMode", 0);

  buttonA.begin(BUTTON_A_PIN,INPUT_PULLUP,false);
  buttonA.setClickHandler(handler);
  buttonB.begin(BUTTON_B_PIN,INPUT_PULLUP,false);
  buttonB.setClickHandler(handler);
  buttonA.setDoubleClickHandler(handler);
  buttonB.setDoubleClickHandler(handler);
  buttonA.setLongClickDetectedHandler(handler);
  buttonB.setLongClickDetectedHandler(handler);
  buttonA.setPressedHandler(pressed);
  buttonA.setReleasedHandler(released);
  buttonB.setPressedHandler(pressed);
  buttonB.setReleasedHandler(released);  

  //attachInterrupt(INPUT_PIN,inputTrigger,FALLING);

  setInputInterrupt(inputMode);

  //initBLE();
  readBattery();
  batteryTimer.attach_ms(60000, readBattery);
  cinterValTimer.attach_ms(150,changeInterval);
  initScreen();
  Serial.println("Setup Done");
  Serial.println(mode);
}


void unPressShutter(){
  digitalWrite(shutterS1,HIGH);
  digitalWrite(shutterS2,HIGH);
  if(mode == 0){
    strip.SetPixelColor(0, blue);
    strip.Show();
  }
  if(mode == 1){
    strip.SetPixelColor(0, purple);
    strip.Show();
  }
}

void triggerShutter(){  
  //Serial.println("Shutter Triggered");
  strip.SetPixelColor(0, red);
  strip.Show();
  digitalWrite(shutterS1,LOW);
  digitalWrite(shutterS2,LOW);
  triggerTimer.once_ms(200,unPressShutter);
  bleTriggerShutter();
  shutterCount++;
}

void holdShutter(){
  strip.SetPixelColor(0, red);
  strip.Show();
  digitalWrite(shutterS1,LOW);
  digitalWrite(shutterS2,LOW);
  bleTriggerShutter();
  strip.SetPixelColor(0, red);
  strip.Show();
}


int triggerCount = 0;

long debouncing_time = 250; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
void inputTrigger(){

  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    if(mode == 0){
      triggerCount++;
      if(triggerCount >= triggerTimes){
        delayTimer.once_ms(triggerDelay,triggerShutter);
        triggerCount = 0;
      }
    }
    last_micros = micros();
  }
}

unsigned long time_now = 0;
bool isHolding = false;
void loop() {
  //Serial.println("loop");
  
  tickScreen();
  buttonA.loop();
  buttonB.loop();
  if(mode == 0){  //输入触发模式
    if(inputMode == 2){ //LOW
        if(digitalRead(INPUT_PIN) == LOW){
            if(!isHolding){
              holdShutter();
              isHolding = true;
            }
          }
         else{
            if(isHolding){
              unPressShutter();
              isHolding =false;
            }
          }
      }
     if(inputMode == 3){ //LOW
        if(digitalRead(INPUT_PIN) == HIGH){
            if(!isHolding){
              holdShutter();
              isHolding = true;
            }
          }
         else{
            if(isHolding){
              unPressShutter();
              isHolding =false;
            }
          }
      }
  }
  if(mode == 1){  //Schedule模式
    //更新倒计时
    if(interValSwitch == 0){
        leftSec = interVal/1000;
      }
    else{
      leftSec = ((interVal - (millis() - time_now))+999)/1000;
     // Serial.println(leftSec);
      if(leftSec < 3){
        strip.SetPixelColor(0, yellow);
        strip.Show();
      }
      if(millis() - time_now > interVal){
        time_now = millis();
        triggerShutter();
      }
    }
  }
  if(mode == 2){   //无线遥控模式
    if(bShutter == 1){
      digitalWrite(shutterS1,LOW);    
      strip.SetPixelColor(0, red);
      strip.Show();
    }    
    else{
      digitalWrite(shutterS1,HIGH); 
      strip.SetPixelColor(0, green);
      strip.Show();
    }
  }
 //Serial.print(digitalRead(6));
 //Serial.println(digitalRead(7));
}

//utils

void changeModeUni(int newmode){
  preferences.putInt("mode", newmode);      
  Serial.println(String("Change Mode to:") + newmode);
  mode = newmode;
  shutterCount = 0;
  if(mode == 0){
    strip.SetPixelColor(0, blue);
    strip.Show();
  }
  if(mode == 1){
    strip.SetPixelColor(0, purple);
    strip.Show();
  }
  ui.transitionToFrame(newmode);
}


unsigned long last_battery_time = 0;

String batteryStatus = "100%";

void readBattery(){
  uint8_t percentage = 100;
  float voltage = analogRead(4) / 4096.0 * 5.9;      // LOLIN D32 (no voltage divider need already fitted to board.or NODEMCU ESP32 with 100K+100K voltage divider
  Serial.println("Voltage = " + String(voltage));
  percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  if (voltage > 4.19) percentage = 100;
  else if (voltage <= 3.50) percentage = 0;
  batteryStatus = String(percentage)+"%";
}

void handler(Button2& btn) {
    Serial.println("Button Click");
    switch (btn.getType()) {
        case single_click:
            if (btn == buttonA) {
              switch(mode){
                case 0:
                  triggerTimes = triggerTimes - 1;
                  if(triggerTimes < 1) triggerTimes = 1;
                  preferences.putInt("triggerTimes", triggerTimes);  
                  break;
                case 1:
                  interValSwitch = 0;
                  preferences.putInt("interValSwitch", 0);  
                  break;
                case 2:
                  inputTrigger();
                  break;
              }
                  
            } else if (btn == buttonB) {
                switch(mode){
                  case 0:
                    triggerTimes = triggerTimes + 1;
                    preferences.putInt("triggerTimes", triggerTimes);  
                    break;
                  case 1:
                    interValSwitch = 1;
                    preferences.putInt("interValSwitch", 1);  
                    break;
                  case 2:
                    inputTrigger();
                    break;
                }
            }
            break;
        case double_click:
            if (btn == buttonA) {
              prevPage();
            } else if (btn == buttonB) {
              nextPage();
            }
            break;
        case triple_click:
            Serial.print("triple ");
            changeBLE();
            break;
        case long_click:
          Serial.println("long click");
          if (btn == buttonA) {
              switch(mode){
                case 0:
                  inputMode = inputMode - 1;
                  if(inputMode <0) inputMode = 4;
                  changeInterrupt(inputMode);
                  break;
                case 1:
                  changeInterValStep = -1000;
                  break;
                case 2:
                  changeBLE();
              }
                  
            } else if (btn == buttonB) {
                switch(mode){
                  case 0:
                    inputMode = inputMode + 1;
                    if(inputMode >4 ) inputMode = 0;
                    changeInterrupt(inputMode);
                    break;
                  case 1:
                    changeInterValStep = 1000;
                    break;
                  case 2:
                    changeBLE();
                }
            }
            break;
    }
}

void prevPage(){
  Serial.println("prev Page");
  int newmode = mode-1;
  if(newmode<0) newmode = MAXPAGE;
  changeModeUni(newmode);
}

void nextPage(){
  Serial.println("next Page");
  int newmode = mode+1;
  if(newmode>MAXPAGE) newmode = 0;
  changeModeUni(newmode);
}

void changeBLE(){
  Serial.println("Change BLE");
  if(isBLEEnable == 0) initBLE();
  else deinitBLE();  
}

void pressed(Button2& btn) {
  counter++;
  if (counter == 2) {
    changeBLE();
  }
}

void changeInterrupt(int inputMode){   //0 FALLING  //1 RISING //2 LOW  //3 HIGH  //4 CHANGE
    Serial.print("Change Interrupt to:");
    Serial.println(inputMode);
    detachInterrupt(INPUT_PIN);
    unPressShutter();
    isHolding =false;
    setInputInterrupt(inputMode);
    preferences.putInt("inputMode", inputMode);  
 }

void setInputInterrupt(int input){
    if(inputMode == 0){
      attachInterrupt(INPUT_PIN,inputTrigger,FALLING);
    }
    if(inputMode == 1){
      attachInterrupt(INPUT_PIN,inputTrigger,RISING);
    }
    if(inputMode == 4){
      attachInterrupt(INPUT_PIN,inputTrigger,CHANGE);  
    }
  }

void changeInterval(){
      int lastInterVal = interVal;
      interVal = interVal + changeInterValStep;
      if(lastInterVal != interVal){
        preferences.putInt("interVal", interVal);  
      }
  }
/////////////////////////////////////////////////////////////////

void released(Button2& btn) {
  counter--;
  changeInterValStep = 0;
}
