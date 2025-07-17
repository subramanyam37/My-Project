const int trigPin = 7;
const int echoPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {

  long duration, inches, cm;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);



  duration = pulseIn(echoPin, HIGH);


  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if(cm>35){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
  }
    else if(cm<=35 && cm>25){
          digitalWrite(2,HIGH);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(6,LOW);
    }
      else if(cm<=25 && cm>15){
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(6,LOW);
      }
        else if(cm<=15 && cm>5){
              digitalWrite(2,HIGH);
              digitalWrite(3,HIGH);
              digitalWrite(4,HIGH);
              digitalWrite(6,LOW);
        }
          else{
                   digitalWrite(2,HIGH);
                   digitalWrite(3,HIGH);
                   digitalWrite(4,HIGH);
                   digitalWrite(6,HIGH);
          }

  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
