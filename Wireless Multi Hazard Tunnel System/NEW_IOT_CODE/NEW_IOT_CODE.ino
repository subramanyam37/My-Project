#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <SoftwareSerial.h>

SoftwareSerial ss(D1, D2);
#define buzzer D7  // Use GPIO Pin 13 (D7)

#define WLAN_SSID       "A1160"
#define WLAN_PASS       "12345678"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "A1160"
#define AIO_KEY         "aio_ECpB33dohcOLfAaGATo9zlWzFKYq"

String sensorValue1 = "", sensorValue2 = "", sensorValue3 = "", sensorValue4 = "", sensorValue5 = "";

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish value1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/info");
Adafruit_MQTT_Publish value2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gasValue");
Adafruit_MQTT_Publish value3 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/VibrationDetection");
//Adafruit_MQTT_Publish value4 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

Adafruit_MQTT_Subscribe mode0 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/mode0");

void MQTT_connect() {
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while (mqtt.connect() != 0) {
    Serial.println(mqtt.connectErrorString(mqtt.connect()));
    retries--;
    if (retries == 0) {
      while (1);
    }
    delay(5000);
  }
  Serial.println("MQTT Connected!");
}

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  pinMode(buzzer, OUTPUT);  // Ensure the buzzer is set to output

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&mode0);
}

void loop() {
  MQTT_connect();

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '*') {
      sensorValue1 = readData('#');
    }
    else if (c == '@') {
      sensorValue2 = readData('#');
    }
    else if (c == '$') {
      sensorValue3 = readData('#');
    }
//    else if (c == '^') {
//      sensorValue4 = readData('#');
//    }
//    else if (c == '&') {
//      sensorValue5 = readData('#');
//    }
  }

  // Publish sensor values if valid
  if (sensorValue1.length() > 0) {
    if (value1.publish(sensorValue1.c_str())) {
      Serial.println("Info data sent: " + sensorValue1);
    } else {
      Serial.println("Error sending info data");
    }
    blinkLED();
  }
  if (sensorValue2.length() > 0) {
    if (value2.publish(sensorValue2.c_str())) {
      Serial.println("Gas value sent: " + sensorValue2);
      int gasValue = sensorValue2.toInt();  // Convert to integer
      if (gasValue > 120) {
        triggerBuzzer();
      }
    } else {
      Serial.println("Error sending gas value");
    }
    blinkLED();
  }
  if (sensorValue3.length() > 0) {
    if (value3.publish(sensorValue3.c_str())) {
      Serial.println("Vibration detection sent: " + sensorValue3);
      int vibrationValue = sensorValue3.toInt();  // Convert to integer
      if (vibrationValue == 0) {
        triggerBuzzer();  // Trigger buzzer on vibration detection
      }
    } else {
      Serial.println("Error sending vibration detection");
    }
    blinkLED();
  }
//  if (sensorValue4.length() > 0) {
//    if (value4.publish(sensorValue4.c_str())) {
//      Serial.println("Humidity data sent: " + sensorValue4);
//    } else {
//      Serial.println("Error sending humidity data");
//    }
//    blinkLED();
//  }

  // Reset sensor values after publishing
  sensorValue1 = "";
  sensorValue2 = "";
  sensorValue3 = "";
//  sensorValue4 = "";

  handleModeChange();
}

String readData(char terminator) {
  String data = "";
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == terminator) {
      break;
    }
    data += c;
  }
  return data;
}

void blinkLED() {
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);
  delay(1000);
}

void triggerBuzzer() {
  Serial.println("ALERT! Activating buzzer...");
  digitalWrite(buzzer, HIGH);  // Turn on buzzer
  delay(2000);  // Buzzer ON for 2 sec
  digitalWrite(buzzer, LOW);  // Turn off buzzer
}

void handleModeChange() {
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &mode0) {
      char mode = mode0.lastread[0];
      switch (mode) {
        case '1':
          ss.write('A');
          break;
        case '2':
          ss.write('M');
          break;
        case '3':
          ss.write('F');
          break;
        case '4':
          ss.write('B');
          break;
        case '5':
          ss.write('R');
          break;
        case '6':
          ss.write('L');
          break;
        case '7':
          ss.write('S');
          break;
      }
    }
  }
}
