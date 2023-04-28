// void flame(void) {
//   int flameVal = analogRead(FLAMEA);
//   Blynk.virtualWrite(V2, flameVal);

//   int flameDig = analogRead(FLAME);
//   Blynk.virtualWrite(V3, flameDig);

//   if (flameVal < 40) {
//     Serial.println("FIRE!" + String(flameVal));
//     Blynk.logEvent("FLAME", "FIRE! FIRE! FIRE!");
//   } else { Serial.println("no FIRE!"); }

//   delay(10);
// }