void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}


void loop() {
for(int a=2;a<=6;a+=2)
  {
  digitalWrite(a, HIGH);  
  delay(1000);                      
  digitalWrite(a, LOW);   
  delay(1000);   
  }
}
