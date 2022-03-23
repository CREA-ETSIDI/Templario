#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>
 
#define puertoB1 5  //inversor
#define puertoB2 6  //Arma
#define gat1 A0 //Motor1
#define gat2 A1 //Motor2

typedef struct  {
int JoyIzq;
int JoyDer;  
bool boton1;
bool boton2;
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

pinMode(gat1,INPUT);
pinMode(gat2,INPUT);
pinMode(puertoB1,INPUT);
pinMode(puertoB2,INPUT);
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

Mimando.boton1  =  digitalRead(puertoB1);
Mimando.boton2  =  digitalRead(puertoB2);
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
