#include <Servo.h>
Servo myservo;

void setup() {
   myservo.attach(2);
}

void loop() {
 myservo.write(0);
 delay(1000);
 myservo.write(45);
 delay(1000);
 myservo.write(90);
 delay(1000);  
 myservo.write(45);
 delay(1000);
 myservo.write(0);
 delay(1000);
  }
