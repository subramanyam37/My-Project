#include<Wire.h>
#include<LiquidCrystal_I2C.h>

const int button = 2;
const int led = 10;
const int led2 = 13;

const int trig = 7;
const int echo = 8;

byte lastButton=1;
byte ledState = 0 ;

int num = 0;

LiquidCrystal_I2C lcd(0x27 , 16 , 2);

void setup() {
Serial.begin(9600);

pinMode(led,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(trig,OUTPUT);

pinMode(button,INPUT);
pinMode(echo,INPUT);

lcd.init();
lcd.backlight();
}

void loop() {

byte buttonState = digitalRead(button);

if(buttonState != lastButton && buttonState==LOW){
ledState = !ledState;
digitalWrite(led,ledState);
delay(50);
}

lastButton = buttonState;

long cm,duration;

if(ledState==HIGH){
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

duration = pulseIn(echo,HIGH);
cm = ms_to_cm(duration);

lcd.setCursor(1,0);
lcd.print("COIN NUMBER :");

if(cm<6){
            num++;
            digitalWrite(led2,HIGH);
            Serial.print("Coin number ");
            Serial.println(num);

            lcdDisplay(num);
          }
          else{
            digitalWrite(led2,LOW);
          }
          delay(400);
     }
     else{
          digitalWrite(led2,LOW);
          lcdDisplay(0);
          num=0;
     }
}

long ms_to_cm(long ms){
  return ms / 29 / 2 ;
}

void lcdDisplay(int n){

lcd.setCursor(1,1);
lcd.print("  ");
lcd.setCursor(1,1);
lcd.print(n);
}

