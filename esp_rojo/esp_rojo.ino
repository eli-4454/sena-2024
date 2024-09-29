#include <BluetoothSerial.h>

// Inicializar Bluetooth para ESP32
BluetoothSerial bluetooth;

// Definición de pines para los motores
const int Motor1A = 5;
const int Motor1B = 18;
const int Motor2A = 19;
const int Motor2B = 21;

void setup() {
    bluetooth.begin("ESP32_Bluetooth");  // Nombre del dispositivo Bluetooth

    pinMode(Motor1A, OUTPUT);
    pinMode(Motor1B, OUTPUT);
    pinMode(Motor2A, OUTPUT);
    pinMode(Motor2B, OUTPUT);

    detenerMotores();
}

void loop() {
    if (bluetooth.available()) {
        char comando = (char)bluetooth.read();
        ejecutarComando(comando);
    }
}

void ejecutarComando(char comando) {
    switch (comando) {
        case 'S':  // Stop
            detenerMotores();
            break;
        case 'F':  // Adelante
            moverAdelante();
            break;
        case 'B':  // Atrás
            moverAtras();
            break;
        case 'L':  // Izquierda
            girarIzquierda();
            break;
        case 'R':  // Derecha
            girarDerecha();
            break;
        case 'G':  // Adelante-Izquierda
            moverAdelanteIzquierda();
            break;
        case 'I':  // Adelante-Derecha
            moverAdelanteDerecha();
            break;
        case 'H':  // Atrás-Izquierda
            moverAtrasIzquierda();
            break;
        case 'J':  // Atrás-Derecha
            moverAtrasDerecha();
            break;
        default:
            detenerMotores();
            break;
    }
}

void detenerMotores() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
}

void moverAdelante() {
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, HIGH);
    digitalWrite(Motor2B, LOW);
}

void moverAtras() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, HIGH);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, HIGH);
}

void girarIzquierda() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, HIGH);
    digitalWrite(Motor2A, HIGH);
    digitalWrite(Motor2B, LOW);
}

void girarDerecha() {
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, HIGH);
}

void moverAdelanteIzquierda() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, HIGH);
    digitalWrite(Motor2B, LOW);
}

void moverAdelanteDerecha() {
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
}

void moverAtrasIzquierda() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, HIGH);
}

void moverAtrasDerecha() {
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, HIGH);
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
}    
