#include "MQ135.h"
void setup (){
Serial.begin (9600);
}
void loop() {
MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
float ppm = gasSensor.getPPM();
Serial.println (ppm);
delay(1000);
}