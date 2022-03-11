bool isConnected = false;

//---------------------------------   BLE -_,-
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#define SERVICE_UUID        "fc1d6c97-b334-45bd-ad8e-964cf37fba58"

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

#define SOFTWARE_VERSION_MAJOR 0
#define SOFTWARE_VERSION_MINOR 1
#define SOFTWARE_VERSION_PATCH 1
#define HARDWARE_VERSION_MAJOR 1
#define HARDWARE_VERSION_MINOR 2
#define SERVICE_UUID_ESPOTA        "d804b643-6ce7-4e81-9f8a-ce0f699085eb"
#define CHARACTERISTIC_UUID_ID           "d804b644-6ce7-4e81-9f8a-ce0f699085eb"

#define SERVICE_UUID_OTA                    "c8659210-af91-4ad3-a995-a58d6fd26145" // UART service UUID
#define CHARACTERISTIC_UUID_FW              "c8659211-af91-4ad3-a995-a58d6fd26145"
#define CHARACTERISTIC_UUID_HW_VERSION      "c8659212-af91-4ad3-a995-a58d6fd26145"


//---------------------------------
BLECharacteristic modeCs("d6b1d851-f38b-4a40-ab1a-323dca8b59c0", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic triggerTimesCs("18a09d26-50df-4539-b0c5-5cc8190dfac3", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic triggerDelayCs("2286b0e0-0fd4-470d-b07d-c2a04cac41c3", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic interValCs("8d4f535a-ec08-4957-bde7-fe0d02fa235f", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic interValSwitchCs("f3ab231f-d13c-49bb-a2dc-94bfbb1237cf", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic bShutterCs("203e69eb-471b-40dc-8d75-7824e112165b", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
BLECharacteristic selfieDelayCs("62f876a1-fbe9-4524-b548-6c3d1df6c4ad", NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);



//--------------------------------- HID -_,-

// Report IDs:
#define KEYBOARD_ID 0x01
BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;


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

uint8_t buttons = 0;

void bleTriggerShutter(){
  Serial.println("BLE Trigger Shutter");
  
    const char* hello = "\n";
    while(*hello){
      KEYMAP map = keymap[(uint8_t)*hello];
      uint8_t msg[] = {map.modifier || buttons, 0x0, map.usage, 0x0,0x0,0x0,0x0,0x0};
      input->setValue(msg,sizeof(msg));
      input->notify();
      hello++;
      uint8_t msg1[] = {0x0, 0x0, 0x0, 0x0,0x0,0x0,0x0,0x0};

      input->setValue(msg1,sizeof(msg1));
      input->notify();
    }  

}

//---------------------------------- Init BLE -_,-
void initBLE(){
  
  Serial.println("Starting BLE work!");
  BLEDevice::init("bbCamsble");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *camsbleService = pServer->createService(BLEUUID(SERVICE_UUID),30,0);
  BLEService *pESPOTAService = pServer->createService(BLEUUID(SERVICE_UUID_ESPOTA),30,0);
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID_OTA),30,0);

  // Create a BLE Characteristic



  camsbleService->addCharacteristic(&modeCs);
  camsbleService->addCharacteristic(&triggerTimesCs);
  camsbleService->addCharacteristic(&triggerDelayCs);
  camsbleService->addCharacteristic(&interValCs);
  camsbleService->addCharacteristic(&interValSwitchCs);
  camsbleService->addCharacteristic(&bShutterCs);
  camsbleService->addCharacteristic(&selfieDelayCs);

// Create a BLE Characteristic
  BLECharacteristic *pESPOTAIdCharacteristic = pESPOTAService->createCharacteristic(
                                       CHARACTERISTIC_UUID_ID,
                                       NIMBLE_PROPERTY::READ
                                     );

  BLECharacteristic *pVersionCharacteristic = pService->createCharacteristic(
                             CHARACTERISTIC_UUID_HW_VERSION,
                             NIMBLE_PROPERTY::READ
                           );

  BLECharacteristic *pOtaCharacteristic = pService->createCharacteristic(
                         CHARACTERISTIC_UUID_FW,
                         NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::WRITE
                       );
  
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setAppearance(HID_KEYBOARD);
  pAdvertising->setScanResponse(true);
  
  //BLEDevice::startAdvertising();
  
  //---------------------------  HID -_,-
  hid = new BLEHIDDevice(pServer);
  input = hid->inputReport(1); // <-- input REPORTID from report map
  output = hid->outputReport(1); // <-- output REPORTID from report map

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
  pESPOTAService->start();
  pService->start();

  // ----------------------- BLE init & notify -_,-
  
  modeCs.setCallbacks(new modeCallbacks());
  modeCs.setValue(std::string(String(mode).c_str()));
  modeCs.notify();

  triggerTimesCs.setCallbacks(new triggerTimesCallbacks());
  triggerTimesCs.setValue(std::string(String(triggerTimes).c_str()));
  triggerTimesCs.notify();

  triggerDelayCs.setCallbacks(new triggerDelayCallbacks());
  triggerDelayCs.setValue(std::string(String(triggerDelay).c_str()));
  triggerDelayCs.notify();

  interValCs.setCallbacks(new interValCallbacks());
  interValCs.setValue(std::string(String(interVal).c_str()));
  interValCs.notify();

  interValSwitchCs.setCallbacks(new interValSwitchCsCallbacks());
  interValSwitchCs.setValue(std::string(String(interValSwitch).c_str()));
  interValSwitchCs.notify();

  bShutterCs.setCallbacks(new bShutterCallbacks());
  bShutterCs.setValue(std::string(String(bShutter).c_str()));
  bShutterCs.notify();

  selfieDelayCs.setCallbacks(new selfieDelayCallbacks());
  selfieDelayCs.setValue(std::string(String(selfieDelay).c_str()));
  selfieDelayCs.notify();
  
  pOtaCharacteristic->setCallbacks(new otaCallback());

  uint8_t hardwareVersion[5] = {HARDWARE_VERSION_MAJOR, HARDWARE_VERSION_MINOR, SOFTWARE_VERSION_MAJOR, SOFTWARE_VERSION_MINOR, SOFTWARE_VERSION_PATCH};
  pVersionCharacteristic->setValue((uint8_t*)hardwareVersion, 5);

  pAdvertising->start();
  // Start the service(s)

  Serial.println("Created Server");
  
//------------------------
}
