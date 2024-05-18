// us mapper thing

#include <Servo.h>

#define xPixels 90
#define yPixels 45

#define trigPin 9
#define echoPin 10

#define serXPin TOSET
#define serYPin TOSET
#define serXOffset TOSET
#define serYOffset TOSET

Servo serX;
Servo serY;

long duration;
int distance;


int arr[xPixels][yPixels];

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
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  serX.attach(serXPin);
  serY.attach(serYPin);
}

void loop() {
  for (int x = 0; x < xPixels; x++) {
    for (int y = 0; y < yPixels; y++) {
      serX.write(x+serXOffset);
      serX.write(y+serYOffset);
      
      arr[x][y] = readSensor();
    }
  }


  for (int x = 0; x < xPixels; x++) {
    for (int y = 0; y < yPixels; y++) {
      Serial.println(arr[x][y]);
    }
  }
  
}