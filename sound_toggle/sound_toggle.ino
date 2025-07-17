const int LED = 3;
const int SOUND = 10;
int SOUNDstate = 0;
int PREVsoundstate = 0;
int num = 1;
void setup()
{

  pinMode(LED,OUTPUT);
  pinMode(SOUND,INPUT);
}
void loop()
{
  SOUNDstate = digitalRead(SOUND);
  if(SOUNDstate == HIGH && PREVsoundstate == LOW)
  {
    num += 1;
  }
  PREVsoundstate = SOUNDstate;

  if(num % 2 == 0)
  {
    digitalWrite(LED, LOW);
    
  }
  else
  {
    digitalWrite(LED,HIGH);
 
  }
}