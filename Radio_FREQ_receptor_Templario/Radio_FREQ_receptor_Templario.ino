#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>
#include <ServoTimer2.h>  // the servo library

#define pinPHA1 4
#define pinPHA2 5
#define pinPHB1 6
#define pinPHB2 7

ServoTimer2 rodillo;


typedef struct  {
int JoyIzq;
int JoyDer; 
bool boton1;
bool boton2;
}InfoMando;

unsigned long UltimaConexion = 0;
int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;
//char ppsBuf[16];

 unsigned long packetsRead = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;

 
const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
//const uint64_t pipe = 0xE8E8F0F0E1LL;
 byte direccion[5] ={'c','a','n','a','l'};
char data[16];
 InfoMando Mimando;

int motor1(int,int);
int motor2(int,int);
bool arma(int);



void updateScreen()
{  
  unsigned long now = millis();
  if ( now - lastScreenUpdate < 100 )
    return;
    
  // moving average over 1 second
  packetCountTotal -= packetCounts[packetCountIndex];
  packetCounts[packetCountIndex] = packetsRead;
  packetCountTotal += packetsRead;

  packetCountIndex = (packetCountIndex + 1) % 10; // cada segundo llena el bufer y hace ciclos de 1 seg
  packetsRead = 0;                  //hace media y calcula si se pierden paquetes o no 



  Serial.print(" lectura Joystick izq: ");
Serial.println(Mimando.JoyIzq);
Serial.print(" lectura Joystick der: ");
Serial.println(Mimando.JoyDer);
Serial.print(" lectura botones: ");
Serial.print(Mimando.boton1);
Serial.println(Mimando.boton2);
Serial.print(" paquetes: ");
Serial.println(packetCountTotal);
  //sprintf(ppsBuf, "PPS: %d", packetCountTotal);  //pps = paquetes por segundo
  
  lastScreenUpdate = millis();  
}


void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(0);
   radio.openReadingPipe(0,direccion);
   radio.startListening();

   memset( packetCounts, 0, sizeof(packetCounts) );
 
}
 
void loop(void)
{

  int velA;
  int velB;
  //Variables control
  int c1;
  int c2;
  int c3;
  



  
   if (radio.available())
   {
    radio.read(&Mimando, sizeof  Mimando);
       //radio.read(&data, sizeof data); 
//Serial.print(" lectura Joystick izq: ");
//Serial.println(Mimando.JoyIzq);
//Serial.print(" lectura Joystick der: ");
//Serial.println(Mimando.JoyDer);
//Serial.print(" lectura botones: ");
//Serial.println(Mimando.Botones);
 packetsRead++;
  UltimaConexion = millis();
//Serial.print(Mimando.boton1);
//Serial.println(Mimando.boton2);

 c1=motor1(Mimando.JoyIzq,Mimando.boton1);
      c2=motor2(Mimando.JoyDer,Mimando.boton1);
      c3=arma(Mimando.boton2);

  
   }
   updateScreen();
 
   
   if(((millis()- UltimaConexion) > 3000) ){
  Mimando.JoyIzq = 0;
  Mimando.JoyDer = 0;
  Mimando.boton1= 0;
  Mimando.boton2= 0;
UltimaConexion = millis();

radio.begin();
    radio.setAutoAck(0);
 radio.setDataRate(RF24_250KBPS);
   radio.openReadingPipe(0,direccion);
   radio.startListening();
  
}


}


int motor1(int a, int c){
  //motor 1
  if(a<180 && c==1 ){
    digitalWrite(pinPHA1,HIGH); 
    digitalWrite(pinPHA2,LOW);
  }
  else if(a<180 && c==0){
    analogWrite(pinPHA1,LOW); 
    digitalWrite(pinPHA2,HIGH);
  }
  else{
    analogWrite(pinPHA1,LOW); 
    digitalWrite(pinPHA2,LOW);
  }

  return a;
}

int motor2(int b,int c){
  //motor 2
  if(b<180 && c==1){
    digitalWrite(pinPHB1,HIGH); 
    digitalWrite(pinPHB2,LOW);
  }
  else if(b<180 && c==0){
  digitalWrite(pinPHB1,LOW); 
  digitalWrite(pinPHB2,HIGH);
  }
  else{
    analogWrite(pinPHB1,LOW); 
    digitalWrite(pinPHB2,LOW);
  }
  return b;
}
bool arma(int c){
  //1 encendido, 0 apagado
  rodillo.attach(3);
  if(c==0){
    rodillo.write(1200);
    return 0;
  }
  else{
    rodillo.write(0);
    return 1;
  }
}
