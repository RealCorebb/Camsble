// MODE  0 输入触发模式  1 Schedule模式    2 B门模式
/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic modeCs("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLEDescriptor modeDs(BLEUUID((uint16_t)0x2903));

int testvalue = 0;


class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      Serial.print("Changed value = ");
      //Serial.println(value.c_str());
      testvalue = String(value.c_str()).toInt();
      Serial.println(testvalue);
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Camsble");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *camsbleService = pServer->createService(SERVICE_UUID);

  camsbleService->addCharacteristic(&modeCs);
  modeDs.setValue("Camsble Mode");
  modeCs.addDescriptor(new BLE2902());

  // Start the service
  camsbleService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);

  modeCs.setCallbacks(new MyCallbacks());

  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  //char* sb = "sb";
  testvalue++;
  //String(millis()).toCharArray(sb,4);
  modeCs.setValue(String(testvalue).c_str());
  modeCs.notify();
}
