/* Arduino biartez, stepperra norantza batera edo bestera mugitu.
 */
 
// Motorraren libraria
#include <Stepper.h>
 
// Stepperraren pausu totalak zehaztu
#define STEPS 32
 
// Stepperraren kontrol pinak zehaztu.
#define IN1  13
#define IN2  12
#define IN3  11
#define IN4  10
 
// Stepper libraria 
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
 
// Joystick shielda arudino plakan jarri.
#define joystick  A0
 
void setup()
{
  pinMode(9, OUTPUT);
   pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    Serial.begin(9600);
  
}
 
void loop()
{
  // joystick-aren balorea irakurri
  int val = analogRead(joystick);
 
  // joystick-a erdian aurkitzen bada ===> Motorra geratu (LED gorria pzituta)
  if(  (val > 485) && (val < 535) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(9, LOW);
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    Serial.println("Geldirik");
  }
 
  else
  {
    // balore haundiagoa baldin bada, motorra martxan jarri (LED berdea)
    while (val >= 535)
    {
      // Mapeoa 5 eta 500 rpm bitartean
      int speed_ = map(val, 535, 1023, 0, 500);
      // Motorraren abiadura
      stepper.setSpeed(speed_);
 
      // Motorra mugitu (Pausu 1)
      stepper.step(1);
 
      val = analogRead(joystick);

      digitalWrite(9, HIGH);
       digitalWrite(2,LOW);
       digitalWrite(3,LOW);
       Serial.println("Ezkerreta");
       
      
    }
 
    // Motorra beste norantzan moitu (led Horia)
    while (val <= 485)
    {
      // Mapeoa 5 eta 500 rpm bitartean
      int speed_ = map(val, 485, 0, 5, 500);
      // Motorraren abiadura
      stepper.setSpeed(speed_);
 
      // Motorra mugitu (Pausu 1)
      stepper.step(-1);
 
      val = analogRead(joystick);

      digitalWrite(9, LOW);
       digitalWrite(2,HIGH);
       digitalWrite(3,LOW);
       Serial.println("Eskubita");
    }
  
    
  }
 
}



 
