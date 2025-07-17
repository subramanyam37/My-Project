void setup(){
  pinMode(2,OUTPUT);
}
void loop(){
  int x=2;
  if(x==2){
    digitalWrite(2,HIGH);
    delay(1000);
  }
  else{
    digitalWrite(2,LOW);
  }
}