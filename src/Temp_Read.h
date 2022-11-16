#include "DHT.h"
#include <Wire.h>
#define DHTPIN 13  //-------input sensor to pin 13 esp32
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

float h = 0;
float t = 0;
float f,hif,hic ;
DHT dht(DHTPIN, DHTTYPE); 

void TM_Read()
{
delay(1000);
   h = dht.readHumidity();
   t = dht.readTemperature();
   f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F(" C "));
  Serial.print(f);
  Serial.print(F(" F  Heat index: "));
  Serial.print(hic);
  Serial.print(F(" C "));
  Serial.print(hif);
  Serial.println(F(" F"));
  
}
