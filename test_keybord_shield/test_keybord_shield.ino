#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  analogWrite(10, 30);
}

byte key() {
  // 1 - 719, 2 - 477, 3 - 131, 4 - 305, 5 - 0
  int val = analogRead(0);
    if (val < 50) return 5;
    else if (val < 150) return 3;
    else if (val < 350) return 4;
    else if (val < 500) return 2;
    else if (val < 800) return 1;
    else if (val <= 1023) return 0;
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("analogRead:");
  lcd.print(analogRead(0));
  lcd.setCursor(0, 1);
    switch (key()) {
      case 1:
        lcd.print("Select");
        break;
      case 2:
        lcd.print("Left");
        break;
      case 3:
        lcd.print("UP");
        break;
      case 4:
        lcd.print("Down");
        break;
      case 5:
        lcd.print("Rigth");
        break;
    }
  
  delay(250);

}
