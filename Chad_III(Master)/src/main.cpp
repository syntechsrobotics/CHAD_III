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
// frontRight           motor         16
// frontLeft            motor         15
// backRight            motor         17
// backLeft             motor         11
// ramp                 motor         20
// ramp2                motor         12
// rightClaw            motor         18
// leftClaw             motor         13
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "ButtonClass.h"
#include "robot-config.h"
#include "vex.h"
using namespace vex;

vex::competition Competition;

// Defines All Variables
#pragma region "Definitions"

// auto selection variables
int autoNumber = 0;

// defining driving speed variables
int leftPower = 0;
int rightPower = 0;
int moveSpeed = 100;
bool arcadeDrive = true;

// defining ramp and intake movment speed
int rampSpeed = 50;
int intakeSpeed = 100;
bool stacking = false;
int grabbySpeed = 50;

// defining strafing variables
int frontStrafePower = 100;
int backStrafePower = 100;
int gyroRotation = 0;
int preGyroRotation = 0;
int gyroCounter = 0;

// Defining fish variables
int fishX = 50;
int fishY = 150;
int fishSize = 20;
color waterBlue = vex::color(0, 9, 153);
color landGreen = vex::color(4, 149, 28);
color fishGold = vex::color(255, 217, 29);

std::string pongQuestionMark = "No";

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

#pragma endregion

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {

/*
  lcdButton onePoint(10, 10, 80, 50, "One Point", yellow);
  lcdButton farRed(100, 10, 80, 50, "Far Red", red);
  lcdButton farBlue(190, 10, 80, 50, "Far Blue", blue);

#pragma region "buttons"
  onePoint.draw();
  farRed.draw();
  farBlue.draw();

  if (Brain.Screen.pressing()) {
    if (onePoint.pressing()) {
      autoNumber = 1;
      Brain.Screen.clearScreen();
    } else if (farRed.pressing()) {
      autoNumber = 2;
      Brain.Screen.clearScreen();
    } else if (farBlue.pressing()) {
      autoNumber = 3;
      Brain.Screen.clearScreen();
    }
  }
  */

#pragma endregion

}

