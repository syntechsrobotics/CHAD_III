#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontRight = motor(PORT5, ratio18_1, false);
motor frontLeft = motor(PORT9, ratio18_1, true);
motor backRight = motor(PORT18, ratio18_1, true);
motor backLeft = motor(PORT11, ratio18_1, false);
motor ramp = motor(PORT6, ratio36_1, true);
motor rightClaw = motor(PORT3, ratio18_1, true);
motor leftClaw = motor(PORT1, ratio18_1, false);
motor ramp2 = motor(PORT4, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}