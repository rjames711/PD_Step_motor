/*
pd_stepper.cpp - Library for stepper motors operating on pulse / direction
interface common with industrial stepper drivers
Created by Rob Ames, 5/17/17
*/

#include "Arduino.h"
#include "pd_stepper.h"

//Constructor
PD_Stepper::PD_Stepper(int dir_pin, int pul_pin, int steps_per_rev)
{
  pinMode(dir_pin, OUTPUT);
  dir_pin_ = dir_pin;
  pinMode(pul_pin, OUTPUT);
  pul_pin_ = pul_pin;
  steps_per_rev_=steps_per_rev;
  position_=0;
}

/*
Step degrees converts the degrees rotation to a number of steps and the speed in rpm to a step delay.
The steps are then executed with the do_step function
*/
void PD_Stepper::step_degrees(long degrees, int rpm)
{
	long steps = (degrees*steps_per_rev_)/360;
	int step_delay= rpm_to_delay(rpm);
	do_steps(steps, step_delay);
		
}
/*
Goes to a given angular position. Finds the difference in steps between the current position and the 
position it need to go to then uses do_step to go to the position.
*/
void PD_Stepper::goto_position_degrees(long degrees,int rpm)
{
	long new_position = (steps_per_rev_*degrees)/360;
	long displacement = new_position - position_;	
	do_steps(displacement,rpm_to_delay(rpm));	
}



/*
This is the function which actual performs the stepping 
Takes the given number of steps with the given delay between steps.
Negative steps will be taken in the reverse direction. 
*/
void PD_Stepper::do_steps(long steps, int step_delay){
	position_+=steps;
	digitalWrite(dir_pin_,LOW);
	digitalWrite(pul_pin_,LOW);
	if (steps<0){
		digitalWrite(dir_pin_,HIGH); //If negative reverse the direction of motor
		steps=abs(steps);	//Make steps positive for loop		
	}	
	for(int i =0; i < steps; i++){
		//For each step pulse pin high and low with delays in between
		digitalWrite(pul_pin_,HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(pul_pin_,LOW);
		delayMicroseconds(step_delay);
	}
	digitalWrite(dir_pin_,LOW);
	digitalWrite(pul_pin_,LOW);
}

int PD_Stepper::get_position(){
	return position_;
}
int PD_Stepper::get_position_degrees(){
	return (position_/steps_per_rev_)*360;
}
void PD_Stepper::reset_position(){
	position_=0;
}
int PD_Stepper::rpm_to_delay(long rpm){
	long delay_per_second = steps_per_rev_*2*rpm/60; 
	int micro_second_delay= 1000000/delay_per_second;
	return micro_second_delay;
}

	



