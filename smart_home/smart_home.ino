#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <MQ135.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "///////"
#define ESP8266_BAUD 9600

// RX, TX jumpers
#define RXWIFISHIELD 2
#define TXWIFISHIELD 3

#define LEDG 9
#define LEDR 10
#define LEDB 11

#define DHTPIN A5
#define DHTTYPE DHT11

#define MQ135_PIN A2

char auth[] = "///////";
char ssid[] = "mFi_07DACB"; // Wifi name
char pass[] = "36458951"; // Wifi pass

// char ssid[] = "TP-LINK_AP_5170"; // Wifi name
// char pass[] = ""; // Wifi pass

BlynkTimer timer;
SoftwareSerial EspSerial(RXWIFISHIELD, TXWIFISHIELD); // RX, TX jumpers
ESP8266 wifi(&EspSerial);
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp; // I2C
MQ135 mq135_sensor(MQ135_PIN);

void runSensors() {
  // lightSensor(); // run Light
  h11Sensor(); // run DTH11
  // flame(); // run Flame
}

BLYNK_WRITE(V0) {
  if (param.asInt() == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
  } else {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
  }
}

void setup(void) {
  pinMode(LIGHT, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(FLAME, INPUT);
  pinMode(FLAMEA, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Debug console
  Serial.begin(9600);
  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  // Start Blynk
  Blynk.begin(auth, wifi, ssid, pass);
  delay(10);

  // Start DHT Sensor
  dht.begin();
  delay(10);

  // Setup a function to be called every 5 min
  timer.setInterval(300000L, runSensors);
}

void loop(void) {
  Blynk.run(); // Initiates Blynk App
  delay(10);

  timer.run(); // Initiates BlynkTimer
  delay(10);
}
