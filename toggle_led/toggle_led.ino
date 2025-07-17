#define LED_PIN 3
#define BUTTON_PIN 2
byte lastButtonState =LOW;
byte ledState=LOW;

void setup(){
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  Serial.begin(9600);
}

void loop(){
  byte buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != lastButtonState){
    lastButtonState = buttonState;
    if(buttonState == LOW){
      ledState = (ledState==HIGH)?LOW:HIGH;
      digitalWrite(LED_PIN,ledState);
    }
  }
  Serial.print("Value: ");  // Print text
  Serial.println(buttonState);
  delay(200);
}