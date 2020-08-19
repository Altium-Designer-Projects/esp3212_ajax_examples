#include <Wire.h>
#include "Adafruit_HTU21DF.h"

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

float temp = htu.readTemperature();
float rel_hum = htu.readHumidity();
  
void setup() {
  Serial.begin(115200);
  Serial.println("HTU21D-F test");

  if(!htu.begin()) {
    Serial.println("Couldn't find sensor!");
  }
  
}

void loop() {

  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" \%");
  delay(500);
    
}
