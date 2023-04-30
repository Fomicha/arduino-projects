#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <MQ135.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BMP280 bmp; // I2C

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN A2
MQ135 mq135_sensor(MQ135_PIN);

void setup() {
  Serial.begin(9600);

  dht.begin(); // Start HDT11 sensor

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  // /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                   Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                   Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                   Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                   Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
          
  display.clearDisplay();
  display.display();
}

void loop() {
  float temperature = bmp.readTemperature(); //Read temperature in C
  float pressure = bmp.readPressure()*0.007500615613026; // 1 pascal is equal to 0.0075006156130264 mmHg.
  float altitude = bmp.readAltitude(1010);

  int hd = dht.readHumidity();
  int td = dht.readTemperature();

  float PPM = mq135_sensor.getPPM();

  // if (isnan(hd) || isnan(td)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   while (1);
  // }

  // if (isnan(temperature) || isnan(pressure) || isnan(altitude)) {
  //   Serial.println("Failed to read from BMP sensor!");
  //   while (1);
  // }

  Serial.println("T: " + String(td));
  Serial.println("H: " + String(hd));

  Serial.println("PPM: " + String(PPM));

  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure);
  Serial.println(" mmHg");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(altitude);
  Serial.println(" m");

  Serial.println();

  // *************************** //

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // BMP-280 Data
  // Temperature
  display.setCursor(0,0);
  display.print("Tmp: " + String(temperature,1) + "C");

  // Pressure
  display.setCursor(0,10);
  display.print("Pressure:");
  
  display.setCursor(0,20);
  display.print(String(pressure,1) + "mmHg");

  // Altitude
  display.setCursor(0,30);
  display.print("Alt: " + String(altitude,1) + "m");

  // DHT11 Data
  // Temperature
  display.setCursor(65,0);
  display.print("Tmp: " + String(td) + "C");

  // Humidity
  display.setCursor(65,10);
  display.print("Hmdt: " + String(hd) + "%");

  // MQ-135 Data
  display.setCursor(65,20);
  display.print("PPM: " + String(PPM));
  
  display.display();

  delay(2000);
}
