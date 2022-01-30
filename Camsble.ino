// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
#include <Ticker.h>
#include <EasyButton.h>

Preferences preferences;

#define shutterS1 10
#define shutterS2 5
#define inputPIN 19
//------------------------------- GLOBAL -_,-
int mode;
int triggerTimes;
int triggerDelay;
int interVal;
int schedule;
int bShutter;
int selfieDelay;

Ticker delayTimer;

EasyButton inputButton(inputPIN);
// -------------------------


void setup() {
  Serial.begin(115200);
  
  pinMode(shutterS1,OUTPUT);
  pinMode(shutterS2,OUTPUT);

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

  initBLE();

  if (inputButton.supportsInterrupt())
  {
    inputButton.enableInterrupt(inputISR);
    Serial.println("Button will be used through interrupts");
  }

  Serial.println("Characteristic defined! Now you can read it in your phone!");
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
  //delay(50);
  //Serial.println(digitalRead(3));
  //char* sb = "sb";
  //String(millis()).toCharArray(sb,4);
  inputButton.update();
}
