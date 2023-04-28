#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

int MQ135_pin = A0;
float RL_VALUE = 10.0;
float RO_CLEAN_AIR_FACTOR = 41;
float CALIBRATION_SAMPLE_TIMES = 50;
float CALIBRATION_SAMPLE_INTERVAL = 5000;
float READ_SAMPLE_INTERVAL = 1000;
float READ_SAMPLE_TIMES = 5;

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }

  // Clear the display
  display.clearDisplay();
  display.display();

  // Calibration
  Serial.print("Calibrating...\n");
  float Ro = MQCalibration();
  Serial.print("Calibration is done...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print(" kohm");

  delay(2000);
}

void loop() {
  float rs = MQRead();
  float ratio = rs / RO_CLEAN_AIR_FACTOR;
  float ppm = (0.64 * pow(ratio, -2.7)) * 1000;

  Serial.print("PPM: ");
  Serial.println(ppm);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Gas sensor: MQ-135");
  display.setCursor(0, 10);
  display.print("PPM:");
  display.setCursor(45, 10);
  display.print(ppm);
  display.display();

  delay(READ_SAMPLE_INTERVAL);
}

float MQRead() {
  int i;
  float rs = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += analogRead(MQ135_pin);
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs / READ_SAMPLE_TIMES;
  rs = (5.0 * rs) / 1024.0;

  return rs;
}

float MQCalibration() {
  int i;
  float rs = 0;

  for (i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) {
    rs += analogRead(MQ135_pin);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }

  rs = rs / CALIBRATION_SAMPLE_TIMES;
  rs = (5.0 * rs) / 1024.0;

  float ratio = rs / RO_CLEAN_AIR_FACTOR;

  float sensor_volt = rs;
  float sensor_r = RL_VALUE * (5.0 - sensor_volt) / sensor_volt;
  float sensor_value = sensor_volt / sensor_r;

  float R0 = sensor_r / ratio;

  return R0;
}
