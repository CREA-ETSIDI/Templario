/*Code del Templario by CREA*/

#include <ServoTimer2.h>  // the servo library
#include <VirtualWire.h> //radio

uint8_t mess[VW_MAX_MESSAGE_LEN];
uint8_t messageLength = VW_MAX_MESSAGE_LEN;

//Deben ser PWM todos.
#define pinPHA1 5
#define pinPHA2 6
#define pinPHB1 8
#define pinPHB2 9

ServoTimer2 rodillo;


int motor1(int,int);
int motor2(int,int);
bool arma(int);

void setup() {
  //Declaracion de pines del puente H
  pinMode(pinPHA1,OUTPUT);
  pinMode(pinPHA2,OUTPUT);
  pinMode(pinPHB1,OUTPUT);
  pinMode(pinPHB2,OUTPUT);

  Serial.begin(9600);//Iniciamos el Serial
  Serial.println("Iniciando...");
  vw_setup(2000);
  vw_set_rx_pin(3);
  vw_rx_start();
  
}

void loop() {
  /*********lectura mensaje de radio**********/
  int boton= mess[5]-48;
  int gat1=(((mess[6]-32)*94)+ mess[7]-32)-40;
  int gat2=(((mess[8]-32)*94)+ mess[9]-32)-40;
  //Velocidades en pwm para los motores
  int velA;
  int velB;
  //Variables control
  int c1;
  int c2;
  int c3;
  vw_get_message(mess, &messageLength);

  if (vw_get_message(mess, &messageLength))  
    {
      //Serial.println(boton);
      c1=motor1(gat1,boton);
      c2=motor2(gat2,boton);
      c3=arma(boton);
      Serial.println(c1);
      Serial.println(c2);
      Serial.println(c3);
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
  rodillo.attach(11);
  if(c==0){
    rodillo.write(1200);
    return 0;
  }
  else{
    rodillo.write(0);
    return 1;
  }
}
