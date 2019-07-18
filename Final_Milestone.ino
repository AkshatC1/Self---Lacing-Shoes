#include <Servo.h>


Servo myservo1;
Servo myservo2;
int pressurePin1 = A0;
int pressurePin2 = A1;
int force1;
int force2;
int forcePrevious;
const int GREENbutton = 4;
int GREENbuttonState = 0;
int count = 0;
int stateMachine = 0;


void setup() {

  Serial.begin(9600);
  myservo1.attach(10);
  myservo2.attach(9);
  myservo1.write(90);
  myservo2.write(90);
  pinMode(GREENbutton, INPUT);
  
}

void loop() {

  GREENbuttonState = digitalRead(GREENbutton);
  force1 = analogRead(pressurePin1);
  force2 = analogRead(pressurePin2);
    

  if ((force1 > 500) && (stateMachine == 1)) {
    myservo1.attach(10);
    myservo2.attach(9);
    myservo1.write(180);
    myservo2.write(0);
    Serial.println(force1);
    Serial.println(stateMachine);
    stateMachine = 2;
  }
  else if (stateMachine == 0)
  {
    myservo1.detach();
    myservo2.detach();
    Serial.println("no force");
    stateMachine = 1;
  }

  while ((force2 > 100) && (stateMachine == 2)) {
    myservo1.detach();
    myservo2.detach();
    stateMachine = 3;
    Serial.println(stateMachine);
  }
  
 while ((GREENbuttonState == HIGH) && (stateMachine == 3)) {
    myservo1.attach(10);
    myservo2.attach(9);
    myservo1.write(0);
    myservo2.write(180);
    stateMachine = 4;
    while ((GREENbuttonState == HIGH) && (stateMachine == 4)) {
      delay(2500);
      myservo1.detach();
      myservo2.detach();
      Serial.println(stateMachine);
      stateMachine = 0;
    }
  }
  
  if (forcePrevious - force1 >= 15) {
  count ++; 
  Serial.print("Steps : ");
  Serial.println(count/2);
}

forcePrevious = force1;

}
