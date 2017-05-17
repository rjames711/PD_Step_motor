/*
pd_stepper.h - Library for stepper motors operating on pulse / direction
interface common with industrial stepper drivers
Created by Rob Ames, 5/17/17
Released into the public domain.
*/
#ifndef pd_stepper_h
#define pd_stepper_h
#include "Arduino.h"

class PD_Stepper
{
  public:
	//Constructor takes the pin controlling direction and pulse / step
    PD_Stepper(int dir_pin, int pul_pin, int steps_per_rev);
	//Takes the number of given steps with a given delay between steps to control speed
	void do_steps(long steps, int step_delay);
	//Steps the given number of degree at the given speed (rpm)
	void step_degrees(long degrees, int rpm);
    //Steps to the given angle (from home position) at the given speed
	void goto_position_degrees(long degrees,int rpm);
	//Returns the net steps taken since the start or last position reset
	int get_position();
	//Returns the current position in degrees
	int get_position_degrees();
	//Makes the current position zero
	void reset_position();
	
	
  private:
	int rpm_to_delay(long rpm); //helper function to convert speed in rpm to the microsecond delay between steps
    int dir_pin_;		//Number of pin connected to direction control
	int pul_pin_;		//Number of pin connected to step / pulse control
	int steps_per_rev_;	//Number of steps per rotation for the motor 
	int position_;		//holds the net number of steps taken since start / reset 
	
};

#endif