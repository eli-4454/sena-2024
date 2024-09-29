#include "BluetoothSerial.h"


BluetoothSerial serialBT;

//Señal Bluetooth Almacenar en esta variable
char btSignal;

//Velocidad inicial del Bot
int Speed = 100;

/*FOR RIGHT MOTOR*/
int RPWM = 5;

/*FOR LEFT MOTOR*/
int LPWM = 4;


//declarar canal para salida pwm
#define R 0
#define L 1

//Define in1/in2/in3/in4 pin
int IN1 = 16;
int IN2 = 17;
int IN3 = 18;
int IN4 = 19;

// Define el pin al que está conectado el buzzer
const int buzzerPin = 25; // Puedes usar cualquier otro pin GPIO

void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("NEXUS2024");

  //output pin declare
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

#define LEFT_PWM_PIN 4
#define RIGHT_PWM_PIN 5

#define PWM_FREQUENCY 20000
#define PWM_RESOLUTION 8

  // Setup PWM channels
  Serial.begin(115200);
  
  // Configurar pines de PWM
  pinMode(LEFT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  pinMode(buzzerPin, OUTPUT);
}

// Función para hacer sonar el buzzer con una frecuencia específica (en Hz) y una duración (en milisegundos)
void playBuzzer(unsigned int frequency, unsigned int duration) {
  unsigned long periodMicros = 1000000UL / frequency;
  unsigned long pulseWidthMicros = periodMicros / 2;

  for (unsigned long elapsedMicros = 0; elapsedMicros < (duration * 1000UL); elapsedMicros += periodMicros) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(pulseWidthMicros);
  }
}

void loop() {

  while (serialBT.available()) {
    btSignal = serialBT.read();
    //Serial.println(btSignal);

    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

    if (btSignal == 'F')  //forward
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    else if (btSignal == 'B')  //backward
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

    }

    else if (btSignal == 'L')  //LEFT
    {

      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    else if (btSignal == 'R')  //RIGHT
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      
    }

    else if (btSignal == 'S')  //STOP
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
     else if (btSignal == 'V')  //BUZZER
    {
       playBuzzer(2000, 1000);
    }
  }
}
