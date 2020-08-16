// Cretaed by Niwantha Meepage for STEM Development Board.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor


#include <Arduino.h>
#include "stemhal.h"
#include "DHT.h"



#define DHTPIN D4  // STEM DATA PIN D4

#define DHTTYPE DHT11  // SENSOR TYPE DHT11 (VCC = 3.3 V or 5V)

DHT dht(DHTPIN, DHTTYPE);

struct temSensor
{
    float tem;
    float hum;
    float temIndex;
};

int externalTemSensor(struct temSensor dht11)
{
    dht11.tem = dht.readTemperature();
    Serial.print("Tem : \t");
    Serial.println(dht11.tem );
    dht11.hum = dht.readHumidity();
    Serial.print("Hum : \t");
    Serial.println(dht11.hum );
    dht11.temIndex= dht.computeHeatIndex(dht11.tem, dht11.hum, false);
    Serial.print("Heat Index : \t");
    Serial.println(dht11.temIndex );
    if (isnan(dht11.hum) || isnan(dht11.tem)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return false;
    }
    return true;
}


void setup() {
    dht.begin();
    Serial.begin(9600);

}

void loop() {
    struct temSensor dht11 ;
    externalTemSensor(dht11);
    delay(3000);

}
