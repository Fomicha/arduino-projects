#include <LiquidCrystal.h> 
#include <SimpleDHT.h> 

int pinDHT11 = 11; 
SimpleDHT11 dht11; 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() { // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(4,0); 
  lcd.print("Bob");
  lcd.setCursor(1,1); 
  lcd.print("PROJECT DHT-11");
  delay(3000);
  lcd.setCursor(0,1); 
  lcd.clear();
}

void loop() { 
  byte temperature = 0;
  byte humidity = 0; 
  int err = SimpleDHTErrSuccess; 

  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess){ 
    lcd.setCursor(0,0);
    lcd.print("Read DHT11 failed, err:"); 
    lcd.setCursor(0,1);
    lcd.println(err);
    delay(1000);
    return;
  } // LCD output

  lcd.setCursor(0,0); // Set the first row (location at which subsequent text written to the LCD will be displayed) 
  lcd.print("T:"); // Print "T:" on the LCD
  lcd.print((int)temperature); // Print string temperature
  lcd.print((char)223); // Prints "o" on the LCD
  lcd.print("C"); // Prints "C" on the LCD

  lcd.setCursor(0,1); // Set the second row (location at which subsequent text written to the LCD will be displayed) 
  lcd.print("H:"); // Print "H:" on the LCD
  lcd.print((int)humidity); // Print string humidity 
  lcd.print("%");
  delay(1500); 
}
