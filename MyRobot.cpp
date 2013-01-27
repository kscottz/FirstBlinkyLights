#include <iostream>
#include "WPILib.h"
#include <DigitalOutput.h>
using namespace std;

const int BUILD = 3;
const int RED_PIN = 1;
const int GREEN_PIN = 2;
const int YELLOW_PIN = 3;

		
//Constant variables for different ports
// USB port for the joystick.
const int JOYSTICK1 = 1;

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class Prototype : public IterativeRobot
{
private:
	Joystick stick;		// The single axis joystick with throttle control.
	DigitalOutput m_DORed; // out one
	DigitalOutput m_DOGreen; // out one
	DigitalOutput m_DOYellow; // out one
	int m_redButton;
	int m_greenButton;
	int m_yellowButton;
	
	bool oldRed;
	bool redToggle;
	bool oldYellow;
	bool yellowToggle;
	bool oldGreen;
	bool greenToggle;

	
public:
	// The constructor for our prototype code. Any initial setup of variables goes here.
	// In this case, it just calls the constructors for our joystick and two victors.
	Prototype(void) : stick(JOYSTICK1), m_DORed(RED_PIN), m_DOGreen(GREEN_PIN), m_DOYellow(YELLOW_PIN)
	{
		m_redButton = 3;
		m_yellowButton = 4;
		m_greenButton = 5;
				
		cout << "Constructor" << endl;
		cout << "RED IS ON PIN " << RED_PIN << endl;
		cout << "YELLOW IS ON PIN " << YELLOW_PIN << endl;
		cout << "GREEN IS ON PIN " << GREEN_PIN << endl;
		cout << "End constructor" << endl;
		
		oldRed = false;
		oldYellow = false;
		oldGreen = false;
		redToggle = false;
		yellowToggle = false;
		greenToggle = false;

	}
	
	// The "init" functions. These will run once as the game state changes.
	
	// Runs when the robot is turned on.
	void RobotInit()
	{
		cout << "BUILD " << BUILD << endl;
	}
	
	// Runs when the robot is disabled.
	void DisabledInit()
	{
		cout << "Disabled init" << endl;
	}
	
	// Runs when the autonomous period starts.
	void AutonomousInit()
	{
	}
	
	// Run at the beginning of the teleop period.
    void TeleopInit()
    {
    	cout << "Teleop init" << endl;
    }

    // The "periodic" functions. These are run once per "cycle" when the game is in the corresponding state.
    
    // Run during disabled. That's right, technically you can program the robot to do things in disabled mode.
	void DisabledPeriodic() 
	{
	}
	
	// Run during autonomous. This is where our autonomous code will go.
	void AutonomousPeriodic()
	{
	}
	
	// Run during teleop. The most important function to get working, without this we sit for 2 minutes with no driver control.
    void TeleopPeriodic()
    {
      	
    	if(!stick.GetRawButton(m_redButton) && oldRed)
    	{
    		redToggle = !redToggle;
    		m_DORed.Set(redToggle);
    	}
    	
    	if(!stick.GetRawButton(m_yellowButton) && oldYellow)
    	{
    		yellowToggle = !yellowToggle;
    		m_DOYellow.Set(yellowToggle);
    	}
    	
    	if(!stick.GetRawButton(m_greenButton) && oldGreen)
    	{
    		greenToggle = !greenToggle;
    		m_DOGreen.Set(greenToggle);
    	}
    		
    	oldRed = stick.GetRawButton(m_redButton);
    	oldYellow = stick.GetRawButton(m_yellowButton);
    	oldGreen = stick.GetRawButton(m_greenButton);
    }
	
};

START_ROBOT_CLASS(Prototype);
