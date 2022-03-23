#include <VirtualWire.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>
 

#define puertoB1 5  //inversor
#define puertoB2 6  //Arma
#define gat1 A0 //Motor1
#define gat2 A1 //Motor2


//NEW RADIO
typedef struct  {
int JoyIzq;
int JoyDer;
bool boton1;
bool boton2; 
}InfoMando;

const int pinCE = 9;
const int pinCSN = 10;
byte direccion[5] ={'c','a','n','a','l'};
 InfoMando Mimando;
RF24 radio(pinCE, pinCSN);


// OLD RADIO

//char senal[]= "sand00SSSS";  //señal por defecto. el tamaño de la señal el mismo que ésta, y el código de indetificación es <sand>

void setup() {
//NEW RADIO
Serial.begin(115200);
  radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(0);
   radio.openWritingPipe(direccion);



/*
//OLD RADIO  
  Serial.begin(9600);  //inicio de la comunicación serie a 9600 baudios
  vw_setup(2000);  //inicio de la velocidad de trnasmisión del módulo de radio, definido por diseño por el fabricante
  vw_set_tx_pin(9);   //inicias el pin de transmisión de datos
  
  pinMode(puertoB1,INPUT);
  pinMode(puertoB2,INPUT);
  pinMode(gat1,INPUT);
  pinMode(gat2,INPUT);
*/
  
}

void loop() {
//NEW RADIO
  //lectura de los gatillos posteriores
  Mimando.JoyIzq=analogRead(gat1);    
  Mimando.JoyDer=analogRead(gat2);
  
  //lectura de los botones delanteros
  Mimando.boton1=digitalRead(puertoB1);
  Mimando.boton2=digitalRead(puertoB2);

radio.write(&Mimando, sizeof Mimando);


Serial.print(Mimando.boton1);
Serial.println(Mimando.boton2);
//OLD RADIO
/* 
  //digitalWrite(led,digitalRead(int1)); 
  //lectura de los gatillos posteriores
  int pote1=analogRead(gat1);    
  int pote2=analogRead(gat2);




  
//lectura de los botones delanteros
  bool boton1=digitalRead(puertoB1);
  bool boton2=digitalRead(puertoB2);

  // añades a la señal los valores de lectura de los botones 
  if(digitalRead(boton1)){  
    senal[4]='1';
  }else{
    senal[4]='0';
  }
  if(digitalRead(boton2)){
    senal[5]='1';
  }else{
    senal[5]='0';
  }
//envías la señal
  send(senal); // se enviar un primer ciclo sin la lectura de los motores debido para garantizar un arranque más seguro mendiante un retardo
  //ajuste de los potes a las señales requeridas para los motores
  senal[6]=(map(pote1,0,1023,0,510)/94)+32;
  senal[7]=(map(pote1,0,1023,0,510)%94)+32;

  senal[8]=(map(pote2,0,1023,0,550)/94)+32;
  senal[9]=(map(pote2,0,1023,0,550)%94)+32;
  
 // imprimir por pantalla los valores de los potes, solo función debuggin
  Serial.print(" gat1: ");
  Serial.print(pote1);
  Serial.print(" gat2: ");
  Serial.print(pote2);
  Serial.print(" Boton1: ");
  Serial.print(boton1);
   Serial.print(" Boton2: ");
  Serial.println(boton2);
  delay(1);
}


//Funcion para enviar el mensaje
void send (char *message)   
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo
  
  //Serial.println(message); //Muestra el mensaje por Serial
*/
}
