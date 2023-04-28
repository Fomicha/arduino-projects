// Define the analog pin used to read the sensor
int mq135_pin = A0;

void setup() {
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the sensor value
  int sensor_value = analogRead(mq135_pin);

  // Convert the sensor value to voltage
  float voltage = sensor_value * (5.0 / 1023.0);

  // Convert the voltage to resistance
  float resistance = (5.0 * 10.0) / voltage - 10.0;

  // Calculate the air quality index (AQI)
  float aqi = 100.0 * pow((resistance / 10000.0), -1.2);

  // Print the sensor value, voltage, resistance, and AQI to the serial monitor
  Serial.print("Sensor value: ");
  Serial.print(sensor_value);
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  Serial.print(", Resistance: ");
  Serial.print(resistance);
  Serial.print(", AQI: ");
  Serial.println(aqi);

  // Wait for 1 second before taking the next reading
  delay(1000);
}
