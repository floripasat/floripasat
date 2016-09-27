#include <pid.h>

void Pid_Init(Pid *pid, float PFactor, float IFactor, float DFactor,
		int ScalingFactor)
{
	/*
	 * Start values for PID controller.
	 */
	pid->SumError = 0;
	pid->LastProcessValue = 0;

	pid->ScalingFactor = ScalingFactor;

	/*
	 * Tuning constants for PID loop.
	 */
	pid->PFactor = (int)(PFactor*(float)pid->ScalingFactor);
	pid->IFactor = (int)(IFactor*(float)pid->ScalingFactor);
	pid->DFactor = (int)(DFactor*(float)pid->ScalingFactor);

	/*
	 *  Limits to avoid overflow.
	 */
	pid->MaxError = INT_MAX / (pid->PFactor + 1);
	pid->MaxSumError = PID_MAX / (pid->IFactor + 1);
}

float Pid_Control(int SetPoint, float ProcessValue, Pid *pid)
{
	volatile int PTerm, DTerm;
	volatile long ITerm, Temp;
	volatile float Ret,Error;

	Error = SetPoint - ProcessValue;

	/*
	 * Calculate Pterm and limit error overflow.
	 */
	if (Error > pid->MaxError) {
		PTerm = INT_MAX;
	} else if (Error < -pid->MaxError) {
		PTerm = -INT_MAX;
	} else {
		PTerm = pid->PFactor * Error;
	}

	/*
	 * Calculate ITerm and limit integral runaway.
	 */
	Temp = pid->SumError + Error;

	if (Temp > pid->MaxSumError) {
		ITerm = MAX_I_TERM;
		pid->SumError = pid->MaxSumError;
	} else if (Temp < -pid->MaxSumError) {
		ITerm = -MAX_I_TERM;
		pid->SumError = -pid->MaxSumError;
	} else {
		pid->SumError = Temp;
		ITerm = pid->IFactor * pid->SumError;
	}

	/*
	 * Calculate DTerm.
	 */
	DTerm = pid->DFactor * (pid->LastProcessValue - ProcessValue);

	pid->LastProcessValue = ProcessValue;

	Ret = (PTerm + ITerm + DTerm) / pid->ScalingFactor;

	if (Ret > INT_MAX) {
		Ret = INT_MAX;
	} else if (Ret < -INT_MAX) {
		Ret = -INT_MAX;
	}

	Ret = Ret*0.000015259+0.5;

	return ((float) Ret);
}
