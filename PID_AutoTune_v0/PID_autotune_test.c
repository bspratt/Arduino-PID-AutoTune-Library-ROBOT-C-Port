/* proof of concept exerciser for ROBOTC port of Arduino PID auto tune library */

#include <..\..\Arduino-PID-Library-ROBOTC-Port\PID_v1.cpp> // ROBOTC port of Arduino PID library

#include <..\..\Arduino-PID-Library-ROBOTC-Port\MyPIDSetup.cpp> // Tweak the contents of this include file to suit your hardware

#include <PID_AutoTune_v0.cpp>

task AutoTune()
{
	while(true)
	{
		while (Runtime()==0) // Perform sampling
		{
			EndTimeSlice();  // Let other tasks take a turn
		}
		// Now get the new parameters
		float kp= PID_ATune_GetKp();
		float ki= PID_ATune_GetKi();
		float kd= PID_ATune_GetKd();
		SetTunings(kp, ki, kd); // Update the PID controller task settings

		EndTimeSlice();  // Let other tasks take a turn
	}
}

task main()
{

	MyPIDSetup(); // Setup PID and start it running - see MyPIDSetup.cpp to adjust

	Setup_PID_ATune(myInput, myOutput); // Initialize autotune, tell it to watch PID task's input and output

	SetControlType(1); //0=PI, 1=PID

	startTask(AutoTune); // Continuously evaluate PID setttings

	while( true )
	{
		// bump setupoint up or down while joystick is held
		int bump = 10; // No idea if this is a meaningful value

		if (vexRT[ Ch2 ]>10)
			ChangeSetpoint(bump);
		else if (vexRT[ Ch2 ]<10)
			ChangeSetpoint(-bump);

		// Get current settings
		double kp = GetKp();
		double ki = GetKi();
		double kd = GetKd();
		double setpoint = GetSetpoint();

		// Display them or whatever you want

		wait1Msec(50);
	}
}
