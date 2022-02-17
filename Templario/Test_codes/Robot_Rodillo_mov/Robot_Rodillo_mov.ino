#include <Servo.h>
int IN1=5;
int IN2=6;
int IN3=4;
int IN4=3;
// Declaramos la variable para controlar el servo
Servo servoMotor;
 
void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  pinMode (IN1,OUTPUT);
 pinMode (IN2,OUTPUT);
 pinMode (IN3,OUTPUT);
 pinMode (IN4,OUTPUT);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  servoMotor.write(0);
  delay(1000);
}
 
void loop() {

 adelante;
 digitalWrite(IN1,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN4,LOW);
  // Esperamos 1 segundo
  delay(1000);

}
void adelante(){
   servoMotor.write(50);
  Serial.println("adelante2");
}
