#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

void setup() {
  motors.flipLeftMotor(false); // Invertir el motor izquierdo para que ambos motores avancen hacia adelante
  lineSensors.initFiveSensors(); // Inicializar los sensores de línea
  Serial.begin(9600);
}

void loop() {
  // Leer los valores de los sensores de línea
  unsigned int lineSensorValues[5];
  lineSensors.read(lineSensorValues);

  // Verificar si se detecta una línea negra
  if (isBlackLine(lineSensorValues)) {
    // Si se detecta una línea negra, retroceder
    motors.setSpeeds(200, 200); // Retroceder
  } 
  else {
    // Si no se detecta una línea negra, avanzar
    motors.setSpeeds(-250, -250); // Avanzar
    delay(200);

  motors.setSpeeds(150, -250);
  delay(200);
  }

  // Imprimir los valores de los sensores de línea
  Serial.print("Sensor Values: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(lineSensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(50); // Esperar un tiempo antes de la próxima lectura
}

// Función para verificar si se detecta una línea negra
bool isBlackLine(unsigned int sensorValues[]) {
  // Comprobar si alguno de los sensores de línea está por debajo de un umbral para detectar una línea negra
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] < 250) { // Umbral ajustable según la sensibilidad de los sensores
      return true;
    }
  }
  return false;
}
