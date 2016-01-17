/* proof of concept exerciser for ROBOT-C port of Arduino PID auto tune library */


///
/// Motor Control setup.  Consider moving this function into
/// an include file for easy use in development and competition code.
///
#include <..\..\Arduino-PID-Library\PID_v1.cpp> // ROBOT-C port of Arduino PID library


void MyPIDSetup()
{
    int EncoderPort = 0;  // Encoder sensor port
    int MotorPorts[] = { 1, 2, 3, 4, 5 }; // Motor drive ports - we assume that +127 give max positive RPM
    int ControllerDirection = DIRECT; // set to REVERSE if your encoder is reversed relative to output direction

    float Setpoint = 500; // normal desired speed, in encoder ticks per millisecond

    // "Conservative" tuning parameters per the Arduino adaptive tuning example (aggressive: Kp=4, Ki=0.2, Kd=1;)
    float Kp = 1;
    float Ki = .05;
    float Kd = .25;

    // Begin the motor control background task
    PID(EncoderPort, MotorPorts, ARRAYSIZE(MotorPorts), Setpoint, Kp, Ki, Kd, ControllerDirection);
}
///
/// End of Motor Control setup.  Consider moving this function into
/// an include file for easy use in development and competition code.
///

#include <PID_AutoTune_v0.cpp>


task main()
{

    MyPIDSetup();
    Setup_PID_ATune(myInput, myOutput); // Initialize autotune
		SetControlType(1); //0=PI, 1=PID
    while( true )
        {
				if (Runtime() == 1)
					break; // Done tuning
        }
    // Now get the new parameters - use a debugger to inspect
		float kp= PID_ATune_GetKp();

		float ki= PID_ATune_GetKi();

		float kd= PID_ATune_GetKd();
}
