#include "ROBLEX.h"
#include "BluetoothSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Ejemplo controlar robot con la aplicacion de celular o control remoto

// CONECTAR EL MODULO DRIVER DE MOTOR IZQUIERDO EN EL PUERTO 4,  EL DERECHO EN EL PUERTO 5 Y LA PANTALLA EN CUALQUIER OTRO

ROBLEX ROBLEX;

BluetoothSerial SerialBT;
String RobotName = "eli_17";  // nombre del robot en el buletooth

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

  if (SerialBT.available()) {

    String cmd = SerialBT.readStringUntil('\n');
    
    Serial.print(cmd);
    ROBLEX.ReadApp(cmd);  //leer la aplicacion y asigna las siguientes variables
    /*
    ROBLEX.AppValue[0]  = valor del motor derecho
    ROBLEX.AppValue[1]  = valor del motor izquierdo
    ROBLEX.AppValue[2]  = valor del led rojo    
    ROBLEX.AppValue[3]  = valor del led verde
    ROBLEX.AppValue[4]  = valor del led azul     
  */
    //mueve los motores segun el valor de la app
    Drive(RIGHT_PWM, -ROBLEX.AppValue[0].toInt());
    Drive(LEFT_PWM, -ROBLEX.AppValue[1].toInt());

    //cambia el color del led RGB segun el valor de la app
    ROBLEX.Rgb(ROBLEX.AppValue[2].toInt(), ROBLEX.AppValue[3].toInt(), ROBLEX.AppValue[4].toInt());
  }

  if (!SerialBT.connected(200)) {
    ROBLEX.ReadApp("0");
  }
}