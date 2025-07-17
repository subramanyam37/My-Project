#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop()
{
  for(int i=0;i<10;i++){
  lcd.setCursor(1, 0);
  lcd.print("COUNT NUMBER :");

  lcd.setCursor(1,1);
  lcd.print(i);
  delay(3000);
  lcd.clear();
  }
}
