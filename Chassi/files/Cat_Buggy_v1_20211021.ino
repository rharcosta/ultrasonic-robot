/***********************************************************
  Basic Obstacle Avoiding Buggy v.20211021
  by Nat Weinham, and everyone else on the internet.

  Arduino Nano; HC-SR04 Sonic Sensor; 
  L298N Motor Driver; 2x DC Motors; 
  3.7v LiPo connected to Boost (usb 18650 charger-boost 3.7v-12v) 
  pushes 12v into L298N, then the L298N outputs 5v for the Nano et al.
  see here for 3D Printed chassis: Cat_Buggy
/***********************************************************/

/************* works  **************************************/
// motor A
const int enA = 3;  // pwm
const int mA1 = 8;
const int mA2 = 7;
// motor B
const int enB = 6;  // pwm
const int mB1 = 5;
const int mB2 = 4;
/***********************************************************/

const int topSpeed = 150; // 75-255
const int lowSpeed = topSpeed/2;

// HC-SR04 sonic sensor
const int trigPin = A0;  // analog pin 0
const int echoPin = A1;  // analog pin 1
long duration, distance, randomNumber;
int first_time = 1;  // pause to establish distance

void setup() {
  Serial.begin(9600);
  // intitialize motor pins
  pinMode(enA, OUTPUT);
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  // turn motors off
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB1, LOW);
  // HC-SR04
  pinMode(echoPin, INPUT);   // echo = INPUT
  pinMode(trigPin, OUTPUT);  // trig = OUTPUT
}
void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;  // distance math
  if (first_time) {
    // at startup, HC-SR04 has a low "distance" value
    // so let's start it off on the good foot.
    first_time = 0;
    distance = 100;
  }
  delay(10);
  if (distance > 20) {
    // continue moving forward.
    // Serial.print("Distance: ");Serial.println(distance);
    forward();
  } else {
    // too close! Backup and turn
    // Serial.print("ALERT: ");Serial.println(distance);
    adapt();
  }
  delay(10);
}
void forward() {
  analogWrite(enA, topSpeed);
  analogWrite(enB, topSpeed);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void adapt() {
  full_stop();
  delay(300);
  backward();
  delay(300);
  full_stop();
  delay(300);
  // randomly select Left OR Right turn.
  randomNumber = random(9);
  // randomNumber%2==1 checks even/odd values
  if (randomNumber % 2 == 1) {
    turn_left();
  } else {
    turn_right();
  }
  delay(500);
}
void backward() {
  analogWrite(enA, lowSpeed);
  analogWrite(enB, lowSpeed);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void turn_left() {
  analogWrite(enA, lowSpeed);
  analogWrite(enB, lowSpeed);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void turn_right() {
  analogWrite(enA, lowSpeed);
  analogWrite(enB, lowSpeed);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void full_stop() {
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}
void loop() {
  measureDistance();
}