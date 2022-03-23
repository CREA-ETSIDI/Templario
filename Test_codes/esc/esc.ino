#include<Servo.h>

Servo ESC; //Crear un objeto de clase servo


void setup()
{
 //Asignar un pin al ESC
 ESC.attach(11);
 
 //Activar el ESC
 ESC.write(0); //1000 = 1ms
 //Cambia el 1000 anterior por 2000 si
 //tu ESC se activa con un pulso de 2ms
 delay(5000); //Esperar 5 segundos para hacer la activacion
  
 //Iniciar puerto serial
 //erial.begin(9600);
// Serial.setTimeout(10);
  
  
}


void loop()
{
ESC.write(50);
}
