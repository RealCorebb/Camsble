// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
#include <Ticker.h>
#include <EasyButton.h>

Preferences preferences;

#define shutterS1 10
#define shutterS2 5
#define inputPIN 3
//------------------------------- GLOBAL -_,-
int mode;
int triggerTimes;
int triggerDelay;
int interVal;
int schedule;
int bShutter;
int selfieDelay;

Ticker delayTimer;
Ticker scheduleTimer;

EasyButton inputButton(inputPIN);

#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "images.h"
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
  schedule = preferences.getInt("schedule", 0);
  bShutter = preferences.getInt("bShutter", 0);
  selfieDelay = preferences.getInt("selfieDelay", 0);

  inputButton.begin();
  inputButton.onPressedFor(0,inputTrigger);  

  //initBLE();

  if (inputButton.supportsInterrupt())
  {
    inputButton.enableInterrupt(inputISR);
    Serial.println("Button will be used through interrupts");
  }

  Serial.println("Characteristic defined! Now you can read it in your phone!");

  initScreen();
  Serial.println("initScreen Done");
  strip.Begin();
  strip.SetPixelColor(0, blue);
  strip.Show();
  Serial.println("Setup Done");
}

void inputISR()
{
  //When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function
  inputButton.read(); 
}

void triggerShutter(){
  Serial.println("Shutter Triggered");
  digitalWrite(shutterS1,LOW);
  delay(50);
  digitalWrite(shutterS1,HIGH);
}

void inputTrigger(){
  if(mode == 0){
    Serial.println("Input Triggered");
    delayTimer.once(triggerDelay,triggerShutter);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  //delay(200);
  //schedule++;
  //updateSchedule(schedule);
  //Serial.println(digitalRead(3));
  //char* sb = "sb";
  //String(millis()).toCharArray(sb,4);
  tickScreen();
  inputButton.update();
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
}

//utils

void changeModeUni(int newmode){
  preferences.putInt("mode", newmode);      
  Serial.println(String("Change Mode to:") + newmode);
  mode = newmode;
  ui.transitionToFrame(newmode);
}

