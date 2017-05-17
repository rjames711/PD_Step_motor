#include <pd_stepper.h>

PD_Stepper s =  PD_Stepper(8,9,3060);
int endstop=13;
int offset=-50;
int cycle_degrees=180;
int end_delay=200;
int count =0;

void setup() {
  pinMode(endstop,INPUT);
  Serial.begin(9600);
  findHome();
  delay(100);
  s.goto_position_degrees(offset,10);
  delay(100);
  s.step_degrees(180,20);
  delay(100);
  s.goto_position_degrees(0,20);
  delay(1000);
  s.goto_position_degrees(45,5);
 // s.step_degrees(offset,10);
}

void loop() {
//  if(count==2)
//    s.goto_position_degrees(0,10);
//  cycle();
  
}

void cycle(){
  s.step_degrees(cycle_degrees,10);
  //Serial.println(s.get_position());
  delay(end_delay);
  s.step_degrees(-cycle_degrees,20);
  //Serial.println(s.get_position());
  delay(end_delay);
  count++;
 
  Serial.println(count);
}

void findHome() {
  int deg=0;
  while (!digitalRead(endstop)) {
    s.step_degrees(-1,10);
    deg+=1;
    if (deg>180)
      while(true); //error loop
  }
  s.reset_position();
}

