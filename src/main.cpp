#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLECast.h>
#include <string.h>

#ifndef BEACON

    BLEScan *pBLEScan;

    const int scanTimeSeconds = 1;


    class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
    {
        void onResult(BLEAdvertisedDevice advertisedDevice)
        {
<<<<<<< HEAD
            if (advertisedDevice.getName().compare("hknogroi39=")!=0)
=======
            if (advertisedDevice.getName().compare("Y2hvY29jaGVzbmV5") == 0)
>>>>>>> 2f817401dba18aad8460ecfd4c186b636b7f67b7
            {
                Serial.print(advertisedDevice.getName().c_str());
                Serial.printf(": %d \n", advertisedDevice.getRSSI());
                Serial.printf(": %s \n", advertisedDevice.getManufacturerData().c_str());
            }
        }
    };

    void setup()
    {
        Serial.begin(115200);
        Serial.println("Scanning...");

        BLEDevice::init("Radiation SCAN");
        pBLEScan = BLEDevice::getScan(); // create new scan
        pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
        pBLEScan->setActiveScan(false); // active scan (true) uses more power, but get results faster
        pBLEScan->setInterval(100);
        pBLEScan->setWindow(99); // less or equal setInterval value
    }

    void loop()
    {
        BLEScanResults foundDevices = pBLEScan->start(scanTimeSeconds, false);
        pBLEScan->clearResults();
    }
#else
    // define BTLE name
    // CAREFUL: each character eats into your usable adv packet length
<<<<<<< HEAD
    BLECast bleCast("hknogroi39=");
=======
    BLECast bleCast("ESP32-WristbandV4.20");
>>>>>>> 2f817401dba18aad8460ecfd4c186b636b7f67b7
    
    uint8_t cnt = 0;
    char data[5];

    void setup()
    {
        Serial.begin(115200);
        Serial.println("Starting BLE Beacon");

        bleCast.begin();
    }

    void loop()
    {
        // note -- if you have too much data, it will not be added to the adv payload

        if (cnt == 20){
            // reset
            cnt = 0;
        }

        if (cnt == 0){
            // regenerate "random" data
            int red = random(20, 50);
            int orange = random(50, 70);
            sprintf(data, "%02d&%02d", red, orange);
        }
        cnt += 1;
        
        std::string s = bleCast.setManufacturerData(data, sizeof(data));
        Serial.println(s.c_str());
        delay(1000);
    }
#endif