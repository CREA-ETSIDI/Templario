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

int motorA(){
  //da el valor del motor A
  return (mess[6]-32)*94+(mess[7]-32);
}

int motorB(){
  //da el valor del motor B
  return (mess[8]-32)*94+(mess[9]-32);
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
