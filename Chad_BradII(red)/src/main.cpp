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
// rDrive               motor         16
// lDrive               motor         15
// sDrive               motor         2
// ramp                 motor         20
// clawR                motor         18
// clawL                motor         13
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "ButtonClass.h"
#include "robot-config.h"
#include "vex.h"
using namespace vex;

vex::competition Competition;

// Defines All Variables
#pragma region "Definitions"

// auto selection variables
int autoNumber = 4;

// defining driving speed variables
int leftPower = 0;
int rightPower = 0;
int strafePower = 0;
int moveSpeed = 100;
bool arcadeDrive = true;

// defining ramp and intake movment speed
int rampSpeed = 50;
int intakeSpeed = 100;
int armSpeed = 50;
bool stacking = false;
bool towering = false;

// Defining fish variables
int fishX = 50;
int fishY = 150;
int fishSize = 20;
color waterBlue = color(0, 9, 153);
color landGreen = color(4, 149, 28);
color fishGold = color(255, 217, 29);

// defining pong variables
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

}

/*
---------------------------------PID Controllers-----------------------------
contains pid controllers for driving straight forwards, turning and raising ramp

drive takes in target value, which is distance from wall in centimeters

intake is just drive but it also does the intake

turn takes in degrees, which is added or subtracted from the current angle
positive is a right turn and negative is a left turn
this is also usable in match

ramp takes in target value, which is the amount of degrees the motor has rotated
0 is the starting position, and fully vertical is somewhere around 700 degrees i
think
------------------------------------------------------------------------------
*/

void PIDDrive(int targetValue) {
  int rightError = 0;
  int leftError = 0;
  int rightSpeed = 0;
  int leftSpeed = 0;
  int kP = 5;

  while (rangeSensor1.distance(distanceUnits::cm) != targetValue &&
         rangeSensor2.distance(distanceUnits::cm) != targetValue) {

    rightError = targetValue - rangeSensor1.distance(distanceUnits::cm);
    leftError = targetValue - rangeSensor2.distance(distanceUnits::cm);

    rightSpeed = rightError * kP;
    leftSpeed = leftError * kP;

    rDrive.spin(directionType::fwd, rightSpeed, percentUnits::pct);
    lDrive.spin(directionType::fwd, leftSpeed, percentUnits::pct);
  }

  rDrive.stop();
  lDrive.stop();
}

void PIDTurn(int turnDegrees) {
  int originalPosition = gyroSensor.value(rotationUnits::deg);
  int error = 0;
  int speed = 0;
  int kP = 5;

  while (gyroSensor.value(rotationUnits::deg) !=
         (originalPosition + turnDegrees)) {

    error = rangeSensor1.distance(distanceUnits::cm) -
            (originalPosition + turnDegrees);

    speed = error * kP;

    rDrive.spin(directionType::fwd, speed, percentUnits::pct);
    lDrive.spin(directionType::fwd, speed, percentUnits::pct);
  }

  rDrive.stop();
  lDrive.stop();
}

void PIDRamp(int targetValue) {
  int error = 0;
  int speed = 0;
  int kP = 5;

  while (ramp.position(rotationUnits::deg) != targetValue) {
    error = ramp.position(rotationUnits::deg) - targetValue;
    speed = error * kP;

    ramp.spin(directionType::fwd, speed, percentUnits::pct);
  }

  ramp.stop();
}

/*
----------------------------general functions--------------------------------- 
these are just here to make the code shorter, and arent pids

intake takes three arguments: revolutions, speed and completion
revolutions is the amount of revolutions you want it to do
        +ve is intake, -ve is outtake
speed is the percent you want them to spin at
completion is a boolean that says whether it stops the code until it ends

raiseArms is basically the same as intake

drive just drives forwards and has the same arguments
only use when you arent sure what the distance behind the robot will be
    ex. robot doing stuff behind us 
        chance of stacked cubes in opposite goal zone
        basically just those two
-----------------------------------------------------------------------------
*/

void intake(int revolutions, int speed, bool completion) {
  clawL.rotateFor(revolutions, rotationUnits::rev, speed, velocityUnits::pct,
                  false);
  clawR.rotateFor(revolutions, rotationUnits::rev, speed, velocityUnits::pct,
                  completion);
}

void raiseArms(int revolutions, int speed, bool completion) {
  armMotor.rotateFor(revolutions, rotationUnits::rev, speed, velocityUnits::pct,
                     completion);
}

