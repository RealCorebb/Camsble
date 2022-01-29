// MODE  0 输入触发模式  1 Schedule模式    2 B门模式

#include <Preferences.h>
Preferences preferences;

//------------------------------- GLOBAL -_,-
int mode;
int triggerTimes;
int triggerDelay;
int interVal;
int schedule;
int bShutter;
int selfieDelay;

// -------------------------


void setup() {
  Serial.begin(115200);
 

  preferences.begin("camsble", false);
  mode = preferences.getInt("mode", 0);
  triggerTimes = preferences.getInt("triggerTimes", 1);
  triggerDelay = preferences.getInt("triggerDelay", 0);
  interVal = preferences.getInt("interVal", 5000);
  schedule = preferences.getInt("schedule", 0);
  bShutter = preferences.getInt("bShutter", 0);
  selfieDelay = preferences.getInt("selfieDelay", 0);

  initBLE();

  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void inputTrigger(){
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  //char* sb = "sb";
  //String(millis()).toCharArray(sb,4);
  
}
