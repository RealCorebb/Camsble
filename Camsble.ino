// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
#include <Ticker.h>
#include "Button2.h"

Preferences preferences;

#define shutterS1 10
#define shutterS2 5

#define BUTTON_A_PIN  0
#define BUTTON_B_PIN  1
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

Ticker delayTimer;
Ticker triggerTimer;
Ticker scheduleTimer;
Ticker batteryTimer;

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
  setCpuFrequencyMhz(80);
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
  interValSwitch = preferences.getInt("interValSwitch", 0);
  bShutter = preferences.getInt("bShutter", 0);
  inputMode = preferences.getInt("inputMode", 0);

  buttonA.begin(BUTTON_A_PIN,INPUT_PULLUP);
  buttonA.setClickHandler(handler);
  buttonB.begin(BUTTON_B_PIN,INPUT_PULLUP);
  buttonB.setClickHandler(handler);
  buttonA.setPressedHandler(pressed);
  buttonA.setReleasedHandler(released);
  buttonB.setPressedHandler(pressed);
  buttonB.setReleasedHandler(released);  

  //attachInterrupt(INPUT_PIN,inputTrigger,FALLING);

  setInputInterrupt(inputMode);

  //initBLE();
  readBattery();
  batteryTimer.attach_ms(60000, readBattery);
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
  Serial.println("Shutter Triggered");
  strip.SetPixelColor(0, red);
  strip.Show();
  digitalWrite(shutterS1,LOW);
  digitalWrite(shutterS2,LOW);
  triggerTimer.once_ms(200,unPressShutter);
  bleTriggerShutter();
  shutterCount++;
}


int triggerCount = 0;
void inputTrigger(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    if(mode == 0){
    Serial.println("Input Triggered");
    triggerCount++;
    if(triggerCount >= triggerTimes){
      delayTimer.once_ms(triggerDelay,triggerShutter);
      triggerCount = 0;
    }
  }
  }
  last_interrupt_time = interrupt_time;
  
}

unsigned long time_now = 0;

void loop() {
  //Serial.println("loop");
  
  tickScreen();
  buttonA.loop();
  buttonB.loop();
  if(mode == 0){  //输入触发模式
    
  }
  if(mode == 1){  //Schedule模式
    //更新倒计时
    if(interValSwitch == 0){
        leftSec = interVal;
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
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
            if (btn == buttonA) {
              
            } else if (btn == buttonB) {
              
            }
            break;
        case DOUBLE_CLICK:
            if (btn == buttonA) {
              prevPage();
            } else if (btn == buttonB) {
              nextPage();
            }
            break;
        case TRIPLE_CLICK:
            Serial.print("triple ");
            break;
        case LONG_CLICK:
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
    detachInterrupt(INPUT_PIN);
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
    if(inputMode == 2){
      attachInterrupt(INPUT_PIN,inputTrigger,LOW);  
    }
    if(inputMode == 3){
      attachInterrupt(INPUT_PIN,inputTrigger,HIGH);  
    }
    if(inputMode == 4){
      attachInterrupt(INPUT_PIN,inputTrigger,CHANGE);  
    }
  }

/////////////////////////////////////////////////////////////////

void released(Button2& btn) {
  counter--;
}
