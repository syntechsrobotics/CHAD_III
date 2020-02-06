#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor rightDrive = motor(PORT16, ratio18_1, true);
motor leftDrive = motor(PORT15, ratio18_1, false);

// VEXcode generated functions



