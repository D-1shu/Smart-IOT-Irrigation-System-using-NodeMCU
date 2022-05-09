#include <Blynk.h>
#include "BlynkEdgent.h"

#define BLYNK_TEMPLATE_ID "TMPL9Ex_wBpX"
#define BLYNK_DEVICE_NAME "IOT"
#include "DHT.h"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define DHTPIN 2
#define DHTTYPE DHT11  
#define BLYNK_PRINT Serial

#define APP_DEBUG
int output_value ;

DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V0)
{
  int pinvalue=param.asInt();
  digitalWrite(14,pinvalue);
}


BLYNK_READ(V3)
{
  Blynk.virtualWrite(V1, "Hello!!");
}

//Soil moisture sensor
int sensorPin =A0;
int sensorValue;
int limit=500;
int superlimit=900;
int state=0;

void setup()
{
  pinMode(14,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  delay(1000);


  BlynkEdgent.begin();
}

void loop() {
  sensorValue = analogRead(sensorPin);
  output_value = map(sensorValue,550,0,0,100);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(sensorValue);
  Serial.println(h);
  Serial.print(t);
  Blynk.virtualWrite(V1,output_value);
  Blynk.virtualWrite(V4,h);
  Blynk.virtualWrite(V2,t);
  BlynkEdgent.run();

 if (sensorValue>limit) 
 {
 digitalWrite(13, HIGH);
 Blynk.virtualWrite(V3, "Water the Plants!!");
 }
 else if(sensorValue<limit) {
 digitalWrite(13, LOW); 
 Blynk.virtualWrite(V3, "Plants watered ");

 }
 
 delay(5000); 
  
}
