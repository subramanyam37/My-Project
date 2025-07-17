
void setup(){
 pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
   pinMode(6,OUTPUT);
    pinMode(8,OUTPUT);
     pinMode(10,OUTPUT);
      pinMode(12,INPUT);
}
void loop(){
  byte buttonState = digitalRead(12);
  if(buttonState == LOW){
    for(int i =10 ; i>=2 ;i-=2)
    {
      digitalWrite(i,HIGH);
      delay(300);
      digitalWrite(i,LOW);
      delay(300);
    }
  }
  else{
        for(int i =2 ; i<=10 ;i+=2)
    {
      digitalWrite(i,HIGH);
      delay(300);
      digitalWrite(i,LOW);
      delay(300);
    }
  }
}
