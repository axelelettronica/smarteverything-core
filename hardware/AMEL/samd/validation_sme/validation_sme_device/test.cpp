/*
    SmeGPS Library - Localization Information

    This example shows how to retrieve the GPS localization information:
    Latitude, Longitude,  Altitude

    It shows also the number of the satellites  are visible by the GPS receiver
    This information is useful to well understand the accuracy of the localization information

    created 27 May 2015
    by Seve (seve@axelelettronica.it)

    This example is in the public domain
    https://github.com/ameltech

    SE868  more information available here:
    http://www.telit.com/products/product-service-selector/product-service-selector/show/product/jupiter-se868-as/
 */

#include <Wire.h>

#include <sl868a.h>
#include <Arduino.h>

int led_status = HIGH;

typedef void (*ledPtr) (uint32_t) ;
ledPtr led;

// the setup function runs once when you press reset or power the board
void setup() {
    SerialUSB.begin(115200);
    smeGps.begin();
    led = ledYellowTwoLight;
    pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    static unsigned loop_cnt = 0;
    unsigned int altitude = 0;
    unsigned char lockedSatellites = 0;
    double latitude = 0;
    double longitude = 0;

    delay(5);

    if (smeGps.ready()) {
        ledYellowTwoLight(LOW);
        led = ledYellowThreeLight;
        
        led(HIGH);

        altitude   = smeGps.getAltitude();
        latitude   = smeGps.getLatitude();
        longitude  = smeGps.getLongitude();
        lockedSatellites = smeGps.getLockedSatellites();

        if ((loop_cnt % 200) == 0) {
            SerialUSB.println(" ");
            SerialUSB.print("Latitude    =  ");
            SerialUSB.println(latitude, 6);
            SerialUSB.print("Longitude   =  ");
            SerialUSB.println(longitude, 6);
            SerialUSB.print("Altitude    =  ");
            SerialUSB.println(altitude, DEC);
            SerialUSB.print("Satellites  =  ");
            SerialUSB.println(lockedSatellites, DEC);
            
            if (led_status == LOW) {
                led_status = HIGH;
                } else {
                led_status = LOW;
            }
            
        }
    } else {
        if ((loop_cnt % 200) == 0) {
            SerialUSB.println("Locking GPS position...");
            if (isOnBattery()){
                SerialUSB.println("is On Battery");
                digitalWrite(13, HIGH);
            } else {
                SerialUSB.println("is On Power");
                digitalWrite(13, LOW);
            }            
            if (led_status == LOW) {
                led_status = HIGH;
            } else {
                led_status = LOW;
            }
        }
    }

    loop_cnt++;
    led(led_status);
}
