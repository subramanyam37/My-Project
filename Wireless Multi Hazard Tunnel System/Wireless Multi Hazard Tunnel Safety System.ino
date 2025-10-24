#include"keypad.h"

int vib_pin = 2;
volatile bool vibrationDetected = false;
int VibrationDetection;
int gasSensorPin = A0;
int gasValue = 0;
int V_COUNT = 0;
int C_COUNT = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
bool flag = true;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
SoftwareSerial mySoftwareSerial(12, 13); // RX, TX df player
DFRobotDFPlayerMini myDFPlayer;

char pressed_key;
bool firstKeyPressed = false;
bool vibrate = false;
void keypadfunction();
void iot(String s);
String lat1 = "13.1877832";
String lon1 = "80.1064227";
String lat2 = "13.1877728";
String lon2 = "80.104057";

void detectVibration() {
  vibrationDetected = true;
}

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(vib_pin, INPUT);
  lcd.init();
  lcd.backlight();
  keypad_init();
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer Mini not detected!");
    //    while (true);
  }
  Serial.println("DFPlayer Mini detected.");
  lcd.setCursor(0, 0);
  lcd.print("TUNNEL_WORKERS");
  lcd.setCursor(0, 1);
  lcd.print("SAFETY");
  delay(2000);
  lcd.clear();
}
void loop() {
  gasValue = analogRead(gasSensorPin);
  //  Serial.print("Gas Sensor Value: ");
  //  Serial.println(gasValue);
  int VibrationDetection = digitalRead(vib_pin);
  //  Serial.print("VibrationDetection: ");
  //  Serial.println(VibrationDetection);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T_GAS:" + String(gasValue));
  lcd.setCursor(0, 1);
  lcd.print("VIBRATION:");
  lcd.setCursor(11, 1);
  lcd.print(VibrationDetection);
  soil("@" + String(gasValue) + "#" + "   " + "$" + String(VibrationDetection) + "#");
  if (VibrationDetection == LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VIBRATION_OCCURED");
    soil("*VIBRATION OCCURED..#");
    soil("*Lat:" + String(lat1) + " Lon:" + String(lon2) + "#");
  }
  keypadfun();
  delay(1000);
}

void keypadfun()
{
  pressed_key = key();
  //  Serial.println("key:" + String(pressed_key));
  if (flag == true)
  {
    soil("*A FOR NEEDS && B FOR EMPLOYEE COUNT...#");
    flag = false;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1ST PRESS A OR B");
  if (pressed_key == 'A')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CHOOSE YOUR NEEDS");
    soil("*CHOOSE YOUR NEEDS...#");
    while (pressed_key != '*')
    {
      pressed_key = key();
      //      Serial.println("pressed_key:" + String(pressed_key));
      if (pressed_key == '1')
      {
        pressed_key = 'x';
        key() == Reset;
        key_reset();
        //        Serial.println("WE WANT WATER..");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WE WANT WATER");
        soil("*WE WANT WATER..#");
        myDFPlayer.volume(30);
        myDFPlayer.play(1);
        delay(100);
      }
      if (pressed_key == '2')
      {
        pressed_key = 'x';
        key() == Reset;
        key_reset();
        //        Serial.println("WE WANT FOOD...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WE WANT FOOD");
        soil("*WE WANT FOOD...#");
        myDFPlayer.volume(30);
        myDFPlayer.play(2);
        delay(100);
      }
       if (pressed_key == '3')
      {
        pressed_key = 'x';
        key() == Reset;
        key_reset();
        //        Serial.println("WE WANT FOOD...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WE WANT  SOME MEDICINE");
        soil("*WE WANT  SOME MEDICINE...#");
        myDFPlayer.volume(30);
        myDFPlayer.play(2);
        delay(100);
      }
       if (pressed_key == '4')
      {
        pressed_key = 'x';
        key() == Reset;
        key_reset();
        //        Serial.println("WE WANT FOOD...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PLEASE HELP FOR US");
        soil("*PLEASE HELP FOR US...#");
        myDFPlayer.volume(30);
        myDFPlayer.play(2);
        delay(100);
      }
       if (pressed_key == '5')
      {
        pressed_key = 'x';
        key() == Reset;
        key_reset();
        //        Serial.println("WE WANT FOOD...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WE ARE SAFE");
        soil("*WE ARE SAFE..#");
        myDFPlayer.volume(30);
        myDFPlayer.play(2);
        delay(100);
      }
      if (pressed_key == '*')
      {
        pressed_key = 'x';
        key() == Reset;
        flag = true;
        break;
      }

    }

  }
  if (pressed_key == 'B')
  {
    while (pressed_key != '*')
    {
      pressed_key = key();
      //      Serial.println("pressed_key:" + String(pressed_key));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("EMPLOYEE_INFO:");
      lcd.setCursor(15, 0);
      lcd.print("EMPLOYEE_INFO:");
      soil("*EMPLOYEE_INFO:#");
      soil("*" + String(pressed_key) + "#");
      if (pressed_key == '*')
      {
        pressed_key = 'x';
        key() == Reset;
        flag = true;
        break;
      }
    }
  }
}

void soil(String s) {
  for (int h = 0; h < s.length(); h++) {
    Serial.write(s[h]);
  }
  delay(2500);
}
