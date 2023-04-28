// void lightSensor() {
//   int light_adc = analogRead(LIGHT);

//   Serial.println("Light ADC: " + String(light_adc));

//   if (light_adc > 900) {
//     digitalWrite(LED, HIGH);
//   } else { digitalWrite(LED, LOW); }

//   Blynk.virtualWrite(V4, light_adc);
// }