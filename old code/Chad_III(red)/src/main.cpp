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
// frontRight           motor         5               
// frontLeft            motor         9               
// backRight            motor         18              
// backLeft             motor         11              
// ramp                 motor         20              
// rightClaw            motor         3               
// leftClaw             motor         15              
// arms                 motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void autonomous(void) {

  //Push Cube into Goal
  //Forwards
    frontRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Backwards
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Turn
    frontRight.rotateFor(0.8, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    backRight.rotateFor(0.8, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-0.8, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-0.8, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, true);

  //Unfolds Arms
  //Forwards
    frontRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Backwards
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Forwards
    frontRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Backwards
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  //Runs Claws
    leftClaw.rotateFor(2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    vex::task::sleep(1000);

}

void usercontrol(void) {

  Brain.Battery.current();

  /*
    Maps from (-100) -> 100 to itself using the function 
    ((100 * pow(4, ((abs(x)-50)/12.5)))/(pow(4, ((abs(x)-50)/12.5))+1)))* ((x > 0) - (x < 0))

    Used to ease in/out joystick movement for more precise control.
    
    If the horizontal input is at 25%, it only has 5% of the power, reducing the amount that
    the robot will slowly veer off course from an imperfect control stick.
    
  */
  int sigmoid_map[255] = {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -98, -98, -98, -98, -98, -98, -97, -97, -97, -96, -96, -96, -95, -95, -94, -94, -93, -92, -92, -91, -90, -89, -88, -86, -85, -84, -82, -80, -79, -77, -75, -73, -70, -68, -66, -63, -61, -58, -55, -52, -50, -47, -44, -41, -39, -36, -34, -31, -29, -27, -24, -22, -21, -19, -17, -16, -14, -13, -12, -10, -9, -8, -8, -7, -6, -5, -5, -4, -4, -3, -3, -3, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 7, 8, 8, 9, 10, 12, 13, 14, 16, 17, 19, 21, 22, 24, 27, 29, 31, 34, 36, 39, 41, 44, 47, 50, 52, 55, 58, 61, 63, 66, 68, 70, 73, 75, 77, 79, 80, 82, 84, 85, 86, 88, 89, 90, 91, 92, 92, 93, 94, 94, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
  int leftPower, rightPower;
 for(;;){
  //Tank Control
  leftPower = sigmoid_map[Controller1.Axis3.value() + 127];
  rightPower = sigmoid_map[Controller1.Axis2.value() + 127];
  
  //Percussion Control
  if (Controller1.ButtonL1.pressing()){
    leftPower /= 2;
    rightPower /= 2;
  }

  //Right side movement
  if (rightPower != 0) {
    frontRight.spin(vex::directionType::fwd, rightPower, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, rightPower, vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()){
    //Move Straight Up
    frontRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()){
    //Move Straight Down
    frontRight.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing() && Controller1.ButtonL1.pressing()) {
    //Turn Left Slowly
    frontRight.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing()) {
    //Turn Left
    frontRight.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing() && Controller1.ButtonL1.pressing()) {
    //Turn Right Slowly
    frontRight.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    //Turn Right
    frontRight.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    backRight.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  } else {
    //Stop
    frontRight.stop(vex::brakeType::brake);
    backRight.stop(vex::brakeType::brake);
  }
        
        
  //Left side movement
  if (leftPower != 0) {
    frontLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()){
    //Move Up
    frontLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()){\
    //Move Down
    frontLeft.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing() && Controller1.ButtonL1.pressing()) {
    //Turn Left Slowly
    frontLeft.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing()) {
    //Turn Left
    frontLeft.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing() && Controller1.ButtonL1.pressing()) {
    //Turn Right Slowly
    frontLeft.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    //Turn Right
    frontLeft.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  } else {
    //Stop
    frontLeft.stop(vex::brakeType::brake);
    backLeft.stop(vex::brakeType::brake);
  }

  //Ramp movement
  if (Controller1.ButtonX.pressing()) {
    ramp.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  } else if (Controller1.ButtonA.pressing()) {
    ramp.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  } else {
    ramp.stop(vex::brakeType::hold);
  }

  //Claw control
  if (Controller1.ButtonR1.pressing()) {
    leftClaw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);  
  } else if (Controller1.ButtonR2.pressing()) {
    leftClaw.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);  
  } else {
    leftClaw.stop(vex::brakeType::hold);
    rightClaw.stop(vex::brakeType::hold);
  }
        
  
  vex::task::sleep(20);
}
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  autonomous();
  usercontrol();

  for(;;) {
    vex::task::sleep(100);
  }
}