void robotDrive(int revolutions, int speed, bool completion) {
  lDrive.rotateFor(revolutions, rotationUnits::rev, speed, velocityUnits::pct,
                  false);
  rDrive.rotateFor(revolutions, rotationUnits::rev, speed, velocityUnits::pct,
                  completion);
}

//------------------------Autonomous Section of Match---------------------------
void auton(void) {

  // Run One Point
  if (autoNumber == 1) {
  } else if (autoNumber == 2) {
  } else if (autoNumber == 3) {
  } else if (autoNumber == 4) {
  }
}

//-----------------------------OP Control Section-----------------------------

// Stacks automatically when button y is pressed
void stack(void) {

  intakeSpeed = 0;
  leftPower = 0;
  rightPower = 0;
  moveSpeed = 0;
  rampSpeed = 0;
  armSpeed = 0;

  // Move ramp forwards
  ramp.rotateFor(1.25, rotationUnits::rev, 35, velocityUnits::pct, true);
  clawL.rotateFor(-1, rotationUnits::rev, 100, velocityUnits::pct, false);
  clawR.rotateFor(-1, rotationUnits::rev, 100, velocityUnits::pct, false);
  ramp.rotateFor(0.25, rotationUnits::rev, 35, velocityUnits::pct, true);
  task::sleep(400);

  // go backwards with intake
  clawL.rotateFor(-1, rotationUnits::rev, 100, velocityUnits::pct, false);
  clawR.rotateFor(-1, rotationUnits::rev, 100, velocityUnits::pct, false);

  rDrive.rotateFor(-2, rotationUnits::rev, 40, velocityUnits::pct, false);
  lDrive.rotateFor(-2, rotationUnits::rev, 40, velocityUnits::pct, false);

  task::sleep(500);

  stacking = false;
}

// tower when right button pressed
void tower(void) {

  intakeSpeed = 0;
  leftPower = 0;
  rightPower = 0;
  moveSpeed = 0;
  rampSpeed = 0;
  armSpeed = 0;

  // arm up and forwards
  armMotor.rotateFor(-3.5, rotationUnits::rev, 100, velocityUnits::pct, false);
  rDrive.rotateFor(1.5, rotationUnits::rev, 15, velocityUnits::pct, false);
  lDrive.rotateFor(1.5, rotationUnits::rev, 15, velocityUnits::pct, false);
  clawL.rotateFor(-2, rotationUnits::rev, 100, velocityUnits::pct, false);
  clawR.rotateFor(-2, rotationUnits::rev, 100, velocityUnits::pct, true);

  towering = false;
}

