#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller CountyGuy = controller(partner);
sonar rangeSensor1 = sonar(Brain.ThreeWirePort.A);
sonar rangeSensor2 = sonar(Brain.ThreeWirePort.C);
gyro gyroSensor = gyro(Brain.ThreeWirePort.E);
motor frontRight = motor(PORT16, ratio18_1, true);
motor frontLeft = motor(PORT15, ratio18_1, false);
motor backRight = motor(PORT17, ratio18_1, true);
motor backLeft = motor(PORT12, ratio18_1, false);
motor ramp = motor(PORT20, ratio36_1, true);
motor rightClaw = motor(PORT18, ratio18_1, true);
motor leftClaw = motor(PORT13, ratio18_1, false);
motor armMotor = motor(PORT19, ratio18_1, false);

// VEXcode generated functions



