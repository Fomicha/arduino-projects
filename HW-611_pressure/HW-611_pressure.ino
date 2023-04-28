#include <SparkFunBME280.h>

int hw611_pin = A1;

void setup() {
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the sensor value
  int sensor_value = analogRead(hw611_pin);

  // Convert the sensor value to voltage
  float voltage = sensor_value * (5.0 / 1023.0);

  // Convert the voltage to pressure in kilopascals (kPa)
  float pressure = (voltage - 0.5) * 20;

  // Print the pressure to the serial monitor
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" kPa");

  // Wait for 1 second before taking the next reading
  delay(1000);
}