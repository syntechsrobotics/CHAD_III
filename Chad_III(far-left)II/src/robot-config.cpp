#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
sonar rangeSensor1 = sonar(Brain.ThreeWirePort.A);
motor frontRight = motor(PORT16, ratio18_1, true);
motor frontLeft = motor(PORT15, ratio18_1, false);
motor backRight = motor(PORT17, ratio18_1, true);
motor backLeft = motor(PORT11, ratio18_1, false);
motor ramp = motor(PORT20, ratio36_1, false);
motor rightClaw = motor(PORT18, ratio18_1, true);
motor leftClaw = motor(PORT13, ratio18_1, false);
motor ramp2 = motor(PORT12, ratio36_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}