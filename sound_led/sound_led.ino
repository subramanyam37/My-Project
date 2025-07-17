const int LED = 3;
const int SOUND = 10;
int SOUNDstate = 0;

void setup()
{

  pinMode(LED,OUTPUT);
  pinMode(SOUND,INPUT);
}
void loop()
{
  SOUNDstate = digitalRead(SOUND);
  if(SOUNDstate == HIGH)
  {
    digitalWrite(LED,HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}