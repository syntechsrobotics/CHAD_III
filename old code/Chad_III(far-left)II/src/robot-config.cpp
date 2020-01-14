#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
//controllers
controller Controller1 = controller(primary);
//sensors
sonar rangeSensor1 = sonar(Brain.ThreeWirePort.A);
sonar rangeSensor2 = sonar(Brain.ThreeWirePort.C);
gyro gyroSensor = gyro(Brain.ThreeWirePort.G);

//motors
motor frontRight = motor(PORT16, ratio18_1, true);
motor frontLeft = motor(PORT15, ratio18_1, false);
motor backRight = motor(PORT17, ratio18_1, true);
motor backLeft = motor(PORT11, ratio18_1, false);
motor ramp = motor(PORT12, ratio36_1, false);
motor ramp2 = motor(PORT20, ratio36_1, true);
motor rightClaw = motor(PORT18, ratio18_1, true);
motor leftClaw = motor(PORT14, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}