const int LED = 3;
const int SOUND = 10;
const int motor = 6;
int SOUNDstate = 0;
int PREVsoundstate = 0;
int num = 0;

const int soundgap = 300;
unsigned long readsound=0; 
void setup()
{

  pinMode(LED,OUTPUT);
  pinMode(SOUND,INPUT);
  pinMode(motor,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  SOUNDstate = digitalRead(SOUND);
  if(SOUNDstate == HIGH && PREVsoundstate == LOW && millis() - readsound > soundgap)
  {
    num += 1;
    readsound=millis();
    Serial.print("Sound no = ");
    Serial.println(num);
  }
  PREVsoundstate = SOUNDstate;

  if(num % 2 == 0)
  {
    analogWrite(motor,200);
    digitalWrite(LED, LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
  else
  {
    analogWrite(motor,200);
    digitalWrite(LED,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
  }
  
}