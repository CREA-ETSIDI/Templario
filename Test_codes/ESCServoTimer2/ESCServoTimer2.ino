#include<ServoTimer2.h>

ServoTimer2 ESC; //Crear un objeto de clase servo


void setup()
{
  Serial.begin(9600);
 //Asignar un pin al ESC
 ESC.attach(7);
 
 //Activar el ESC
 ESC.write(2000); //1000 = 1ms
 Serial.println("beep bop madafaka");
 //Cambia el 1000 anterior por 2000 si
 //tu ESC se activa con un pulso de 2ms
 delay(10); //Esperar 5 segundos para hacer la activacion
 ESC.write(0);
 Serial.println("Se queda quieto y al loop");  
  
}


void loop()
{
  int vel=100;//2550 es 0V y 0 es a tope de puto power
  Serial.print("velocidad="); Serial.println(vel);
ESC.write(vel);
}
