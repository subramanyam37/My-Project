void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
}


void loop() {
  for(int a=2;a<=12;a+=2)
  {
  digitalWrite(a, HIGH);  
  delay(500);                      
  digitalWrite(a, LOW);   
  delay(500);   
  }
for(int a=12;a>=2;a-=2)
  {
  digitalWrite(a, HIGH);  
  delay(500);                      
  digitalWrite(a, LOW);   
  delay(500);   
  }
}
