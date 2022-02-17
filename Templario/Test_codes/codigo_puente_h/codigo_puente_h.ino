/******Para usar el módulo bluetooth******/

//#include <SoftwareSerial.h>
//SoftwareSerial BT1(3, 11); // TX | RX

//Pines del punete H,A->motor 1, B->motor2

#include <ServoTimer2.h>  // the servo library
#include <VirtualWire.h> //radio

//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
uint8_t mess[VW_MAX_MESSAGE_LEN];
uint8_t messageLength = VW_MAX_MESSAGE_LEN;

//Deben ser PWM todos.
#define pinPHA1 5
#define pinPHA2 6
#define pinPHB1 9
#define pinPHB2 10

//#define quietoMin 80 //valor mínimo en el que el motor no se enciende
//#define quietoMax 120 //valor máximo en el que el motor no se enciende

ServoTimer2 rodillo;
//int state=0;
void setup() {
  //Declaracion de pines del puente H
  pinMode(pinPHA1,OUTPUT);
  pinMode(pinPHA2,OUTPUT);
  pinMode(pinPHB1,OUTPUT);
  pinMode(pinPHB2,OUTPUT);

  //Rodillo arma
  //rodillo.attach(13);//hay problemas con la comunicación con esta linea de código
  //rodillo.write(0);
  

  //Módulo BT
  //BT1.begin(9600);
  
  //Comunicación
  Serial.begin(9600);//Iniciamos el Serial
  Serial.println("Iniciando...");
  vw_setup(2000);
  vw_set_rx_pin(3);
  vw_rx_start();
  
  /*if(!verificar()){
    Serial.println("Error");
  }
  else{
    Serial.println("Correcto");
    //aqui va lo que querais hacer con las señales
  }*/
}

void loop() {
  /*********lectura mensaje de radio**********/
  int boton= mess[5]-48;
  int gat1=(((mess[6]-32)*94)+ mess[7]-32)-40;
  int gat2=(((mess[8]-32)*94)+ mess[9]-32)-40;
  //Modo de funcionamiento
  int modoA=1;
  int modoB=1;
  //Velocidades en pwm para los motores
  int velA;
  int velB;

  vw_get_message(mess, &messageLength);
  //Serial.println(*mess);
  if (vw_get_message(mess, &messageLength))  
    {
      /*Serial.print("Mensaje: ");
      for ( int i = 0; i < messageLength; i++)
      {
          Serial.print((char)mess[i]);
      }*/
      
      //Serial.println("");    
      //Serial.println(boton); 
      Serial.println(200-gat1); //0 en 203
      if(boton==1)
        velA=Serial.read();
      else
        velA=0;
      //Serial.println(200-gat2); //0 en 173
      /*********Mover el rodillo***********/
 
       //rodillo.write(1000);
      /********CONTROL RUEDAS*********/
      analogWrite(pinPHA1,velA); 
      digitalWrite(pinPHA2,LOW);
      /*switch(modoA){
        case 1://motor 1 hacia alante
           
        break;
    
        case 2:
          digitalWrite(pinPHA1,LOW); 
          analogWrite(pinPHA2,velA); 
        break;
    
        case 0:
          digitalWrite(pinPHB1,LOW); 
          digitalWrite(pinPHB2,LOW);
        default:
          digitalWrite(pinPHA1,LOW); 
          digitalWrite(pinPHA2,LOW); 
      }
    
    switch(modoB){
      case 1://motor 2 hacia alante
        analogWrite(pinPHB1,velB); 
        digitalWrite(pinPHB2,LOW); 
      break;
    
      case 2:
        digitalWrite(pinPHB1,LOW); 
        analogWrite(pinPHB2,velB); 
      break;
    
      case 0:
        digitalWrite(pinPHB1,LOW); 
        digitalWrite(pinPHB2,LOW);
      default:
        digitalWrite(pinPHB1,LOW); 
        digitalWrite(pinPHB2,LOW);
      }*/
  }

  //ModuloBT
  /*if (BT1.available())
           Serial.write(BT1.read());
       
  if (Serial.available())
    {  String S = GetLine();
       BT1.print(S);
       Serial.println("---> " + S);
       state = Serial.read();//si el modulo a manda dato, guardarlo en estado.
        if (state==1)
        {
          modoA=1;
          modoB=1;
        }
        else if (state==0)
        {
          modoA=0;
          modoB=0;
        }
    }
  */

}
/********FUNCION SALTO LINEA BT***********/
/*String GetLine()
   {   String S = "" ;
       if (Serial.available())
          {    char c = Serial.read(); ;
                while ( c != '\n')            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial.read();
                  }
                return( S + '\n') ;
          }
   }*/
bool verificar() {
  //Esta funcion compara el mensaje con la firma.
  //Si son iguales, devuelve 1. Si no, devuelve 0.
  char* firma = "sand";
  
  for(int i = 0; i<4; i++)
  {
    Serial.println(mess[i]);
    if(mess[i] != firma[i])
    { 
      return 0;
    }
  }
  return 1;
}

bool inversor(){
  //1 invertido, 0 normal
  if(mess[4]=='0')
    return 0;
  if(mess[4]=='1')
    return 1;
}

bool arma(){
  //1 encendido, 0 apagado
  if(mess[5]=='0')
    return 0;
  if(mess[5]=='1')
    return 1;
}

int motor1(){
  //da el valor del motor 1
  return (mess[6]-32)*94+(mess[7]-32);
}

int motor2(){
  //da el valor del motor 2
  return (mess[8]-32)*94+(mess[9]-32);
}
