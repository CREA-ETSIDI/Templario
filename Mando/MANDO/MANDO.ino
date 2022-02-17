#include <VirtualWire.h>

#define puertoB1 5  //inversor
#define puertoB2 6  //Arma
#define gat1 A0 //Motor1
#define gat2 A1 //Motor2

char senal[]= "sand00SSSS";

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(9);
  
  pinMode(puertoB1,INPUT);
  pinMode(puertoB2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  //digitalWrite(led,digitalRead(int1)); 
  int pote1=analogRead(gat1);
  int pote2=analogRead(gat2);

  bool boton1=digitalRead(puertoB1);
  bool boton2=digitalRead(puertoB2);
  
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

  send(senal);
  
  senal[6]=(map(pote1,0,1023,0,510)/94)+32;
  senal[7]=(map(pote1,0,1023,0,510)%94)+32;

  senal[8]=(map(pote2,0,1023,0,550)/94)+32;
  senal[9]=(map(pote2,0,1023,0,550)%94)+32;
  
 
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
}
