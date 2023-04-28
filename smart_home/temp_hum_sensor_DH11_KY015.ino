void h11Sensor() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("T: " + String(t));
  Serial.println("H: " + String(h));

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}