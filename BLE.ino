bool isConnected = false;

//---------------------------------   BLE -_,-
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#define SERVICE_UUID        "45c424d1-adee-4a3d-b508-50d3acee84ad"

#define BLEDevice                  NimBLEDevice
#define BLEServerCallbacks         NimBLEServerCallbacks
#define BLECharacteristicCallbacks NimBLECharacteristicCallbacks
#define BLEHIDDevice               NimBLEHIDDevice
#define BLECharacteristic          NimBLECharacteristic
#define BLEAdvertising             NimBLEAdvertising
#define BLEServer                  NimBLEServer

#include "esp_ota_ops.h"
#define FULL_PACKET 512
#define CHARPOS_UPDATE_FLAG 5
esp_ota_handle_t otaHandler = 0;
bool updateFlag = false;
bool readyFlag = false;

//---------------------------------
BLECharacteristic modeCs("d6b1d851-f38b-4a40-ab1a-323dca8b59c0", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic triggerTimesCs("18a09d26-50df-4539-b0c5-5cc8190dfac3", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic triggerDelayCs("2286b0e0-0fd4-470d-b07d-c2a04cac41c3", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic interValCs("8d4f535a-ec08-4957-bde7-fe0d02fa235f", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic interValSwitchCs("f3ab231f-d13c-49bb-a2dc-94bfbb1237cf", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic bShutterCs("203e69eb-471b-40dc-8d75-7824e112165b", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic selfieDelayCs("62f876a1-fbe9-4524-b548-6c3d1df6c4ad", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);

BLECharacteristic pOtaCharacteristic("a63d3ca7-2949-4173-802b-a0e6ee471ae0", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::WRITE);
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


class otaCallback: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string rxData = pCharacteristic->getValue();
    if (!updateFlag) { //If it's the first packet of OTA since bootup, begin OTA
      Serial.println("BeginOTA");
      esp_ota_begin(esp_ota_get_next_update_partition(NULL), OTA_SIZE_UNKNOWN, &otaHandler);
      updateFlag = true;
    }
      if (rxData.length() > 0)
      {
        esp_ota_write(otaHandler, rxData.c_str(), rxData.length());
        if (rxData.length() != FULL_PACKET)
        {
          esp_ota_end(otaHandler);
          Serial.println("EndOTA");
          if (ESP_OK == esp_ota_set_boot_partition(esp_ota_get_next_update_partition(NULL))) {
            delay(2000);
            esp_restart();
          }
          else {
            Serial.println("Upload Error");
          }
        }
      }
    
  
    uint8_t txData[5] = {1, 2, 3, 4, 5};
    //delay(1000);
    pCharacteristic->setValue((uint8_t*)txData, 5);
    pCharacteristic->notify();
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
  //modeCs.createDescriptor();
  camsbleService->addCharacteristic(&triggerTimesCs);
  //triggerTimesCs.createDescriptor();
  camsbleService->addCharacteristic(&triggerDelayCs);
  //triggerDelayCs.createDescriptor();
  camsbleService->addCharacteristic(&interValCs);
  //interValCs.createDescriptor();
  camsbleService->addCharacteristic(&interValSwitchCs);
  //interValSwitchCs.createDescriptor();
  camsbleService->addCharacteristic(&bShutterCs);
  //bShutterCs.createDescriptor();
  camsbleService->addCharacteristic(&selfieDelayCs);
  //selfieDelayCs.createDescriptor();

  
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

  pOtaCharacteristic.setCallbacks(new otaCallback());
//------------------------
}
