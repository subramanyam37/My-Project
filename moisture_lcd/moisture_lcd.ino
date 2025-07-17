#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int moist = A0;
int led = 2 ;

int moistValue = 0;

void setup(){
  pinMode(moist,INPUT);
  pinMode(led,OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop(){
moistValue = analogRead(moist);

lcd.setCursor(1,0);
lcd.print("Moisture Value:");

lcd.setCursor(1,1);
lcd.print(moistValue);
lcd.print("      ");

Serial.print(moistValue);
Serial.println();
delay(500);

if (moistValue>1000){
   digitalWrite(led,HIGH);
   delay(300);
}
else{
  digitalWrite(led,LOW);
  delay(300);
}
}