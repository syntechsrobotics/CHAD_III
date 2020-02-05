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
int autoNumber = 2;

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

// Defining fish variables
int fishX = 50;
int fishY = 150;
int fishSize = 20;
color waterBlue = vex::color(0, 9, 153);
color landGreen = vex::color(4, 149, 28);
color fishGold = vex::color(255, 217, 29);

//defining pong variables
int pingY = 50;
int pongY = 50;
int ballX = 70;
int ballY = 90;
bool ballFacingRightQuestionMark = true;
bool ballGoingUpQuestionMark = false;

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


//-----------------------------Autonomous Section of Match------------------------------
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
    //Unfold
    leftClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontRight.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    backRight.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    backLeft.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, true);

    ramp.rotateFor(-0.3, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    leftClaw.rotateFor(13, vex::rotationUnits::rev, 90, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(13, vex::rotationUnits::rev, 90, vex::velocityUnits::pct, false);
    frontRight.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);

    //turn
    frontLeft.rotateFor(-1.6, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1.6, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    frontRight.rotateFor(-3.75, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    backRight.rotateFor(-3.75, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, true);

    //move forwards and move up ramp
    leftClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontRight.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);
    
    ramp.rotateFor(1.55, vex::rotationUnits::rev, 45, vex::velocityUnits::pct, true);
    frontRight.rotateFor(0.15, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    backRight.rotateFor(0.15, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(0.15, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    backLeft.rotateFor(0.15, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, true);
   

  
    leftClaw.rotateFor(-1, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-1, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontRight.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);

    vex::task::sleep(2500);
  

  

  

  } else if (autoNumber == 3) {
    //Run far left
    //Unfold
    leftClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontRight.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    backRight.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    backLeft.rotateFor(.5, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, true);

    ramp.rotateFor(-0.3, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    leftClaw.rotateFor(11, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(11, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontRight.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(3.5, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);

    //turn
    frontRight.rotateFor(-1.6, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    backRight.rotateFor(-1.6, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-3.9, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-3.9, vex::rotationUnits::rev, 60, vex::velocityUnits::pct, true);

    //move forwards and move up ramp
    leftClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-0.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
    frontRight.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(1.85, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);
    
    ramp.rotateFor(1.6, vex::rotationUnits::rev, 45, vex::velocityUnits::pct, true);
    frontRight.rotateFor(0.25, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    backRight.rotateFor(0.25, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(0.25, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, false);
    backLeft.rotateFor(0.25, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, true);
   

    //move back
    leftClaw.rotateFor(-1, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    rightClaw.rotateFor(-1, vex::rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    frontRight.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backRight.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    frontLeft.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, false);
    backLeft.rotateFor(-1, vex::rotationUnits::rev, 30, vex::velocityUnits::pct, true);

    vex::task::sleep(2500);
  }
}


//----------------------------------OP Control Section----------------------------------
// Stacks automatically when button y is pressed
void stack(void) {

  intakeSpeed = 0;
  leftPower = 0;
  rightPower = 0;
  moveSpeed = 0;
  rampSpeed = 0;
  grabbySpeed = 0;
  backStrafePower = 0;
  frontStrafePower = 0;
  

  // Move ramp forwards
  ramp.rotateFor(1.55, vex::rotationUnits::rev, 45, vex::velocityUnits::pct,
                 true);

  vex::task::sleep(200);

  // drive forwards
  frontRight.rotateFor(0.15, vex::rotationUnits::rev, 15, vex::velocityUnits::pct,
                       false);
  backRight.rotateFor(0.15, vex::rotationUnits::rev, 15, vex::velocityUnits::pct,
                      false);
  frontLeft.rotateFor(0.15, vex::rotationUnits::rev, 15, vex::velocityUnits::pct,
                      false);
  backLeft.rotateFor(0.15, vex::rotationUnits::rev, 15, vex::velocityUnits::pct,
                     true);


  //go backwards with intake
  leftClaw.rotateFor(-1, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  rightClaw.rotateFor(-1, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  
  frontRight.rotateFor(-2, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                       false);
  backRight.rotateFor(-2, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                      false);
  frontLeft.rotateFor(-2, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                      false);
  backLeft.rotateFor(-2, vex::rotationUnits::rev, 40, vex::velocityUnits::pct,
                     true);
                     
                     

  vex::task::sleep(500);

  stacking = false;
}

//drive movement
void rightSideMovement(int speed) {
  frontRight.spin(directionType::fwd, speed, velocityUnits::pct);
  backRight.spin(directionType::fwd, speed, velocityUnits::pct);
}
void leftSideMovement(int speed) {
  frontLeft.spin(directionType::fwd, speed, velocityUnits::pct);
  backLeft.spin(directionType::fwd, speed, velocityUnits::pct);
}

// Controls wheel movements for driver control section
void driveMovement(void) {

  if (stacking == false) {

    if (arcadeDrive == true) {
      // Arcade control
      leftPower = sigmoid_map[Controller1.Axis3.value() + 127] +
                  sigmoid_map[Controller1.Axis1.value() + 127];
      rightPower = sigmoid_map[Controller1.Axis3.value() + 127] -
                   sigmoid_map[Controller1.Axis1.value() + 127];
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
      grabbySpeed = 20;
      backStrafePower = 25;
      frontStrafePower = 25;
    } else if (Controller1.ButtonL1.pressing()) {
      leftPower /= 2;
      rightPower /= 2;
      moveSpeed = 25;
      rampSpeed = 25;
      grabbySpeed = 30;
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

    // prevents overheating
    if (rightClaw.temperature(percentUnits::pct) >= 75 ||
        leftClaw.temperature(percentUnits::pct) >= 75) {
      intakeSpeed = 50;
    }

  // Right side movement
    if (Controller1.Axis1.position() >= 10 || Controller1.Axis1.position() <= 10){
      rightSideMovement(rightPower/1.5);
    } else if (rightPower != 0) {
      // drive
      rightSideMovement(rightPower);
    } else if (Controller1.ButtonUp.pressing()) {
      // Move Straight Up
      rightSideMovement(moveSpeed);
    } else if (Controller1.ButtonDown.pressing()) {
      // Move Straight Down
      moveSpeed *= -1;
      rightSideMovement(moveSpeed);
    } else {
      // Stop
      frontRight.stop(vex::brakeType::brake);
      backRight.stop(vex::brakeType::brake);
    }

    // Left side movement
    if (Controller1.Axis1.position() >= 10 || Controller1.Axis1.position() <= 10){
      leftSideMovement(leftPower/1.5);
    } else if (leftPower != 0) {
      // drive
      leftSideMovement(leftPower);
    } else if (Controller1.ButtonUp.pressing()) {
      // Move Up
      leftSideMovement(moveSpeed);
    } else if (Controller1.ButtonDown.pressing()) {
      // Move Down
      leftSideMovement(moveSpeed);
    } else {
      // Stop
      frontLeft.stop(vex::brakeType::brake);
      backLeft.stop(vex::brakeType::brake);
    }
   
    // Do some sick donuts
    if (Controller1.ButtonB.pressing() && Controller1.ButtonL2.pressing() && Controller1.ButtonRight.pressing()) {
      frontLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      backRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      backLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
  }
}
  
// Controls ramp n intake movements for driver control section
void rampNIntake(void) {

  if (stacking == false) {

    // Ramp movement
    if (Controller1.ButtonX.pressing() && ramp.position(degrees) >= 700) {
      Controller1.rumble(".");
      ramp.stop(vex::brakeType::hold);
    } else if (Controller1.ButtonA.pressing() &&
               ramp.position(degrees) <= -50) {
      Controller1.rumble(".");
      ramp.stop(vex::brakeType::hold);
    } else if (Controller1.ButtonX.pressing()) {
      ramp.spin(vex::directionType::fwd, rampSpeed, vex::velocityUnits::pct);
    } else if (Controller1.ButtonA.pressing()) {
      ramp.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::pct);
    } else {
      ramp.stop(vex::brakeType::hold);
    }

    //grabby guy stuff
    if (Controller1.ButtonY.pressing()) {
      arm.spin(vex::directionType::fwd, grabbySpeed,
                     vex::velocityUnits::pct);
    } else if (Controller1.ButtonB.pressing()) {
      arm.spin(vex::directionType::rev, grabbySpeed,
                     vex::velocityUnits::pct);
    } else {
      arm.stop(vex::brakeType::hold);
    }

    // Claw control
    if (Controller1.ButtonR1.pressing()) {
      leftClaw.spin(vex::directionType::fwd, intakeSpeed,
                    vex::velocityUnits::pct);
      rightClaw.spin(vex::directionType::fwd, intakeSpeed,
                     vex::velocityUnits::pct);
    } else if (Controller1.ButtonR2.pressing()) {
      leftClaw.spin(vex::directionType::rev, intakeSpeed,
                    vex::velocityUnits::pct);
      rightClaw.spin(vex::directionType::rev, intakeSpeed,
                     vex::velocityUnits::pct);
    } else {
      leftClaw.stop(vex::brakeType::hold);
      rightClaw.stop(vex::brakeType::hold);
    }

    // Runs stack function
    if (Controller1.ButtonLeft.pressing()) {
      stacking = true;
      stack();
    }
  }
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
  Brain.Screen.drawCircle(230, 15, 52);
  Brain.Screen.drawCircle(276, 5, 17);
  Brain.Screen.drawCircle(298, 6, 36);
  Brain.Screen.drawCircle(334, 2, 50);

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

//f
void gameOver(void) {
  pongQuestionMark = "damn it damn it damn it";
  Brain.Screen.clearScreen();
}

//ping
void pong(void) {

  //draw stuff
  Brain.Screen.clearScreen();

  Brain.Screen.drawRectangle(20, pingY, 20, 50);
  Brain.Screen.drawRectangle(450, pongY, 20, 50);
  Brain.Screen.drawCircle(ballX, ballY, 10);

  //check for collisions
  if (ballX == 40) {
    if (ballFacingRightQuestionMark == false && ballY >= (pingY -20) && ballY <= (pingY + 70)) {
      ballFacingRightQuestionMark = true;
    } else {
      gameOver();
    }
  } else if (ballX == 450) {
    if (ballFacingRightQuestionMark == true && ballY >= (pongY -20) && ballY <= (pongY + 70)) {
      ballFacingRightQuestionMark = false;
    } else {
      gameOver();
    }
  }

  //move ball left/right
  if (ballFacingRightQuestionMark == true) {
    ballX += 2;
  } else {
    ballX -= 2;
  }

  //move ball up/down
  if (ballGoingUpQuestionMark == true) {
    ballY -= 2;
  } else {
    ballY += 2;
  }

  if (ballY == 20) {
    ballGoingUpQuestionMark = false;
  } else if (ballY == 219) {
    ballGoingUpQuestionMark = true;
  }

  if (Controller1.ButtonUp.pressing() && pingY >= 1) {
    pingY -= 1;
  } else if (Controller1.ButtonDown.pressing() && pingY <= 238) {
    pingY += 1;
  }

  pongY = ballY - 25;
  

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
      fish();

      // switch to pong time
      if (Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing() &&
          Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()) {
        pongQuestionMark = "Yes";
      }

      // Adds delay between each run
      vex::task::sleep(200);

      // pong time baybee
    } else if (pongQuestionMark == "Yes") {
      //hell yeah pong time baybee

      pong();


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