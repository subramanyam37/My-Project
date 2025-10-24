#include <Arduino.h>

const int soundSensorPin = 2;

const int IN1_LF = 7;
const int IN2_LF = 6;

const int IN1_LR = 5;
const int IN2_LR = 4;

const int IN1_RF = 8;
const int IN2_RF = 13;

const int IN1_RR = 12;
const int IN2_RR = 11; 

enum RobotState {
    STOPPED,
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT
};

RobotState currentState = STOPPED;

const int motorSpeed = 250; 

volatile bool soundDetected = false; 
volatile unsigned long lastSoundTime = 0; 

int clapCount = 0;
unsigned long lastClapTime = 0; 
const unsigned long clapDetectionWindow = 1500; 
const unsigned long soundDebounceDelay = 300;   

void detectClap();
void processSound(); 
void moveRobot(RobotState state);
void stopMotors();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();


void setup() {
    Serial.begin(9600);
    
    pinMode(IN1_LF, OUTPUT);
    pinMode(IN2_LF, OUTPUT);
    pinMode(IN1_LR, OUTPUT);
    pinMode(IN2_LR, OUTPUT);
    pinMode(IN1_RF, OUTPUT);
    pinMode(IN2_RF, OUTPUT);
    pinMode(IN1_RR, OUTPUT);
    pinMode(IN2_RR, OUTPUT); 

    pinMode(soundSensorPin, INPUT);
    
    stopMotors(); 

    attachInterrupt(digitalPinToInterrupt(soundSensorPin), detectClap, RISING);

    Serial.println("Robot Ready. Awaiting Claps! (New robust clap logic active)");
}


void loop() {
    if (soundDetected) {
        processSound();
    }
    
    if (clapCount > 0 && (millis() - lastClapTime > clapDetectionWindow)) {
        
        int commandClapCount = clapCount; 
        clapCount = 0; 
        
        Serial.print("Detected ");
        Serial.print(commandClapCount);
        Serial.println(" clap(s). Processing command.");
        
        switch (commandClapCount) {
            case 1:
                if (currentState == FORWARD) {
                    moveRobot(BACKWARD);
                } else if (currentState == BACKWARD) {
                    moveRobot(STOPPED);
                } else {
                    moveRobot(FORWARD); 
                }
                break;
            
            case 2:
                if (currentState == TURN_LEFT) {
                    moveRobot(TURN_RIGHT);
                } else if (currentState == TURN_RIGHT) {
                    moveRobot(STOPPED);
                } else {
                    moveRobot(TURN_LEFT); 
                }
                break;
            
            case 3:
                moveRobot(STOPPED);
                break;

            default:
                Serial.println("Command not recognized (1-3 claps only). Ignoring.");
                break;
        }
    }
}

void detectClap() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastSoundTime > soundDebounceDelay) {
        soundDetected = true;
        lastSoundTime = currentTime;
    }
}

void processSound() {
    soundDetected = false; 
    
    unsigned long currentTime = lastSoundTime; 
    
    if (clapCount > 0 && (currentTime - lastClapTime < clapDetectionWindow)) {
        clapCount++;
        Serial.print("Clap registered: ");
        Serial.println(clapCount);
    } else {
          clapCount = 1;
          Serial.println("New clap sequence started: 1");
    }

    lastClapTime = currentTime;
}

void moveRobot(RobotState newState) {
    currentState = newState;
    Serial.print("New State: ");
    
    switch (currentState) {
        case FORWARD:
            moveForward();
            Serial.println("FORWARD");
            break;
        case BACKWARD:
            moveBackward();
            Serial.println("BACKWARD");
            break;
        case TURN_LEFT:
            turnLeft();
            Serial.println("TURN_LEFT");
            break;
        case TURN_RIGHT:
            turnRight();
            Serial.println("TURN_RIGHT");
            break;
        case STOPPED:
        default:
            stopMotors();
            Serial.println("STOPPED");
            break;
    }
}

void stopMotors() {
    digitalWrite(IN1_LF, LOW);
    digitalWrite(IN2_LF, LOW);
    digitalWrite(IN1_LR, LOW);
    digitalWrite(IN2_LR, LOW);
    digitalWrite(IN1_RF, LOW);
    digitalWrite(IN2_RF, LOW);
    digitalWrite(IN1_RR, LOW);
    digitalWrite(IN2_RR, LOW);
}

void moveForward() {
    digitalWrite(IN1_LF, HIGH);
    digitalWrite(IN2_LF, LOW);
    digitalWrite(IN1_LR, HIGH);
    digitalWrite(IN2_LR, LOW);

    digitalWrite(IN1_RF, HIGH);
    digitalWrite(IN2_RF, LOW);
    digitalWrite(IN1_RR, HIGH);
    digitalWrite(IN2_RR, LOW);
}

void moveBackward() {
    digitalWrite(IN1_LF, LOW);
    digitalWrite(IN2_LF, HIGH);
    digitalWrite(IN1_LR, LOW);
    digitalWrite(IN2_LR, HIGH);

    digitalWrite(IN1_RF, LOW);
    digitalWrite(IN2_RF, HIGH);
    digitalWrite(IN1_RR, LOW);
    digitalWrite(IN2_RR, HIGH);
}

void turnLeft() {
    digitalWrite(IN1_LF, LOW);
    digitalWrite(IN2_LF, HIGH);
    digitalWrite(IN1_LR, LOW);
    digitalWrite(IN2_LR, HIGH);

    digitalWrite(IN1_RF, HIGH);
    digitalWrite(IN2_RF, LOW);
    digitalWrite(IN1_RR, HIGH);
    digitalWrite(IN2_RR, LOW);
}

void turnRight() {
    digitalWrite(IN1_LF, HIGH);
    digitalWrite(IN2_LF, LOW);
    digitalWrite(IN1_LR, HIGH);
    digitalWrite(IN2_LR, LOW);

    digitalWrite(IN1_RF, LOW);
    digitalWrite(IN2_RF, HIGH);
    digitalWrite(IN1_RR, LOW);
    digitalWrite(IN2_RR, HIGH);
}
