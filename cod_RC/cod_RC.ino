#include "ROBLEX.h"
#include "BluetoothSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Ejemplo controlar robot con la aplicacion de celular o control remoto

// CONECTAR EL MODULO DRIVER DE MOTOR IZQUIERDO EN EL PUERTO 4,  EL DERECHO EN EL PUERTO 5 Y LA PANTALLA EN CUALQUIER OTRO

ROBLEX ROBLEX;

BluetoothSerial SerialBT;
String RobotName = "KIRA";  // nombre del robot en el buletooth


//Señal Bluetooth Almacenar en esta variable
char btSignal;

//Velocidad inicial del robot
int Speed = 22;

#define LEFT_PWM MCPWM_UNIT_0
#define RIGHT_PWM MCPWM_UNIT_1

Adafruit_SSD1306 display(128, 64, &Wire, -1);  // configurar la pantalla oled

void setup() {

  //Configurar los motores en los puertos respectivos con una frecuencia de pwm de 20000
  ROBLEX.SetupMotor(4, LEFT_PWM, 20000);
  ROBLEX.SetupMotor(5, RIGHT_PWM, 20000);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // iniciar la pantalla oled
  display.clearDisplay();
  display.drawBitmap(0, 0, ROBLEX.LogoRoblex, 128, 64, WHITE);  //imprimir imagen del logo ROBLEX en la pantalla

  int namePosition = round((128 - RobotName.length() * 5) / 2);  // calcular la posicion del nombre en la pantalla segun el largo del nombre

  //imprimir el nombre en la pantalla
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(namePosition, 0);
  display.print(RobotName);
  display.display();


  Serial.begin(115200);

  SerialBT.begin(RobotName);  //iniciar la comunicacion bluetooth con el nombre asignado
  Serial.println(SerialBT.getBtAddressString());
}

//crear funcion para mover los motores
void Drive(mcpwm_unit_t unit, int out) {

  if (out < 0) {
    ROBLEX.MotorForward(unit, abs(out));

  } else if (out > 0) {
    ROBLEX.MotorBackward(unit, out);

  } else {
    ROBLEX.MotorStop(unit);
  }
}


void loop() {


  while (SerialBT.available()) {
    btSignal = SerialBT.read();
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
      Drive(LEFT_PWM, -250);
      Drive(RIGHT_PWM, 250);
    }

    else if (btSignal == 'B')  //backward
    {
      Drive(LEFT_PWM, 250);
      Drive(RIGHT_PWM, -250);

    }

    else if (btSignal == 'L')  //left
    {

      Drive(LEFT_PWM, -120);
      Drive(RIGHT_PWM, 0);
    }

    else if (btSignal == 'R')  //right
    {
      Drive(LEFT_PWM, 0);
      Drive(RIGHT_PWM, 120);
    }

    else if (btSignal == 'S')  //STOP
    {
      Drive(LEFT_PWM, 0);
      Drive(RIGHT_PWM, 0);
    }
    else if (btSignal == 'G') // forward left - diagonal izquierda
    {
      Drive(LEFT_PWM, -100);
      Drive(RIGHT_PWM, 35);
    }
    else if (btSignal == 'I') // forward right - diagonal derecha
    {
      Drive(LEFT_PWM, -35);
      Drive(RIGHT_PWM, 100);
    }
    else if (btSignal == 'H') // back left - atrás + izquierda
    {
      Drive(LEFT_PWM, 35);
      Drive(RIGHT_PWM, -100);
    }
    else if (btSignal == 'J') // back right - atrás + derecha
    {
      Drive(LEFT_PWM, 100);
      Drive(RIGHT_PWM, -35);
    }
  }
}