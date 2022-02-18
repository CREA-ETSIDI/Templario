#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>


typedef struct  {
int JoyIzq;
int JoyDer;
byte Botones ;   // estructura "JoYIzQButton JoyDerButton SW1 SW2  B1 B2 B3 B4"   
}InfoMando;

unsigned long UltimaConexion = 0;
int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;
char ppsBuf[16];

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
Serial.println(Mimando.Botones);
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
   }
   updateScreen();
   if(((millis()- UltimaConexion) > 3000) ){
  Mimando.JoyIzq = 0;
  Mimando.JoyDer = 0;
  Mimando.Botones= 0;

UltimaConexion = millis();

radio.begin();
    radio.setAutoAck(0);
 radio.setDataRate(RF24_250KBPS);
   radio.openReadingPipe(0,direccion);
   radio.startListening();
  
}
}