// Autonomous Section of Match
void auton(void) {

  // Run One Point
  if (autoNumber == 1) {

    // Unfold
    leftClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, true);

    vex::task::sleep(500);

    frontRight.rotateFor(1, vex::rotationUnits::rev, 40,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    frontLeft.rotateFor(1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    backLeft.rotateFor(1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       true);

    frontRight.rotateFor(-1, vex::rotationUnits::rev, 75,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-1, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-1, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct,
                       true);
    vex::task::sleep(500);
    vex::task::sleep(2000);

  } else if (autoNumber == 2) {
    //Run Far Right
    // Unfold
    leftClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, true);

    // //pick up 4 long row of cubes
    // while (rangeSensor1.distance(distanceUnits::in) < 3 0) {
    //   leftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
    //   rightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
    //   frontRight.spin(directionType::fwd, 50, velocityUnits::pct);
    //   backRight.spin(directionType::fwd, 50, velocityUnits::pct);
    //   frontLeft.spin(directionType::fwd, 50, velocityUnits::pct);
    //   backRight.spin(directionType::fwd, 50, velocityUnits::pct);
    // }
    //   leftClaw.stop(brakeType::coast);
    //   rightClaw.stop(brakeType::coast);
    //   frontRight.stop(brakeType::brake);
    //   backRight.stop(brakeType::brake);
    //   frontLeft.stop(brakeType::brake);
    //   backLeft.stop(brakeType::brake);

    leftClaw.rotateFor(10, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(10, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, false);

    vex::task::sleep(100);

    frontRight.rotateFor(4, vex::rotationUnits::rev, 40,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    frontLeft.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    backLeft.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(500);

    frontRight.rotateFor(-1, vex::rotationUnits::rev, 40,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-1, vex::rotationUnits::rev, 40,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-1, vex::rotationUnits::rev, 40,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       true);

    // Pivot
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 50,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                        false);
    backLeft.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(500);

    // Go towards goal zone
    frontRight.rotateFor(2.5, vex::rotationUnits::rev, 75,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(2.5, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2.5, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(2.5, vex::rotationUnits::rev, 75,
                       vex::velocityUnits::pct, true);

    vex::task::sleep(500);

    // Move ramp forwards
    ramp.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                   false);
    ramp2.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                    true);
    ramp.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                   false);
    ramp2.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                    true);

    frontRight.rotateFor(0.5, vex::rotationUnits::rev, 50,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(0.5, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(0.5, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(0.5, vex::rotationUnits::rev, 50,
                       vex::velocityUnits::pct, true);
    vex::task::sleep(500);

    // do things
    leftClaw.rotateFor(-2, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-2, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, false);
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 80,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 80,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 80,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(2000);

  } else if (autoNumber == 3) {
    //Run far left
    // Unfold
    leftClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-1, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, true);

    // //pick up 4 long row of cubes
    // while (rangeSensor1.distance(distanceUnits::in) < 3 0) {
    //   leftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
    //   rightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
    //   frontRight.spin(directionType::fwd, 50, velocityUnits::pct);
    //   backRight.spin(directionType::fwd, 50, velocityUnits::pct);
    //   frontLeft.spin(directionType::fwd, 50, velocityUnits::pct);
    //   backRight.spin(directionType::fwd, 50, velocityUnits::pct);
    // }
    //   leftClaw.stop(brakeType::coast);
    //   rightClaw.stop(brakeType::coast);
    //   frontRight.stop(brakeType::brake);
    //   backRight.stop(brakeType::brake);
    //   frontLeft.stop(brakeType::brake);
    //   backLeft.stop(brakeType::brake);

    leftClaw.rotateFor(10, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(10, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, false);
    vex::task::sleep(100);
    frontRight.rotateFor(4, vex::rotationUnits::rev, 40,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    frontLeft.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                        false);
    backLeft.rotateFor(4, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(500);

    frontRight.rotateFor(-1, vex::rotationUnits::rev, 40,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-1, vex::rotationUnits::rev, 40,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-1, vex::rotationUnits::rev, 40,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       true);

    // Pivot
    frontRight.rotateFor(2, vex::rotationUnits::rev, 50,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                        false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(500);

    // Go towards goal zone
    frontRight.rotateFor(2.5, vex::rotationUnits::rev, 75,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(2.5, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(2.5, vex::rotationUnits::rev, 75,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(2.5, vex::rotationUnits::rev, 75,
                       vex::velocityUnits::pct, true);

    vex::task::sleep(500);

    // Move ramp forwards
    ramp.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                   false);
    ramp2.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                    true);
    ramp.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                   false);
    ramp2.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                    true);

    frontRight.rotateFor(0.5, vex::rotationUnits::rev, 50,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(0.5, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(0.5, vex::rotationUnits::rev, 50,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(0.5, vex::rotationUnits::rev, 50,
                       vex::velocityUnits::pct, true);
    vex::task::sleep(500);

    // do things
    leftClaw.rotateFor(-2, vex::rotationUnits::rev, 100,
                       vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-2, vex::rotationUnits::rev, 100,
                        vex::velocityUnits::pct, false);
    frontRight.rotateFor(-2, vex::rotationUnits::rev, 80,
                         vex::velocityUnits::pct, false);
    backRight.rotateFor(-2, vex::rotationUnits::rev, 80,
                        vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-2, vex::rotationUnits::rev, 80,
                        vex::velocityUnits::pct, false);
    backLeft.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                       true);

    vex::task::sleep(2000);
  }
}

// Stacks automatically when button y is pressed
void stack(void) {

  // Move ramp forwards
  ramp.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                 false);
  ramp2.rotateFor(1, vex::rotationUnits::rev, 60, vex::velocityUnits::pct,
                  true);
  ramp.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                 false);
  ramp2.rotateFor(0.5, vex::rotationUnits::rev, 25, vex::velocityUnits::pct,
                  true);

  frontRight.rotateFor(0.5, vex::rotationUnits::rev, 50,
                       vex::velocityUnits::pct, false);
  backRight.rotateFor(0.5, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                      false);
  frontLeft.rotateFor(0.5, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                      false);
  backLeft.rotateFor(0.5, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                     true);

  vex::task::sleep(500);

  // do things
  leftClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct,
                     false);
  rightClaw.rotateFor(-2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct,
                      false);
  frontRight.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                       false);
  backRight.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                      false);
  frontLeft.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                      false);
  backLeft.rotateFor(-2, vex::rotationUnits::rev, 80, vex::velocityUnits::pct,
                     true);

  vex::task::sleep(500);

  stacking = false;
}

