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
gyro gyroSensor = gyro(Brain.ThreeWirePort.E);
motor frDrive = motor(PORT16, ratio18_1, true);
motor flDrive = motor(PORT15, ratio18_1, false);
motor brDrive = motor(PORT17, ratio18_1, true);
motor blDrive = motor(PORT12, ratio18_1, false);
motor ramp = motor(PORT20, ratio36_1, true);
motor clawR = motor(PORT18, ratio18_1, true);
motor clawL = motor(PORT13, ratio18_1, false);
motor armMotor = motor(PORT19, ratio18_1, false);

// VEXcode generated functions



