#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup(){

  Serial.begin(9600);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  int h=DHT.humidity;
  Serial.print(h);
Serial.print(",");
Serial.flush();
  delay(1000);
}