// Controls wheel movements for driver control section
void driveMovement(void) {

  if (arcadeDrive == true) {
    // Arcade control
    leftPower = sigmoid_map[Controller1.Axis3.value() + 127] +
                sigmoid_map[Controller1.Axis4.value() + 127];
    rightPower = sigmoid_map[Controller1.Axis3.value() + 127] -
                 sigmoid_map[Controller1.Axis4.value() + 127];
  } else {
    // Tank Control
    leftPower = sigmoid_map[Controller1.Axis3.value() + 127];
    rightPower = sigmoid_map[Controller1.Axis2.value() + 127];
  }

  // Precision Control
  if (Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()) {
    leftPower /= 4;
    rightPower /= 4;
    moveSpeed = 10;
    rampSpeed = 10;
    grabbySpeed = 5;
    backStrafePower = 25;
    frontStrafePower = 25;
  } else if (Controller1.ButtonL1.pressing()) {
    leftPower /= 2;
    rightPower /= 2;
    moveSpeed = 25;
    rampSpeed = 25;
    grabbySpeed = 10;
    backStrafePower = 50;
    frontStrafePower = 50;
  } else {
    intakeSpeed = 100;
    moveSpeed = 100;
    rampSpeed = 50;
    grabbySpeed = 50;
    backStrafePower = 100;
    frontStrafePower = 100;
  }

  //prevents overheating
  if (rightClaw.temperature(percentUnits::pct) >= 75 ||
      leftClaw.temperature(percentUnits::pct) >= 75) {
    intakeSpeed = 50;
  }






  // Right side movement
  if (Controller1.Axis4.value() >= 10 && Controller1.Axis4.value() <= -10){
    //turn
    frontRight.spin(vex::directionType::fwd, rightPower,
                    vex::velocityUnits::pct);
  } else if (rightPower != 0) {
    //drive
    frontRight.spin(vex::directionType::fwd, rightPower,
                    vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, rightPower,
                   vex::velocityUnits::pct);
  } else if (Controller1.ButtonLeft.pressing()) {
    // Strafe left
    backRight.spin(vex::directionType::fwd, backStrafePower,
                   vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::rev, backStrafePower,
                    vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    // Strafe right
    backRight.spin(vex::directionType::rev, backStrafePower,
                   vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::fwd, backStrafePower,
                    vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()) {
    // Move Straight Up
    frontRight.spin(vex::directionType::fwd, moveSpeed,
                    vex::velocityUnits::pct);
    backRight.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()) {
    // Move Straight Down
    frontRight.spin(vex::directionType::rev, moveSpeed,
                    vex::velocityUnits::pct);
    backRight.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else {
    // Stop
    frontRight.stop(vex::brakeType::brake);
    backRight.stop(vex::brakeType::brake);
  }

  // Left side movement
  if (Controller1.Axis4.value() >= 10 && Controller1.Axis4.value() <= -10){
    //turn
    frontRight.spin(vex::directionType::fwd, rightPower,
                    vex::velocityUnits::pct);
  } else if (leftPower != 0) {
    //drive
    frontLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, leftPower, vex::velocityUnits::pct);
  } else if (Controller1.ButtonUp.pressing()) {
    // Move Up
    frontLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, moveSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonDown.pressing()) {
    // Move Down
    frontLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, moveSpeed, vex::velocityUnits::pct);
  } else {
    // Stop
    frontLeft.stop(vex::brakeType::brake);
    backLeft.stop(vex::brakeType::brake);
  }

  
  //gyro stuff
  if (gyroCounter < 2) {
    gyroCounter += 1;
  } else {
    preGyroRotation = gyroSensor.value(vex::analogUnits::range12bit);
    gyroCounter = 0;
  }

  if (Controller1.ButtonLeft.pressing()) {
    // Strafe left
    gyroRotation = gyroSensor.value(vex::analogUnits::range12bit);

    if (gyroRotation != preGyroRotation) {
      frontStrafePower /= gyroRotation;
    }

    backRight.spin(vex::directionType::fwd, backStrafePower,
                   vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::rev, frontStrafePower,
                    vex::velocityUnits::pct);
    frontLeft.spin(vex::directionType::fwd, frontStrafePower,
                   vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::rev, backStrafePower,
                  vex::velocityUnits::pct);
  } else if (Controller1.ButtonRight.pressing()) {
    // Strafe right
    gyroRotation = gyroSensor.value(vex::analogUnits::range12bit);

    if (gyroRotation != preGyroRotation) {
      frontStrafePower /= (gyroRotation/preGyroRotation);
    }

    backRight.spin(vex::directionType::rev, backStrafePower,
                   vex::velocityUnits::pct);
    frontRight.spin(vex::directionType::fwd, frontStrafePower,
                    vex::velocityUnits::pct);
    frontLeft.spin(vex::directionType::rev, frontStrafePower,
                   vex::velocityUnits::pct);
    backLeft.spin(vex::directionType::fwd, backStrafePower,
                  vex::velocityUnits::pct);
  }

  Brain.Screen.clearScreen();

  task::sleep(20);
  //gyroRotation = gyroSensor.value(analogUnits::range12bit);
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print(gyroSensor.value(analogUnits::range12bit));

  // // Do some sick donuts
  // if (Controller1.ButtonB.pressing()) {
  //   frontLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  //   backRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  //   backLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // }
}

// Controls ramp n intake movements for driver control section
void rampNIntake(void) {

  // Ramp movement
  if (Controller1.ButtonX.pressing() && ramp.position(degrees) >= 1500) {
    Controller1.rumble(".");
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  } else if (Controller1.ButtonA.pressing() && ramp.position(degrees) <= -100) {
    Controller1.rumble(".");
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  } else if (Controller1.ButtonX.pressing()) {
    ramp.spin(vex::directionType::fwd, rampSpeed, vex::velocityUnits::pct);
    ramp2.spin(vex::directionType::fwd, rampSpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonA.pressing()) {
    ramp.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::pct);
    ramp2.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::pct);
  } else {
    ramp.stop(vex::brakeType::hold);
    ramp2.stop(vex::brakeType::hold);
  }

  if (Controller1.ButtonY.pressing()) {
    grabbyGuy.spin(vex::directionType::fwd, grabbySpeed, vex::velocityUnits::pct);
  } else if (Controller1.ButtonB.pressing()) {
    grabbyGuy.spin(vex::directionType::rev, grabbySpeed, vex::velocityUnits::pct);
  } else {
    grabbyGuy.stop(vex::brakeType::hold);
  }

  // Claw control
  if (Controller1.ButtonR2.pressing()) {
    leftClaw.spin(vex::directionType::fwd, intakeSpeed,
                  vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::fwd, intakeSpeed,
                   vex::velocityUnits::pct);
  } else if (Controller1.ButtonR1.pressing()) {
    leftClaw.spin(vex::directionType::rev, intakeSpeed,
                  vex::velocityUnits::pct);
    rightClaw.spin(vex::directionType::rev, intakeSpeed,
                   vex::velocityUnits::pct);
  } else {
    leftClaw.stop(vex::brakeType::hold);
    rightClaw.stop(vex::brakeType::hold);
  }

  // Runs stack function
  // Controller1.ButtonY.pressed(stack);
  // if (Controller1.ButtonY.pressing() && stacking == false) {
  //   stacking = true;
  //   stack();
  // }
}

