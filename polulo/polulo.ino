// Definir los pines de los sensores infrarrojos de línea
#define LEFT_SENSOR_PIN A0
#define RIGHT_SENSOR_PIN A1

// Definir los pines de los sensores de persecución
#define LEFT_CHASE_SENSOR_PIN A2
#define RIGHT_CHASE_SENSOR_PIN A3

// Definir los pines de los motores
#define LEFT_MOTOR_PIN 9
#define RIGHT_MOTOR_PIN 10

// Definir los umbrales de detección de línea y de persecución
#define LINE_THRESHOLD 500
#define CHASE_THRESHOLD 100

void setup() {
  // Inicializar los pines de los sensores como entradas
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  pinMode(LEFT_CHASE_SENSOR_PIN, INPUT);
  pinMode(RIGHT_CHASE_SENSOR_PIN, INPUT);

  // Inicializar los pines de los motores como salidas
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
}

void loop() {
  // Leer los valores de los sensores
  int leftSensorValue = analogRead(LEFT_SENSOR_PIN);
  int rightSensorValue = analogRead(RIGHT_SENSOR_PIN);
  int leftChaseSensorValue = analogRead(LEFT_CHASE_SENSOR_PIN);
  int rightChaseSensorValue = analogRead(RIGHT_CHASE_SENSOR_PIN);

  // Verificar si se detecta una línea negra
  int leftOnLine = (leftSensorValue > LINE_THRESHOLD);
  int rightOnLine = (rightSensorValue > LINE_THRESHOLD);

  // Verificar si se detecta al objetivo
  int leftChasing = (leftChaseSensorValue < CHASE_THRESHOLD);
  int rightChasing = (rightChaseSensorValue < CHASE_THRESHOLD);

  // Determinar la velocidad de los motores
  int leftSpeed = 0;
  int rightSpeed = 0;

  if (leftChasing && rightChasing) {
    // Ambos sensores de persecución detectan al objetivo, perseguir con máxima velocidad
    leftSpeed = 255;
    rightSpeed = 255;
  } else if (leftOnLine && !rightOnLine) {
    // Girar a la derecha para mantenerse en la línea
    leftSpeed = 200;
    rightSpeed = 100;
  } else if (!leftOnLine && rightOnLine) {
    // Girar a la izquierda para mantenerse en la línea
    leftSpeed = 100;
    rightSpeed = 200;
  } else if (leftOnLine && rightOnLine) {
    // Retroceder si ambos sensores de línea detectan la línea
    leftSpeed = -150;
    rightSpeed = -150;
  } else {
    // Avanzar en línea recta
    leftSpeed = 150;
    rightSpeed = 150;
  }

  // Controlar la velocidad de los motores
  analogWrite(LEFT_MOTOR_PIN, abs(leftSpeed));
  analogWrite(RIGHT_MOTOR_PIN, abs(rightSpeed));

  // Controlar la dirección de los motores
  if (leftSpeed < 0) digitalWrite(LEFT_MOTOR_PIN + 1, HIGH);
  else digitalWrite(LEFT_MOTOR_PIN + 1, LOW);

  if (rightSpeed < 0) digitalWrite(RIGHT_MOTOR_PIN + 1, HIGH);
  else digitalWrite(RIGHT_MOTOR_PIN + 1, LOW);
}