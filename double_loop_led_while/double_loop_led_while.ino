void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
}


void loop() {
  int a=0;
  while(a<=12)
  {
  digitalWrite(a, HIGH);  
  delay(100);                      
  digitalWrite(a, LOW);   
  delay(100);   
  a+=2;
  }
  int b=12;
  while(b>=2)
  {
  digitalWrite(b, HIGH);  
  delay(200);                      
  digitalWrite(b, LOW);   
  delay(200);   
  b-=2;
  }
}
