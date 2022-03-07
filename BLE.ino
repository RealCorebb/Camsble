bool isConnected = false;

//---------------------------------   BLE -_,-
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "BLEHIDDevice.h"
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#define SERVICE_UUID        "45c424d1-adee-4a3d-b508-50d3acee84ad"

//---------------------------------
BLECharacteristic modeCs("d6b1d851-f38b-4a40-ab1a-323dca8b59c0", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic triggerTimesCs("18a09d26-50df-4539-b0c5-5cc8190dfac3", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic triggerDelayCs("2286b0e0-0fd4-470d-b07d-c2a04cac41c3", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic interValCs("8d4f535a-ec08-4957-bde7-fe0d02fa235f", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic interValSwitchCs("f3ab231f-d13c-49bb-a2dc-94bfbb1237cf", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic bShutterCs("203e69eb-471b-40dc-8d75-7824e112165b", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic selfieDelayCs("62f876a1-fbe9-4524-b548-6c3d1df6c4ad", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

//--------------------------------- HID -_,-

// Report IDs:
#define KEYBOARD_ID 0x01
#define MEDIA_KEYS_ID 0x02
BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;
BLECharacteristic* inputMediaKeys;


//---------------------------------   Callback -_,-
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {      
    isConnected = true;
    Serial.println("BLE Connected");
  };
  void onDisconnect(BLEServer* pServer) {
    isConnected = false;
    Serial.println("BLE Disconnected");
    BLEDevice::startAdvertising();
  }
};

class modeCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      changeModeUni(String(value.c_str()).toInt());
  }
};

class triggerTimesCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      Serial.println(value.c_str());
      triggerTimes = String(value.c_str()).toInt();
      preferences.putInt("triggerTimes", triggerTimes);      
      Serial.println(String("Change triggerTimes to:") + triggerTimes);
  }
};

class triggerDelayCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      triggerDelay = String(value.c_str()).toInt();
      preferences.putInt("triggerDelay", triggerDelay);      
      Serial.println(String("Change triggerDelay to:") + triggerDelay);
  }
};

class interValCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      interVal = String(value.c_str()).toInt();
      preferences.putInt("interVal", interVal);      
      Serial.println(String("Change interVal to:") + interVal);
  }
};

class interValSwitchCsCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      interValSwitch = String(value.c_str()).toInt();
      preferences.putInt("interValSwitch", interValSwitch);      
      Serial.println(String("Change interValSwitch to:") + interValSwitch);
  }
};

class bShutterCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      bShutter = String(value.c_str()).toInt();
      preferences.putInt("bShutter", bShutter);      
      Serial.println(String("Change bShutter to:") + bShutter);
  }
};

class selfieDelayCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      selfieDelay = String(value.c_str()).toInt();
      preferences.putInt("selfieDelay", selfieDelay);      
      Serial.println(String("Change selfieDelay to:") + selfieDelay);
  }
};

 class MyOutputCallbacks : public BLECharacteristicCallbacks {
 void onWrite(BLECharacteristic* me){
    uint8_t* value = (uint8_t*)(me->getValue().c_str());
    
  }
};

//-----------------------------------

static const uint8_t hidReportDescriptor[] = {
      USAGE_PAGE(1),      0x01,       // Generic Desktop Ctrls
      USAGE(1),           0x06,       // Keyboard
      COLLECTION(1),      0x01,       // Application
      REPORT_ID(1),       0x01,        //   Report ID (1)
      USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
      USAGE_MINIMUM(1),   0xE0,
      USAGE_MAXIMUM(1),   0xE7,
      LOGICAL_MINIMUM(1), 0x00,
      LOGICAL_MAXIMUM(1), 0x01,
      REPORT_SIZE(1),     0x01,       //   1 byte (Modifier)
      REPORT_COUNT(1),    0x08,
      HIDINPUT(1),           0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
      REPORT_COUNT(1),    0x01,       //   1 byte (Reserved)
      REPORT_SIZE(1),     0x08,
      HIDINPUT(1),           0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
      REPORT_COUNT(1),    0x06,       //   6 bytes (Keys)
      REPORT_SIZE(1),     0x08,
      LOGICAL_MINIMUM(1), 0x00,
      LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
      USAGE_MINIMUM(1),   0x00,
      USAGE_MAXIMUM(1),   0x65,
      HIDINPUT(1),           0x00,       //   Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
      REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
      REPORT_SIZE(1),     0x01,
      USAGE_PAGE(1),      0x08,       //   LEDs
      USAGE_MINIMUM(1),   0x01,       //   Num Lock
      USAGE_MAXIMUM(1),   0x05,       //   Kana
      HIDOUTPUT(1),          0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
      REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
      REPORT_SIZE(1),     0x03,
      HIDOUTPUT(1),          0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
      END_COLLECTION(0)
    };

