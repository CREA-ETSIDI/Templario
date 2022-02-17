#include <ServoTimer2.h>
#include <VirtualWire.h>


//Pines del punete H,A->motor 1, B->motor2
//Deben ser PWM todos.
#define pinPHA1 5
#define pinPHA2 6
#define pinPHB1 9
#define pinPHB2 10

#define quietoMin 80 //valor mínimo en el que el motor no se enciende
#define quietoMax 120 //valor máximo en el que el motor no se enciende

//Comunicación con el mando
//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
uint8_t mess[VW_MAX_MESSAGE_LEN];
uint8_t messageLength = VW_MAX_MESSAGE_LEN;

//Arma 
ServoTimer2 rodillo;

void setup() {
  
  //Declaracion de pines del puente H
  pinMode(pinPHA1,OUTPUT);
  pinMode(pinPHA2,OUTPUT);
  pinMode(pinPHB1,OUTPUT);
  pinMode(pinPHB2,OUTPUT);
  
  Serial.begin(2000000);//Iniciamos el Serial
  Serial.println("Iniciando...");

 //Rodillo
 rodillo.attach(7);
 //Configuracion del ESC
 rodillo.write(2000); //2000 = 2ms
 delay(1000);
 Serial.println("beep bop madafaka");
 //Cambia el 1000 anterior por 2000 si
 //tu ESC se activa con un pulso de 2ms
 rodillo.write(0);
 Serial.println("ESC configurado");  
  
  //movidas de radiofrecuencias
  vw_setup(2000);
  vw_set_rx_pin(9);
  vw_rx_start();

}

void loop() {

  enum {ALANTE=1,ATRAS=2,QUIETO=0};
 //Modo de funcionamiento de los motores
  int modoA=ALANTE;
  int modoB=ALANTE;
  
  //Velocidades en pwm para los motores
  int velA=150; //valor pwm 0-255
  int velB=150;

  //int sigMandoA=motorA();
  //Serial.println(sigMandoA);

  //Medidas que llegan del módulo de radio
  int valoPoteA=90;
  int valPoteB=90;
  
  //Estado del arma
  bool arma=0;
  //arma=arma();
  
  //Leo el mensaje que llega por radio
  vw_get_message(mess, &messageLength);
  //Serial.println(*mess);
if (vw_get_message(mess, &messageLength))  
    {
  Serial.print("Mensaje: ");
  for (int i = 0; i < messageLength; i++)
  {
      Serial.print((char)mess[i]);
  }
  Serial.println("");     
    }
 
  if(arma){
    rodillo.write(100); //2250-0
  }else{
    rodillo.write(2250);
  }
  
  
  switch(modoA){
    case 1://motor 1 hacia alante
      analogWrite(pinPHA1,velA); 
      digitalWrite(pinPHA2,LOW);  
    break;

    case 2:
      digitalWrite(pinPHA1,LOW); 
      analogWrite(pinPHA2,velA); 
    break;

    case 0:
    default:
      digitalWrite(pinPHA1,LOW); 
      digitalWrite(pinPHA2,LOW); 
  }

  switch(modoB){
    case 1://motor 1 hacia alante
      analogWrite(pinPHB1,velB); 
      digitalWrite(pinPHB2,LOW); 
    break;

    case 2:
      digitalWrite(pinPHB1,LOW); 
      analogWrite(pinPHB2,velB); 
    break;

    case 0:
    default:
      digitalWrite(pinPHB1,LOW); 
      digitalWrite(pinPHB2,LOW); 
  }
}
