const int BUTTON = 2;
const int LED = 3;
int BUTTONstate = 0;

void setup()
{
  pinMode(BUTTON,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(6,OUTPUT);

}
void loop()
{
  BUTTONstate = digitalRead(BUTTON);
  if(BUTTONstate == HIGH)
  {

    analogWrite(6, 200);
    digitalWrite(11, HIGH);
    digitalWrite(10,LOW);
    digitalWrite(3,HIGH);
   
  }
  else
  {
    analogWrite(6, 200);
    digitalWrite(11, LOW);
    digitalWrite(10,HIGH);
    digitalWrite(3,LOW);
  }
 
}
