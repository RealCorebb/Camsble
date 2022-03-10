// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
#include <Ticker.h>
#include <EasyButton.h>

Preferences preferences;

#define shutterS1 10
#define shutterS2 5
#define inputPIN 3
#define buttonLPIN 0
#define buttonRPIN 1
#define MAXPAGE 2
//------------------------------- GLOBAL -_,-
int mode;
int triggerTimes;
int triggerDelay;
int interVal;
int interValSwitch;
int bShutter;
int selfieDelay;
int hasScreen = 0;
int leftSec = 0;
int shutterCount = 0;

Ticker delayTimer;
Ticker scheduleTimer;

EasyButton inputButton(inputPIN);
EasyButton inputButtonL(buttonLPIN);
EasyButton inputButtonR(buttonRPIN);
//EasyButton inputScreen(7,35,false,true);

#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "images.h"
#include "fonts.h"
SSD1306Wire display(0x3c, 6, 7);
OLEDDisplayUi ui ( &display );
// -------------------------
#include <NeoPixelBus.h>
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(1, 8);
#define colorSaturation 128
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
//-------------------

void setup() {
  Serial.println("initScreen Done");
  strip.Begin();
  strip.SetPixelColor(0, blue);
  strip.Show();

  Serial.println("Setup...");
  Serial.begin(115200);
  
  pinMode(shutterS1,OUTPUT);
  pinMode(shutterS2,OUTPUT);

  digitalWrite(shutterS1,HIGH);
  digitalWrite(shutterS2,HIGH);

  preferences.begin("camsble", false);
  mode = preferences.getInt("mode", 0);
  triggerTimes = preferences.getInt("triggerTimes", 1);
  triggerDelay = preferences.getInt("triggerDelay", 0);
  interVal = preferences.getInt("interVal", 5000);
  interValSwitch = preferences.getInt("interValSwitch", 0);
  bShutter = preferences.getInt("bShutter", 0);
  selfieDelay = preferences.getInt("selfieDelay", 0);

  inputButton.begin();
  inputButtonL.begin();
  inputButtonR.begin();
  inputButton.onPressedFor(0,inputTrigger);  
  inputButtonL.onPressedFor(0,prevPage);
  inputButtonR.onPressedFor(0,nextPage);

  initBLE();

  inputButton.enableInterrupt(inputISR);
  inputButtonL.enableInterrupt(buttonLISR);
  inputButtonR.enableInterrupt(buttonRISR);
  Serial.println("Characteristic defined! Now you can read it in your phone!");



  initScreen();
  Serial.println("Setup Done");
  Serial.println(mode);
}

void inputISR()
{
  //When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function
  inputButton.read(); 
}
void buttonLISR(){
  inputButtonL.read();
}
void buttonRISR(){
  inputButtonR.read();
}

void triggerShutter(){
  Serial.println("Shutter Triggered");
  digitalWrite(shutterS1,LOW);
  bleTriggerShutter();
  delay(50);
  digitalWrite(shutterS1,HIGH);
  shutterCount++;
}

int triggerCount = 0;
void inputTrigger(){
  if(mode == 0){
    Serial.println("Input Triggered");
    triggerCount++;
    if(triggerCount >= triggerTimes){
      delayTimer.once(triggerDelay,triggerShutter);
      triggerCount = 0;
    }
  }
}

unsigned long time_now = 0;

void loop() {
  //Serial.println("loop");
  
  tickScreen();
  inputButton.update();
  inputButtonL.update();
  inputButtonR.update();
  if(mode == 0){
    strip.SetPixelColor(0, black);
    strip.Show();
  }
  if(mode == 1){
    //更新倒计时
    leftSec = ((interVal - (millis() - time_now))+999)/1000;
   // Serial.println(leftSec);
    if(millis() - time_now > interVal){
      time_now = millis();
      
      triggerShutter();
    }
  }
  if(mode == 2){   
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
  ui.transitionToFrame(newmode);
}

String readBattery(){
  uint8_t percentage = 100;
  float voltage = analogRead(4) / 4096.0 * 5.9;      // LOLIN D32 (no voltage divider need already fitted to board.or NODEMCU ESP32 with 100K+100K voltage divider
  //Serial.println("Voltage = " + String(voltage));
  percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  if (voltage > 4.19) percentage = 100;
  else if (voltage <= 3.50) percentage = 0;
  return String(percentage)+"%";
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
