#include <Arduino.h>
#include "stemhal.h"
#include "DHT.h"



#define DHTPIN D4  
#define DHTTYPE DHT11 
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
    Serial.println(dht11.tem );
    dht11.hum = dht.readHumidity();
    dht11.temIndex= dht.computeHeatIndex(dht11.tem, dht11.hum, false);

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
    if(externalTemSensor(dht11))
    {
        Serial.println(dht11.hum);
        Serial.println(dht11.tem);
        Serial.println(dht11.temIndex);
    }

    delay(3000);

}
