/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\purpl                                            */
/*    Created:      Sun Oct 20 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller            
// Controller2          controller        
// frontRight           motor         16             
// frontLeft            motor         15              
// backRight            motor         17              
// backLeft             motor         11              
// ramp                 motor         20             
// rightClaw            motor         18              
// leftClaw             motor         13              
// ramp2                motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::competition Competition;

void auton(void) {

  //Unfold & pick up 4 long row of cubes
  leftClaw.rotateFor(1, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  rightClaw.rotateFor(1, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);
  leftClaw.rotateFor(4, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  rightClaw.rotateFor(4, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  frontRight.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //Move Backwards
  frontRight.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  //Turn around
  frontRight.rotateFor(2.5, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(2.5, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(-2.5, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(-2.5, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //Go backwards 
  frontRight.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(4, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //Pivot
  frontRight.rotateFor(0.8, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(0.8, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(-0.8, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(-0.8, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //Go towards goal zone
  frontRight.rotateFor(2, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backRight.rotateFor(2, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(2, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
  backLeft.rotateFor(2, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //Move ramp forwards
  ramp.rotateFor(1.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  ramp2.rotateFor(1.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //do things
  leftClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  rightClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  frontRight.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  backRight.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  backLeft.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);  

  vex::task::sleep(2000);

}

//Stacks automatically when partner button y is pressed
void stack(void) {

  Controller1.rumble("...");
  Controller2.rumble("...");

  //Move ramp forwards
  ramp.rotateFor(2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  ramp2.rotateFor(2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);

  vex::task::sleep(500);

  //do things
  leftClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  rightClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  frontRight.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  backRight.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  frontLeft.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  backLeft.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);

}


void opcontrol(void) {

  Brain.Battery.current();

  /*
    Maps from (-100) -> 100 to itself using the function
    ((100 * pow(4, ((abs(x)-50)/12.5)))/(pow(4, ((abs(x)-50)/12.5))+1)))* ((x >
    0) - (x < 0))

    Used to ease in/out joystick movement for more precise control.

    If the horizontal input is at 25%, it only has 5% of the power, reducing the
    amount that the robot will slowly veer off course from an imperfect control
    stick.

  */
  int sigmoid_map[255] = {
      -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100,
      -100, -100, -100, -100, -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,
      -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,  -99,
      -99,  -98,  -98,  -98,  -98,  -98,  -98,  -97,  -97,  -97,  -96,  -96,
      -96,  -95,  -95,  -94,  -94,  -93,  -92,  -92,  -91,  -90,  -89,  -88,
      -86,  -85,  -84,  -82,  -80,  -79,  -77,  -75,  -73,  -70,  -68,  -66,
      -63,  -61,  -58,  -55,  -52,  -50,  -47,  -44,  -41,  -39,  -36,  -34,
      -31,  -29,  -27,  -24,  -22,  -21,  -19,  -17,  -16,  -14,  -13,  -12,
      -10,  -9,   -8,   -8,   -7,   -6,   -5,   -5,   -4,   -4,   -3,   -3,
      -3,   -2,   -2,   -2,   -2,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    1,    1,    1,    1,    1,    1,    1,    2,    2,
      2,    2,    3,    3,    3,    4,    4,    5,    5,    6,    7,    8,
      8,    9,    10,   12,   13,   14,   16,   17,   19,   21,   22,   24,
      27,   29,   31,   34,   36,   39,   41,   44,   47,   50,   52,   55,
      58,   61,   63,   66,   68,   70,   73,   75,   77,   79,   80,   82,
      84,   85,   86,   88,   89,   90,   91,   92,   92,   93,   94,   94,
      95,   95,   96,   96,   96,   97,   97,   97,   98,   98,   98,   98,
      98,   98,   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
      99,   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,   100,
      100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
      100,  100,  100};
  int leftPower, rightPower;
  int moveSpeed, rampSpeed;

  moveSpeed = 100;
  rampSpeed = 25; 

for(;;) {

  //-------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------
  //-----------------------------Controller 1 Code---------------------------------
  //-------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------

  // Tank Control
  // leftPower = sigmoid_map[Controller1.Axis3.value() + 127];
  // rightPower = sigmoid_map[Controller1.Axis2.value() + 127];

  // Arcade control
  leftPower = sigmoid_map[Controller1.Axis3.value() + 127] +
              sigmoid_map[Controller1.Axis4.value() + 127];
  rightPower = sigmoid_map[Controller1.Axis3.value() + 127] -
               sigmoid_map[Controller1.Axis4.value() + 127];

  
  // Precision Control
  if (Controller1.ButtonL1.pressing()) {
    leftPower /= 2;
    rightPower /= 2;
    moveSpeed /= 2;
  } else {
    moveSpeed = 100;
  }


  //Right side movement
  if (rightPower != 0) {
    frontRight.spin(vex::directionType::fwd, rightPower, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, rightPower, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing()) {
    //Strafe left
    backRight.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    //Strafe right
    backRight.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()){
    //Move Straight Up
    frontRight.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()){
    //Move Straight Down
    frontRight.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonL1.pressing()) {

  } else {
    //Stop
    frontRight.stop(vex::brakeType::brake);
    backRight.stop(vex::brakeType::brake);
  }
        
        
  //Left side movement
  if (leftPower != 0) {
    frontLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing()) {
    //Strafe left
    frontLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    //Strafe right
    frontLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()){
    //Move Up
    frontLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()){
    //Move Down
    frontLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonL1.pressing()) {

  } else {
    //Stop
    frontLeft.stop(vex::brakeType::brake);
    backLeft.stop(vex::brakeType::brake);
  }

  if (Brain.timer(timeUnits::sec) == 30) {
    Controller1.rumble("...");
  } 

  //Do some sick donuts
  if (Controller1.ButtonB.pressing()) {
    frontLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }

  //-------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------
  //-----------------------------Controller 2 Code---------------------------------
  //-------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------

  if (Controller2.ButtonL1.pressing()) {
    rampSpeed /= 3;
  } else {
    rampSpeed = 25;
  }

  // Ramp movement
  if (Controller2.ButtonX.pressing() && ramp.position(degrees) >= 500) {
    Controller2.rumble(".");
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  } else if (Controller2.ButtonA.pressing() && ramp.position(degrees) <= -100) {
    Controller2.rumble(".");
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  } else if (Controller2.ButtonX.pressing()) {
    ramp.spin(vex::directionType::fwd, rampSpeed, vex::velocityUnits::pct);
    ramp2.spin(vex::directionType::fwd, rampSpeed, vex::velocityUnits::pct);
  } else if (Controller2.ButtonA.pressing()) {
    ramp.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::pct);
    ramp2.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::pct);
  } else {
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  }

  // Claw control
  if (Controller2.ButtonR1.pressing() && Controller2.ButtonL1.pressing()) {
    leftClaw.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  } else if (Controller2.ButtonR2.pressing() && Controller2.ButtonL1.pressing()) {
    leftClaw.spin(vex::directionType::rev, 75, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::rev, 75, vex::velocityUnits::pct);
  } else if (Controller2.ButtonR1.pressing()) {
    leftClaw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (Controller2.ButtonR2.pressing()) {
    leftClaw.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else {
    leftClaw.stop(vex::brakeType::hold);
    rightClaw.stop(vex::brakeType::hold);
  }


  //Runs stack function
  Controller2.ButtonY.pressed(stack); 

  vex::task::sleep(200);
}
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.autonomous(auton);
  Competition.drivercontrol(opcontrol);

  for(;;) {
    vex::task::sleep(100);
  }

}