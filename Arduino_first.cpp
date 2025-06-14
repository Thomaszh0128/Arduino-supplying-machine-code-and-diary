#include <Stepper.h>
//requirement for this code file : (1) 28BYJ-48 Step motor X 2 (2) 3D printed rail for 28BYJ-48 Step motor X 2 (3) three-pin-button X 2 (4) ULN2003 board X2 (For step motor) (5) Arduino Uno X 1 (6) Bread Board (7) dupont lines

//We use 28BYJ-48 Step motor here, we need 4 of them and we use button to control them
//We need a 3D printed rail for our step motor
const int stepsPerRevolution = 2048; 
//our two motor. We use motors to push items.
Stepper myStepper3(stepsPerRevolution, 2, 4, 3, 5); // Notice!! it is 2, 4, 3, 5
Stepper myStepper4(stepsPerRevolution, A2, A4, A3, A5); // Notice!! it is A2, A4, A3, A5
void setup() {
  myStepper4.setSpeed(15);
  myStepper3.setSpeed(15);
}
//I tested the speed, we set the speed to 15rpm, but maybe it can be set higher.
//The number 10787 here is correspond to the length of rail, which in my case is 22 cm, so it may need to be changed.
int i = 0;
void loop() {
  int state4 = digitalRead(A1); 
  if (state4 == LOW) {
      for(int i = 0; i< 10788; i++){
        myStepper4.step(-1);
      }
      for(int i = 0; i< 10788; i++){
        myStepper4.step(1);
      }
  }
  int state3 = digitalRead(A0); 
  if (state3 == LOW) {
    for(int i = 0; i< 10788; i++){
        myStepper3.step(1);
      }
    for(int i = 0; i< 10788; i++){
        myStepper3.step(-1);
      }
  }
}
//The motor will go forth and back, work as intented.