// fish
void fish(void) {

  Brain.Screen.clearScreen();
  // fish size = (average distance from range sensors)*5
  fishSize =
      ((rangeSensor1.distance(inches) + rangeSensor2.distance(inches)) / 2) * 3;
  if (fishSize >= 25) {
    fishSize = 25;
  }

  // Draw Water
  Brain.Screen.setPenColor(waterBlue);
  Brain.Screen.setFillColor(waterBlue);
  Brain.Screen.drawRectangle(0, 0, 500, 500);

  // Draw land
  Brain.Screen.setPenColor(landGreen);
  Brain.Screen.setFillColor(landGreen);
  Brain.Screen.drawCircle(3, 8, 17);
  Brain.Screen.drawCircle(36, 5, 38);
  Brain.Screen.drawCircle(80, 10, 50);
  Brain.Screen.drawCircle(138, 9, 39);
  Brain.Screen.drawCircle(189, 3, 63);

  // fish
  Brain.Screen.setPenColor(fishGold);
  Brain.Screen.setFillColor(fishGold);
  Brain.Screen.drawCircle(fishX, fishY, fishSize);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawCircle((fishX - fishSize / 2), (fishY - fishSize / 4),
                          (fishSize / 4));
  // tail
  Brain.Screen.setPenColor(fishGold);
  Brain.Screen.setFillColor(fishGold);
  Brain.Screen.drawCircle((fishX + (fishSize * 1.5)), fishY, fishSize);
  Brain.Screen.setPenColor(waterBlue);
  Brain.Screen.setFillColor(waterBlue);
  Brain.Screen.drawCircle((fishX + fishSize * 2.25), (fishY), fishSize);

  // rectangles
  // Brain.Screen.drawRectangle(fishX, (fishY -(fishSize/2)), (fishSize*2),
  // fishSize); Brain.Screen.drawRectangle((fishX + (fishSize*1.5)), (fishY -
  // fishSize), (fishSize/1.5), (fishSize*2));

  // triangle
  // Brain.Screen.drawLine(fishX, fishY, (fishX + 30), (fishY - 15));
  // Brain.Screen.drawLine((fishX + 30), (fishY - 15), (fishX + 30), (fishY +
  // 15)); Brain.Screen.drawLine((fishX + 30), (fishY + 15), fishX, fishY);

  // move fish
  fishX -= 2;
  if (fishX < (0 - (fishSize * 2))) {
    fishX = 500;
  }
}

// Driver Control Section
void opcontrol(void) {

  for (;;) {

    // if we aint playin pong
    if (pongQuestionMark == "No") {

      //----------------------------Movement-----------------------------

      driveMovement();
      rampNIntake();

      //-----------------------------Extra-------------------------------

      // Rumble controller at 30 seconds
      if (Brain.timer(timeUnits::sec) == 30) {
        Controller1.rumble("...");
      }

      // fish
      //fish();

      // switch to pong time
      if (Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing() &&
          Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()) {
        pongQuestionMark = "Yes";
      }

      // Adds delay between each run
      vex::task::sleep(200);

      // pong time baybee
    } else if (pongQuestionMark == "Yes") {

      // boo you loser why are you switching back
      if (Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing() &&
          Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()) {
        pongQuestionMark = "No";
      }
    }
  }
}

int main() {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.autonomous(auton);
  Competition.drivercontrol(opcontrol);

  for (;;) {
    vex::task::sleep(100);
  }
}