#include <VirtualWire.h>

//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
uint8_t mess[VW_MAX_MESSAGE_LEN];
uint8_t messageLength = VW_MAX_MESSAGE_LEN;
 
void setup()
{
  
  Serial.begin(9600);//Iniciamos el Serial
  Serial.println("Iniciando...");
  
  vw_setup(2000);
  vw_set_rx_pin(3);
  vw_rx_start();

  //mess="sand01  %p";

  /*if(!verificar()){
    Serial.println("Error");
  }
  else{
    Serial.println("Correcto");
    //aqui va lo que querais hacer con las señales
  }*/
}

void loop()
{


 int boton= mess[5]-48;
int gat1=(((mess[6]-32)*94)+ mess[7]-32)-40;
int gat2=(((mess[8]-32)*94)+ mess[9]-32)-40;


  vw_get_message(mess, &messageLength);
 //Serial.println(*mess);
  if (vw_get_message(mess, &messageLength))  
    {
  int i;

/*  Serial.print("Mensaje: ");
  for (i = 0; i < messageLength; i++)
  {
      Serial.print((char)mess[i]);
  }
  */
  Serial.println("");    
Serial.println(boton); 
Serial.println(200-gat1); //0 en 203
Serial.println(200-gat2); //0 en 173
 
   
/*boton = mess[5]-48;
Serial.println(boton);
gat1 = mess[7]+32 +(mess[6]+32)*94;
Serial.println(gat1);
gat1 = mess[9]+32 +(mess[8]+32)*94;
Serial.println(gat2);*/

  
    }
}
 
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
