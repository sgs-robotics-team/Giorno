/**
    SGS Robotics
    motor.h

    @author Stephen Yang
    @version 1.2 13/08/19
*/
#include "serialize.h"
#include "transferclient.h"

#ifndef MOTOR_H
#define MOTOR_H

class motor{

public:
  //setTargetRPM
  motor();
  ~motor();

  void initialize();//initializes arrays targetrpms and

  /**
    sets target RPM of thruster with ID in param
    @param mID the ID of a thruster, range = {0,NUMMOTORS}
    @param val the percent of max RPM target for this thruster
  */
  void setTargetRPM(int mID,int val);
  /**
    sets target RPM of all thrusters
    @param val the percent of max RPM target for this thruster
  */
  void setTargetRPM(int val);

  /**
    gets target/desired RPM of thruster with ID in param
    @param mID the ID of a thruster, range = {0,NUMMOTORS}
    @return the target RPM value of this motor with ID mID
  */
  int getTargetRPM(int mID);
  /**
    gets target/desired RPM of all thrusters
    @return the target RPM values of all motors
  */
  int* getTargetRPM();

  /**
    gets current/sensor RPM of thruster with ID in param
    @param mID the ID of a thruster, range = {0,NUMMOTORS}
    @return the RPM value of this motor with ID mID
  */
  int getCurrentRPM(int mID);
  /**
    gets current/sensor RPM of all thrusters
    @return the RPM values of all motors
  */
  int* getCurrentRPM();

  /**
    updates the current RPM array by sending a "RECV" code to python thread
    @return 1 if successful, 0 if not
  */
  int updateCurrentRPMs();
  /**
    arguably the most important function: sends a "SEND" code to python thread with target RPM values
    @return 1 if successful, 0 if not
  */
  int updateTargetRPMs();

  /**
    test function (WIP)
  */
  void test();

  /**
    @return value of predefined NUMMOTORS
  */
  int getSize(){ return size; }

private:

  int size;

  int* targetrpms;//array of target rpms
  int* currentrpms;//array of current rpms

  bool* thrusterStatus;//motor on/off
  int* thrusterAmps;//array of current values measured in amps
  int* thrusterVolts;//array of voltage values measured in volts
  int* thrusterTemps;//array of temperature values measured in C

  transferclient tco;//transferclient object
  serialize so;//serialize object
};

#endif