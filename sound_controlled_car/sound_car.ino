// --- Pin Definitions (Updated for Driver with hardwired Enables) ---
// Note: PWM (EN) pins are no longer used or defined.

const int soundSensorPin = 2;

// Motor 1 (Left Front)
const int IN1_LF = 7;
const int IN2_LF = 6;

// Motor 2 (Left Rear)
const int IN1_LR = 5;
const int IN2_LR = 4;

// Motor 3 (Right Front)
const int IN1_RF = 8;
const int IN2_RF = 13;

// Motor 4 (Right Rear)
const int IN1_RR = 12;
const int IN2_RR = 11; 

// --- Robot State Machine ---
enum RobotState {
    STOPPED,
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT
};

RobotState currentState = STOPPED;

const int motorSpeed = 250; 

// --- Clap Detection Parameters ---
// NOTE: These variables are now volatile as they are shared between the ISR and loop()
volatile bool soundDetected = false; 
volatile unsigned long lastSoundTime = 0; // Time of the last raw sound trigger (for simple debounce)

// These variables are handled in loop()
int clapCount = 0;
unsigned long lastClapTime = 0; // Time of the last confirmed clap (for sequence counting)
const unsigned long clapDetectionWindow = 1500; // Max time (ms) to wait between claps for a sequence
const unsigned long soundDebounceDelay = 300;   // Min time (ms) between sound triggers

// --- Function Prototypes ---
void detectClap();
void processSound(); // New function to handle counting logic
void moveRobot(RobotState state);
void stopMotors();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();


void setup() {
    Serial.begin(9600);
    
    // Set all 8 Direction pins as OUTPUT
    pinMode(IN1_LF, OUTPUT);
    pinMode(IN2_LF, OUTPUT);
    pinMode(IN1_LR, OUTPUT);
    pinMode(IN2_LR, OUTPUT);
    pinMode(IN1_RF, OUTPUT);
    pinMode(IN2_RF, OUTPUT);
    pinMode(IN1_RR, OUTPUT);
    pinMode(IN2_RR, OUTPUT); 

    // Sound Sensor Input Pin
    pinMode(soundSensorPin, INPUT);
    
    stopMotors(); // Ensure motors are off at startup

    // Attach an Interrupt to the sound sensor pin (D2)
    attachInterrupt(digitalPinToInterrupt(soundSensorPin), detectClap, RISING);

    Serial.println("Robot Ready. Awaiting Claps! (New robust clap logic active)");
}


void loop() {
    // 1. Process Raw Sound Event
    if (soundDetected) {
        processSound();
    }
    
    // 2. Process Clap Sequence Timeout
    // Check if the clap detection window has expired and we have claps to process
    if (clapCount > 0 && (millis() - lastClapTime > clapDetectionWindow)) {
        
        // Temporarily store the count to avoid interrupt conflicts during command processing
        int commandClapCount = clapCount; 
        clapCount = 0; // Reset the sequence count
        
        Serial.print("Detected ");
        Serial.print(commandClapCount);
        Serial.println(" clap(s). Processing command.");
        
        switch (commandClapCount) {
            case 1:
                // 1 Clap: Cycle FORWARD -> BACKWARD -> STOPPED -> FORWARD ...
                if (currentState == FORWARD) {
                    moveRobot(BACKWARD);
                } else if (currentState == BACKWARD) {
                    moveRobot(STOPPED);
                } else {
                    moveRobot(FORWARD); 
                }
                break;
            
            case 2:
                // 2 Claps: Cycle TURN_LEFT -> TURN_RIGHT -> STOPPED -> TURN_LEFT ...
                if (currentState == TURN_LEFT) {
                    moveRobot(TURN_RIGHT);
                } else if (currentState == TURN_RIGHT) {
                    moveRobot(STOPPED);
                } else {
                    moveRobot(TURN_LEFT); 
                }
                break;
            
            case 3:
                // 3 Claps: Always STOPPED
                moveRobot(STOPPED);
                break;

            default:
                Serial.println("Command not recognized (1-3 claps only). Ignoring.");
                break;
        }
    }
}

// --- Interrupt Service Routine (ISR) for Clap Detection ---
// This routine must be FAST. It only flags that a sound occurred and updates time.
void detectClap() {
    unsigned long currentTime = millis();
    
    // Simple debounce: ensures we don't process a sound that's too close to the last one
    if (currentTime - lastSoundTime > soundDebounceDelay) {
        soundDetected = true;
        lastSoundTime = currentTime;
    }
}

// --- Clap Counting Logic (executed in the main loop) ---
void processSound() {
    // Must clear the flag immediately
    soundDetected = false; 
    
    unsigned long currentTime = lastSoundTime; // Use the time recorded in the ISR
    
    // Check if the clap is part of a sequence or starts a new one
    if (clapCount > 0 && (currentTime - lastClapTime < clapDetectionWindow)) {
         // The clap is part of an ongoing sequence
        clapCount++;
        Serial.print("Clap registered: ");
        Serial.println(clapCount);
    } else {
         // This is the first clap of a new potential sequence
         clapCount = 1;
         Serial.println("New clap sequence started: 1");
    }

    // Update the last confirmed clap time
    lastClapTime = currentTime;
}

// --- Robot Movement Control ---
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

// ------------------------------------------------------------------
// --- Motor Control Functions ---
// ------------------------------------------------------------------

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
    // Left Side (Forward)
    digitalWrite(IN1_LF, HIGH);
    digitalWrite(IN2_LF, LOW);
    digitalWrite(IN1_LR, HIGH);
    digitalWrite(IN2_LR, LOW);

    // Right Side (Forward)
    digitalWrite(IN1_RF, HIGH);
    digitalWrite(IN2_RF, LOW);
    digitalWrite(IN1_RR, HIGH);
    digitalWrite(IN2_RR, LOW);
}

void moveBackward() {
    // Left Side (Reverse)
    digitalWrite(IN1_LF, LOW);
    digitalWrite(IN2_LF, HIGH);
    digitalWrite(IN1_LR, LOW);
    digitalWrite(IN2_LR, HIGH);

    // Right Side (Reverse)
    digitalWrite(IN1_RF, LOW);
    digitalWrite(IN2_RF, HIGH);
    digitalWrite(IN1_RR, LOW);
    digitalWrite(IN2_RR, HIGH);
}

void turnLeft() {
    // Left Side (Reverse) - Spin
    digitalWrite(IN1_LF, LOW);
    digitalWrite(IN2_LF, HIGH);
    digitalWrite(IN1_LR, LOW);
    digitalWrite(IN2_LR, HIGH);

    // Right Side (Forward)
    digitalWrite(IN1_RF, HIGH);
    digitalWrite(IN2_RF, LOW);
    digitalWrite(IN1_RR, HIGH);
    digitalWrite(IN2_RR, LOW);
}

void turnRight() {
    // Left Side (Forward)
    digitalWrite(IN1_LF, HIGH);
    digitalWrite(IN2_LF, LOW);
    digitalWrite(IN1_LR, HIGH);
    digitalWrite(IN2_LR, LOW);

    // Right Side (Reverse) - Spin
    digitalWrite(IN1_RF, LOW);
    digitalWrite(IN2_RF, HIGH);
    digitalWrite(IN1_RR, LOW);
    digitalWrite(IN2_RR, HIGH);
}