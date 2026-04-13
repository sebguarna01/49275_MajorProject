#include <Servo.h>

Servo myservo;

const int trigPin = 7;
const int echoPin = 6;

long duration;
float distance;

int pos = 90;  // start in middle

// --- Control ---
float target = 15.0;

float Kp = 0.550;
float Kd = 0.10;

float prevError = 0;

void setup() {
  myservo.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // --- Ultrasonic read ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // timeout prevents blocking

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);

  // --- PD Control ---
  float error = distance - target;
  float dt = 0.01; // 10 ms loop
  float derivative = (error - prevError) / dt;

  float output = Kp * error + Kd * derivative;

  // deadband
  if (abs(error) < 0.5) {
    output = 0;
  }

  float maxStep = 0.5 + abs(error) * 0.5;
  maxStep = constrain(maxStep, 1.0, 15.0);

  output = constrain(output, -maxStep, maxStep);

  pos += output;

  pos -= 0.2 * (pos - 90);

  pos = constrain(pos, 45, 150);
  myservo.write(pos);

  prevError = error;

  Serial.print(" | Pos: ");
  Serial.println(pos);


  delay(10);
}
