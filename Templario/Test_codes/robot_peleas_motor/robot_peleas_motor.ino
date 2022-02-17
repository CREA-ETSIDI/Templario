
byte PWM_PIN = 3;
byte PWM_PIN2 = 4;
int motor1;
int motor2;
 
int pwm_value;

int pwm_value2;
 
void setup() {
  pinMode(PWM_PIN, INPUT);
  pinMode(PWM_PIN2, INPUT);
  Serial.begin(115200);
}
 
void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  pwm_value2 = pulseIn(PWM_PIN2, HIGH);
  
  motor1= map(pwm_value,0,2200,0,255);
  motor2= map(pwm_value2,0,2200,0,255);
  analogWrite(5, motor1);
  analogWrite(6, motor2);
  digitalWrite(7,0);
  digitalWrite(2,0);

Serial.print(motor1);
  Serial.print("    ");
  Serial.println(motor2);





  
}
