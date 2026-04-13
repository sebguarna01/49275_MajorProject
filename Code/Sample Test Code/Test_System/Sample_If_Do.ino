#include <Servo.h>

Servo myservo;

const int trigPin = 7;
const int echoPin = 6;

long duration;
float distance;

int pos = 90;

float target = 15.0;

void setup() {
  myservo.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // --- Read distance ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);

  // --- Simple control ---
  if (distance > target + 1) {
    pos += 1;  // move one way
  }
  else if (distance < target - 1) {
    pos -= 1;  // move other way
  }
  // else do nothing (close enough)

  pos = constrain(pos, 45, 150);

  myservo.write(pos);

  Serial.print(" | Pos: ");
  Serial.println(pos);

  delay(20);
}
