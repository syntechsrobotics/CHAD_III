#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
sonar rangeSensor1 = sonar(Brain.ThreeWirePort.G);
sonar rangeSensor2 = sonar(Brain.ThreeWirePort.C);
inertial inertialSensor = inertial(PORT10);
motor rDrive = motor(PORT16, ratio18_1, true);
motor lDrive = motor(PORT17, ratio18_1, true);
motor sDrive = motor(PORT2, ratio18_1, false);
motor ramp = motor(PORT20, ratio36_1, true);
motor clawR = motor(PORT18, ratio18_1, true);
motor clawL = motor(PORT13, ratio18_1, false);
motor armMotor = motor(PORT19, ratio18_1, false);

// VEXcode generated functions



