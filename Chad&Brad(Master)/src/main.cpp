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
int autoNumber = 1;

// defining driving speed variables
int leftPower = 0;
int rightPower = 0;
int moveSpeed = 100;
bool arcadeDrive = false;

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

    rightDrive.rotateFor(1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, false);
    leftDrive.rotateFor(1, vex::rotationUnits::rev, 40, vex::velocityUnits::pct, true);

    vex::task::sleep(1000);

    rightDrive.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
    leftDrive.rotateFor(-1, vex::rotationUnits::rev, 75, vex::velocityUnits::pct, false);
    vex::task::sleep(2000);

  } else if (autoNumber == 2) {
    
    //we only have one point auto

  } else if (autoNumber == 3) {
    
    //we only have one point auto

  }
}


//----------------------------------OP Control Section----------------------------------

//drive movement
void rightSideMovement(int speed) {
  rightDrive.spin(directionType::fwd, speed, velocityUnits::pct);
}
void leftSideMovement(int speed) {
  leftDrive.spin(directionType::fwd, speed, velocityUnits::pct);
}

// Controls wheel movements for driver control section
void driveMovement(void) {

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
    } else if (Controller1.ButtonL1.pressing()) {
      leftPower /= 2;
      rightPower /= 2;
      moveSpeed = 25;
    } else {
      moveSpeed = 100;
    }

    // prevents overheating
    if (rightDrive.temperature(percentUnits::pct) >= 75 ||
        leftDrive.temperature(percentUnits::pct) >= 75) {
      rightPower /= 2;
      leftPower /= 2;
      moveSpeed /= 2;
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
      rightDrive.stop(vex::brakeType::brake);
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
      leftDrive.stop(vex::brakeType::brake);
    }
   
    // Do some sick donuts
    if (Controller1.ButtonL1.pressing()) {
      leftDrive.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      rightDrive.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
  }


// fish
void fish(void) {

  Brain.Screen.clearScreen();
  // fish size = (average distance from range sensors)*5
  fishSize = 25;

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