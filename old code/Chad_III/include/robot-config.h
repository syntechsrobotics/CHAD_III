using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor frontRight;
extern motor frontLeft;
extern motor backRight;
extern motor backLeft;
extern motor ramp;
extern motor rightClaw;
extern motor leftClaw;
extern motor ramp2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );