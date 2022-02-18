#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>
 
#define SW 7

typedef struct  {
int JoyIzq;
int JoyDer;
byte Botones ;   // estructura "JoYIzQButton JoyDerButton SW1 SW2  B1 B2 B3 B4"   
}InfoMando;


const int pinCE = 9;
const int pinCSN = 10;

RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
// const uint64_t pipe = 0xE8E8F0F0E1LL;
byte direccion[5] ={'c','a','n','a','l'};
 
char data[16]="Hola Mundo" ;
InfoMando Mimando;

 
void setup(void)
{
pinMode(SW,INPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
   radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(0);
   radio.openWritingPipe(direccion);

 // el modo de funciona
   
}
 
void loop(void)
{
Mimando.JoyIzq = analogRead(A0);
Mimando.JoyDer = analogRead(A1);
Mimando.Botones =  digitalRead(SW);
  
  radio.write(&Mimando, sizeof Mimando);
   //radio.write(&data, sizeof data);
   
}

/*   joys1, joys2    -> 1 lecturas depotencometros cada 1  -> 2 int 8 bits*2 = 2 bytes 
 *   2 potenciometros ->2 lecturas -->  2 int       2 bytes 
 * 
 *   2 switches  2- bits   
 *   4 botones  --> 4 bits
 *   botones de joystic -> 2 bits
 */
