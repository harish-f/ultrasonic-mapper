#include <Servo.h>

// pins for ultrasonic sensor
#define trigPin 5
#define echoPin 6

#define serXPin 11 // x servo pin
#define serYPin 10 // y servo pin
#define serXOffset 90 // minimum y value of servo that you want
#define serYOffset 45 // minimum y value of servo that you want

// initialise x and y servos
Servo serX;
Servo serY;

// variables to store image data
int xPixels;
int yPixels;

int xAngle;
int yAngle;

// variables for processing distance value
long duration;
int distance;


// function to measure distance from sensor and returns an integer
int readSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}


void setup() {
// initialise serial communication
  Serial.begin(9600);
  Serial.setTimeout(50);

// initialise sensor and servo pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

// attach servos to their pins
  serX.attach(serXPin);
  serY.attach(serYPin);

// set servos to starting positions
  serX.write(serXOffset);
  serY.write(serYOffset);
  delay(500);

// Simple test to test communication with arduino
// Sends back summed up pixel and angle values received from python
  while (!Serial.available());
  xPixels = Serial.readString().toInt();
  while (!Serial.available());
  yPixels = Serial.readString().toInt();

  while (!Serial.available());
  xAngle = Serial.readString().toInt();
  while (!Serial.available());
  yAngle = Serial.readString().toInt();

  Serial.print(xPixels+yPixels+xAngle+yAngle);

  delay(1000);

  for (int xVal = 0; xVal < xPixels; xVal++) {
    serX.write(map(xVal, 0, xPixels ,serXOffset, serXOffset + xAngle));
    delay(500); // delay to give time for servo to move

    for (int yVal = 0; yVal < yPixels; yVal++) {
      serY.write(map(yVal, 0, yPixels ,serYOffset, serYOffset + yAngle));
      delay(500); // delay to give time for servo to move
      Serial.print(readSensor()); // read from sensor and send to python
      delay(100); // buffer
    }
  }
}

void loop() {
  // press reset on arduino to restart "imaging"
}