// Controls wheel movements for driver control section
void driveMovement(void) {

  if (stacking == false && towering == false) {

    if (arcadeDrive == true) {
      // Arcade control
      leftPower = sigmoid_map[Controller1.Axis3.value() + 127] +
                  sigmoid_map[Controller1.Axis1.value() + 127];
      rightPower = sigmoid_map[Controller1.Axis3.value() + 127] -
                   sigmoid_map[Controller1.Axis1.value() + 127];
      strafePower = sigmoid_map[Controller1.Axis4.value() + 127];
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
      armSpeed = 5;
    } else if (Controller1.ButtonL1.pressing()) {
      leftPower /= 2;
      rightPower /= 2;
      moveSpeed = 25;
      rampSpeed = 25;
      armSpeed = 10;
    } else {
      intakeSpeed = 100;
      moveSpeed = 100;
      rampSpeed = 50;
      armSpeed = 50;
    }

    // prevents overheating
    if (clawR.temperature(percentUnits::pct) >= 75 ||
        clawL.temperature(percentUnits::pct) >= 75) {
      intakeSpeed = 50;
    }

    // Right side movement
    if (Controller1.Axis4.value() >= 10 && Controller1.Axis4.value() <= -10) {
      // turn
      rDrive.spin(directionType::fwd, rightPower, velocityUnits::pct);
    } else if (rightPower != 0) {
      // drive
      rDrive.spin(directionType::fwd, rightPower, velocityUnits::pct);
    } else if (Controller1.ButtonUp.pressing()) {
      // Move Straight Up
      rDrive.spin(directionType::fwd, moveSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonDown.pressing()) {
      // Move Straight Down
      rDrive.spin(directionType::rev, moveSpeed, velocityUnits::pct);
    } else {
      // Stop
      rDrive.stop(brakeType::brake);
    }

    // Left side movement
    if (Controller1.Axis4.value() >= 10 && Controller1.Axis4.value() <= -10) {
      // turn
      lDrive.spin(directionType::fwd, leftPower, velocityUnits::pct);
    } else if (leftPower != 0) {
      // drive
      lDrive.spin(directionType::fwd, leftPower, velocityUnits::pct);
    } else if (Controller1.ButtonUp.pressing()) {
      // Move Up
      lDrive.spin(directionType::fwd, moveSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonDown.pressing()) {
      // Move Down
      lDrive.spin(directionType::rev, moveSpeed, velocityUnits::pct);
    } else {
      // Stop
      lDrive.stop(brakeType::brake);
    }

    // Do some sick donuts
    if (Controller1.ButtonB.pressing() && Controller1.ButtonL2.pressing() &&
        Controller1.ButtonRight.pressing()) {
      lDrive.spin(directionType::fwd, 100, velocityUnits::pct);
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(gyroSensor.heading());
    Brain.Screen.setCursor(20, 20);
    Brain.Screen.print(gyroSensor.angle());
    

  }
}

// Controls ramp n intake movements for driver control section
void rampNIntake(void) {

  if (stacking == false && towering == false) {

    // Ramp movement
    if (Controller1.ButtonX.pressing() && ramp.position(degrees) >= 700) {
      Controller1.rumble(".");
      ramp.stop(brakeType::hold);
    } else if (Controller1.ButtonA.pressing() &&
               ramp.position(degrees) <= -50) {
      Controller1.rumble(".");
      ramp.stop(brakeType::hold);
    } else if (Controller1.ButtonX.pressing()) {
      ramp.spin(directionType::fwd, rampSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonA.pressing()) {
      ramp.spin(directionType::rev, rampSpeed, velocityUnits::pct);
    } else {
      ramp.stop(brakeType::hold);
    }

    // grabby guy stuff
    if (Controller1.ButtonY.pressing()) {
      armMotor.spin(directionType::fwd, armSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonB.pressing()) {
      armMotor.spin(directionType::rev, armSpeed, velocityUnits::pct);
    } else {
      armMotor.stop(brakeType::hold);
    }

    // Claw control
    if (Controller1.ButtonR1.pressing()) {
      clawL.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
      clawR.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonR2.pressing()) {
      clawL.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
      clawR.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    } else {
      clawL.stop(brakeType::hold);
      clawR.stop(brakeType::hold);
    }

    // Runs stack function
    if (Controller1.ButtonLeft.pressing()) {
      stacking = true;
      stack();
    }
    // Runs tower function
    if (Controller1.ButtonRight.pressing()) {
      towering = true;
      tower();
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
  Brain.Screen.drawCircle(210, 13, 37);
  Brain.Screen.drawCircle(252, 6, 29);
  Brain.Screen.drawCircle(280, 22, 17);
  Brain.Screen.drawCircle(321, 12, 26);

  // fish
  Brain.Screen.setPenColor(fishGold);
  Brain.Screen.setFillColor(fishGold);
  Brain.Screen.drawCircle(fishX, fishY, fishSize);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawCircle((fishX - fishSize / 2), 
                    (fishY - fishSize / 4), (fishSize / 4));
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

// f
void gameOver(void) {
  pongQuestionMark = "damn it damn it damn it";
  Brain.Screen.clearScreen();
}

// ping
void pong(void) {

  // draw stuff
  Brain.Screen.clearScreen();

  Brain.Screen.drawRectangle(20, pingY, 20, 50);
  Brain.Screen.drawRectangle(450, pongY, 20, 50);
  Brain.Screen.drawCircle(ballX, ballY, 10);

  // check for collisions
  if (ballX == 40) {
    if (ballFacingRightQuestionMark == false && ballY >= (pingY - 20) &&
        ballY <= (pingY + 70)) {
      ballFacingRightQuestionMark = true;
    } else {
      gameOver();
    }
  } else if (ballX == 450) {
    if (ballFacingRightQuestionMark == true && ballY >= (pongY - 20) &&
        ballY <= (pongY + 70)) {
      ballFacingRightQuestionMark = false;
    } else {
      gameOver();
    }
  }

  // move ball left/right
  if (ballFacingRightQuestionMark == true) {
    ballX += 2;
  } else {
    ballX -= 2;
  }

  // move ball up/down
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

    while(gyroSensor.isCalibrating() ) {
      task::sleep(200);
    }

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
      task::sleep(50);

      // pong time baybee
    } else if (pongQuestionMark == "Yes") {
      // hell yeah pong time baybee

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
    task::sleep(100);
  }
}