typedef uint8_t MediaKeyReport[2];
const MediaKeyReport KEY_MEDIA_VOLUME_DOWN = {64, 0};
uint8_t buttons = 0;

void bleTriggerShutter(){
  Serial.println("BLE Trigger Shutter");
  /*
  inputMediaKeys->setValue((uint8_t*)KEY_MEDIA_VOLUME_DOWN, sizeof(MediaKeyReport));
  inputMediaKeys->notify();
  uint8_t msg1[] = {0x0, 0x0, 0x0, 0x0,0x0,0x0,0x0,0x0};  

      inputMediaKeys->setValue(msg1,sizeof(msg1));
      inputMediaKeys->notify();

      */

    const char* hello = "Hello world from esp32 hid keyboard!!!\n";

    while(*hello){
      KEYMAP map = keymap[(uint8_t)*hello];
      uint8_t msg[] = {map.modifier || buttons, 0x0, map.usage, 0x0,0x0,0x0,0x0,0x0};
      input->setValue(msg,sizeof(msg));
      input->notify();
      hello++;
      uint8_t msg1[] = {0x0, 0x0, 0x0, 0x0,0x0,0x0,0x0,0x0};

      input->setValue(msg1,sizeof(msg1));
      input->notify();
      delay(10);
    }  
  
}

//---------------------------------- Init BLE -_,-
void initBLE(){
  
  Serial.println("Starting BLE work!");
  BLEDevice::init("SBCamsble");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *camsbleService = pServer->createService(BLEUUID(SERVICE_UUID),30,0);

  camsbleService->addCharacteristic(&modeCs);
  modeCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&triggerTimesCs);
  triggerTimesCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&triggerDelayCs);
  triggerDelayCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&interValCs);
  interValCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&interValSwitchCs);
  interValSwitchCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&bShutterCs);
  bShutterCs.addDescriptor(new BLE2902());
  camsbleService->addCharacteristic(&selfieDelayCs);
  selfieDelayCs.addDescriptor(new BLE2902());

  
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setAppearance(HID_KEYBOARD);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  //---------------------------  HID -_,-
  hid = new BLEHIDDevice(pServer);
  input = hid->inputReport(1); // <-- input REPORTID from report map
  output = hid->outputReport(1); // <-- output REPORTID from report map
  //inputMediaKeys = hid->inputReport(MEDIA_KEYS_ID);

  output->setCallbacks(new MyOutputCallbacks());

  std::string name = "ElectronicCats";
  hid->manufacturer()->setValue(name);

  hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  hid->hidInfo(0x00,0x02);
  hid->reportMap((uint8_t*)hidReportDescriptor, sizeof(hidReportDescriptor));
  hid->startServices();
  hid->setBatteryLevel(7);

  // Start the service
  camsbleService->start();

  // ----------------------- BLE init & notify -_,-

  modeCs.setCallbacks(new modeCallbacks());
  modeCs.setValue(String(mode).c_str());
  modeCs.notify();

  triggerTimesCs.setCallbacks(new triggerTimesCallbacks());
  triggerTimesCs.setValue(String(triggerTimes).c_str());
  triggerTimesCs.notify();

  triggerDelayCs.setCallbacks(new triggerDelayCallbacks());
  triggerDelayCs.setValue(String(triggerDelay).c_str());
  triggerDelayCs.notify();

  interValCs.setCallbacks(new interValCallbacks());
  interValCs.setValue(String(interVal).c_str());
  interValCs.notify();

  interValSwitchCs.setCallbacks(new interValSwitchCsCallbacks());
  interValSwitchCs.setValue(String(interValSwitch).c_str());
  interValSwitchCs.notify();

  bShutterCs.setCallbacks(new bShutterCallbacks());
  bShutterCs.setValue(String(bShutter).c_str());
  bShutterCs.notify();

  selfieDelayCs.setCallbacks(new selfieDelayCallbacks());
  selfieDelayCs.setValue(String(selfieDelay).c_str());
  selfieDelayCs.notify();
//------------------------
}


