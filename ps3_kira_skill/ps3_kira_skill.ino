#include <Ps3Controller.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir pines para los motores
#define IN1_A 12
#define IN2_A 13
#define IN1_B 27
#define IN2_B 4

#define SPEED_SCALE 2 // Factor de escala para ajustar la sensibilidad del control de velocidad

// Definir el ancho y alto del display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Crear una instancia del display OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Imagen bitmap de "play"
const unsigned char epd_bitmap_play [] PROGMEM = {// '34', 128x64px

};

void setupMotors() {
    pinMode(IN1_A, OUTPUT);
    pinMode(IN2_A, OUTPUT);
    pinMode(IN1_B, OUTPUT);
    pinMode(IN2_B, OUTPUT);
}

void notify() {
    // Obtener valores de los sticks analógicos
    int leftJoyY = Ps3.data.analog.stick.ly; // Joystick izquierdo (adelante/atrás)
    int rightJoyX = Ps3.data.analog.stick.rx; // Joystick derecho (giro)

    // Invertir el valor del joystick izquierdo para que hacia adelante sea positivo
    int scaledSpeedForward = leftJoyY * SPEED_SCALE;
    // Aplicar factor de escala a la velocidad del motor para el giro
    int scaledSpeedTurn = rightJoyX * SPEED_SCALE;

    // Mapear el valor del joystick izquierdo escalado a una velocidad de motor para el movimiento hacia adelante/atrás
    int motorSpeedForward = map(scaledSpeedForward, -128 * SPEED_SCALE, 127 * SPEED_SCALE, -220, 220);
    // Mapear el valor del joystick derecho escalado a una velocidad de motor para el giro
    int motorSpeedTurn = map(scaledSpeedTurn, -128 * SPEED_SCALE, 127 * SPEED_SCALE, -220, 220);

    // Calcular las velocidades de los motores basadas en el control diferencial
    int leftMotorSpeed = motorSpeedForward + motorSpeedTurn;
    int rightMotorSpeed = motorSpeedForward - motorSpeedTurn;

    // Limitar los valores de velocidad a [-255, 255]
    leftMotorSpeed = constrain(leftMotorSpeed, -100, 240);
    rightMotorSpeed = constrain(rightMotorSpeed, -240, 100);
    // Controlar los motores con las velocidades calculadas
    // Motor A (izquierdo)
    if (leftMotorSpeed > 0) {
        analogWrite(IN1_A, leftMotorSpeed);
        analogWrite(IN2_A, 0);
    } else if (leftMotorSpeed < 0) {
        analogWrite(IN1_A, 0);
        analogWrite(IN2_A, -leftMotorSpeed);
    } else {
        analogWrite(IN1_A, 0);
        analogWrite(IN2_A, 0);
    }

    // Motor B (derecho)
    if (rightMotorSpeed > 0) {
        analogWrite(IN1_B, rightMotorSpeed);
        analogWrite(IN2_B, 0);
    } else if (rightMotorSpeed < 0) {
        analogWrite(IN1_B, 0);
        analogWrite(IN2_B, -rightMotorSpeed);
    } else {
        analogWrite(IN1_B, 0);
        analogWrite(IN2_B, 0);
    }
}

void onConnect() {
    Serial.println("Connected.");
}

void setup() {
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("00:25:56:45:Ob:c3");  // Iniciar con la dirección MAC específica

    setupMotors();  // Configurar los pines de los motores
    Serial.println("Ready.");

    // Inicializar el display OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Loop infinito para detener la ejecución si la inicialización falla
    }

    // Limpiar el buffer del display
    display.clearDisplay();

    // Mostrar la imagen bitmap
    display.drawBitmap(0, 0, epd_bitmap_play, 128, 64, SSD1306_WHITE);
    display.display();
}

void loop() {
    if (!Ps3.isConnected())
        return;

    delay(100); // Esperar un breve período para evitar saturar la CPU
}
