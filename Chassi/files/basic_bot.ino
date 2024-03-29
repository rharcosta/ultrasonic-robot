/***********************************************
  Basic 2-wheeled obstacle avoiding buggy with:
  Battery (9v), SPST (On/Off switch),
  Arduino Nano, Sonic Sensor (HC-SR04),
  2 DC Motors, DC Motor Driver (L298N) 
/***********************************************/
int trigPin = 7;      
int echoPin = 8;      
long duration, distance;
int revLeft = 5;       
int fwdLeft = 6;       
int revRight = 9;      
int fwdRight = 10;     
/***********************************************/
void setup() {
 // Serial.begin(9600);
  pinMode(revLeft, OUTPUT);
  pinMode(fwdLeft, OUTPUT);
  pinMode(revRight, OUTPUT);
  pinMode(fwdRight, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);     
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;   
  delay(10);
  if (distance > 20){
    digitalWrite(fwdLeft, HIGH);
    digitalWrite(revLeft, LOW); 
    digitalWrite(fwdRight, HIGH);
    digitalWrite(revRight, LOW);
  }
  if (distance < 20){
    // Stop
    digitalWrite(fwdRight, LOW);  
    digitalWrite(revRight, LOW);
    digitalWrite(fwdLeft, LOW);
    digitalWrite(revLeft, LOW);
    delay(500);
    // Reverse
    digitalWrite(fwdLeft, LOW);
    digitalWrite(revLeft, HIGH);
    delay(10);
    digitalWrite(fwdRight, LOW);      
    digitalWrite(revRight, HIGH);
    delay(500);
    // Stop
    digitalWrite(fwdRight, LOW);  
    digitalWrite(revRight, LOW);
    digitalWrite(fwdLeft, LOW);
    digitalWrite(revLeft, LOW);
    delay(100);
    //Turn Left
    digitalWrite(revLeft, LOW);
    digitalWrite(fwdLeft, HIGH);
    delay(10);
    digitalWrite(fwdRight, LOW);
    digitalWrite(revRight, LOW);
    delay(500);
  }
}