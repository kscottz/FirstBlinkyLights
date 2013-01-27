#ifndef FLYWHEEL_H
#define FLYWHEEL_H
#include <iostream>
// PWM ports for the victors
const int VICTOR1 = 1;
//const int VICTOR2 = 2;

// Encoder constants
int A_CHANNEL = 1;
int B_CHANNEL = 2;
Encoder::EncodingType ENCODER_TYPE = Encoder::k2X;
bool REVERSE_DIRECTION = false;

class Flywheel : public PIDOutput, public PIDSource
{
	Victor flywheel1;	// Victor used for single-motor flywheel prototype.
	// Victor flywheel2;	// Additional victor used for the dual-motor prototype.
	Encoder flywheelEncoder; // Encoder used to get flywheel spinning speed.

public:
	Flywheel() : flywheel1(VICTOR1), //flywheel2(VICTOR2), 
			flywheelEncoder(A_CHANNEL,B_CHANNEL,REVERSE_DIRECTION,ENCODER_TYPE)
	{
	}
	
	float NewMotorSpeed(float target_speed, float max_change)
	{ // Returns a value to set motor at
		float current_speed = flywheel1.Get();
		cout << "\tSpeed: " << current_speed << endl;
		float different_speed = target_speed - current_speed;
		int neg_multiplier;
		if (different_speed < 0)
			neg_multiplier = -1;
		else
			neg_multiplier = 1;
		float final = current_speed + (max_change * neg_multiplier);
		if (final < 0)
			final = 0;
		if (different_speed * neg_multiplier <= max_change)
			return target_speed;
		else
			return final;
	}
	
	
	void SetSpeed(float speed)
	{
		if (speed <= 1.0f && speed >= -1.0f)
			flywheel1.Set(speed);
			
	}
	
	void Stop()
	{
		SetSpeed(0.0f);
	}
	
	float GetSpeed()
	{
		return flywheel1.Get();
	}
	
	void PIDWrite(float output)
	{
		SetSpeed(output);
	}
	
	double PIDGet()
	{
		return flywheelEncoder.GetRate();
	}
	
};


#endif
