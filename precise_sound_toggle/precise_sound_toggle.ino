const int LED = 3;
const int SOUND = 10;

int SOUNDstate = 0;
int PREVsoundstate = 0;
int num = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 300;  // 300 ms cooldown

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SOUND, INPUT);
  Serial.begin(9600);
}

void loop() {
  SOUNDstate = digitalRead(SOUND);
  unsigned long currentTime = millis();

  // Detect rising edge AND check debounce
  if (SOUNDstate == HIGH && PREVsoundstate == LOW && (currentTime - lastDebounceTime > debounceDelay)) {
    num++;
    Serial.print("Sound Number: ");
    Serial.println(num);
    lastDebounceTime = currentTime;
  }

  PREVsoundstate = SOUNDstate;

  // Toggle LED based on clap count
  if (num % 2 == 0) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}
