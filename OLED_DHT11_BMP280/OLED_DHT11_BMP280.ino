#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

Adafruit_BMP280 bmp; // I2C

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin(); // Start HDT11 sensor

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }

  // Clear the display
  display.clearDisplay();
  display.display();

  // Initialize BMP280 sensor
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() * 0.007500615613026;
  float altitude = bmp.readAltitude(1010);

  int hd = dht.readHumidity();
  int td = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\n");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa\n");
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.print(" hPa\n");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp and Pressure");

  display.setCursor(0, 10);
  display.print("Temp:");
  display.setCursor(45, 10);
  display.print(temperature);

  display.setCursor(0, 20);
  display.print("Pressure:");
  display.setCursor(60, 20);
  display.print(pressure);

  display.setCursor(0, 30);
  display.print("Alt:");
  display.setCursor(40, 30);
  display.print(altitude);

  display.setCursor(0, 40);
  display.print("Temp:");
  display.setCursor(30, 40);
  display.print(td);

  display.setCursor(0, 50);
  display.print("Hum:");
  display.setCursor(30, 50);
  display.print(hd);
  display.display();

  delay(2000);
}
