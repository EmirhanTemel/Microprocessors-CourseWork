#include <Arduino.h>

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>

#define LED_PIN 13
#define MZ80_PIN 6
#define NUM_SENSORS 6
 
//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;

// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // --------------------------- Start Of The Calibration -------------------------
  reflectanceSensors.init();
  unsigned long startTime = millis();
  while (millis() - startTime < 5000)  // make the calibration take 10 seconds
  {
    reflectanceSensors.calibrate();
  }
  // ------------------- End Of The Calibration -----------------------
}

unsigned int mostLeftSensor() {
  if (sensorValues[0] < 600)
    return 1;
  else
    return 0;
}

unsigned int leftSensor() {
  if (sensorValues[1] < 600)
    return 1;
  else
    return 0;
}

unsigned int midLeftSensor() {
  if (sensorValues[2] < 600)
    return 1;
  else
    return 0;
}

unsigned int midRightSensor() {
  if (sensorValues[3] < 600)
    return 1;
  else
    return 0;
}

unsigned int rightSensor() {
  if (sensorValues[4] < 600)
    return 1;
  else
    return 0;
}

unsigned int mostRightSensor() {
  if (sensorValues[5] < 600)
    return 1;
  else
    return 0;
}

void turnRight() {
  motors.setSpeeds(150, -150); // The negative sign indictes that the right motor will rotate in the opposite direction to the left motor, causing the robot to turn right.
}

void stop() { 
  motors.setSpeeds(0, 0);
}


void loop() {
  static unsigned long startTime = millis();  // Declare startTime as static to retain its value across iterations
  static int count = 0;  // Declare count as static to retain its value across iterations
  static int i = 0;  // Declare i as static to retain its value across iterations
  static bool conditionTriggered = false;  // Flag variable to track if the condition has been triggered
  
  if (millis() - startTime < 4000) {
    turnRight();
    if (digitalRead(MZ80_PIN) && !conditionTriggered) {
      count++;
      conditionTriggered = true;  // Set the flag to true to avoid multiple increments within a single iteration
    }
    else if (!digitalRead(MZ80_PIN)) {
      conditionTriggered = false;  // Reset the flag when the condition is no longer triggered
    }
  }
  else {
    stop();
    if (i < count-1) {
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
      i++;
    }
    else {
      // Reset the count, i, and conditionTriggered variables
      count = 0;
      i = 0;
      conditionTriggered = false;
    }
  }
}

