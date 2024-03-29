//Carrega biblioteca do sensor
#include <Ultrasonic.h>

//Definindo pinos do sensor
#define pino_trigger 13
#define pino_echo 11

//Definindo pinos do motor
int IN1 = 4;
int IN2 = 5;
#define PWMA 3
int IN3 = 6;
int IN4 = 7;
#define PWMB 10

//Variáveis de velocidade
int Vmax = 110;
int Vmin = 0;
int Vmedia = 110;

//Variáveis do PID
float Kp = 0.07; //related to the proportional control term;
//change the value by trial-and-error (ex: 0.07).
float Ki = 0.0008; //related to the integral control term;
//change the value by trial-and-error (ex: 0.0008).
float Kd = 0.6; //related to the derivative control term;
//change the value by trial-and-error (ex: 0.6).
int P;
int I;
int D;
int lastError = 0;

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup() {

  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //Iniciando serial
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}

void forward_brake(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(PWMA, posa);
  analogWrite(PWMB, posb);
}

void loop() {

  //Le as informações do sensor em cm
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  //Exibe informações no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  //delay(1000); --> tiramos para parar na hora

  //Inicia motores
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //delay(10000);

  int motorspeeda = Vmedia;
  int motorspeedb = Vmedia;

  if (motorspeeda > Vmax) {
    motorspeeda = Vmax;
  }
  if (motorspeedb > Vmax) {
    motorspeedb = Vmax;
  }
  forward_brake(motorspeeda, motorspeedb);

  //Detecta objeto
  if (cmMsec <= 16) {

    //Inverte motores
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //delay(10000);

  } else if (cmMsec <= 20 && cmMsec >= 17) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

  }

}
