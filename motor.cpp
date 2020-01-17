
#include <cstdlib>
#include <cstdio>

#include "motor.h"
#include "serialize.h"
#include "transferclient.h"

#define NUMMOTORS 8

motor::motor(): tco(),so((int)NUMMOTORS){//(transferclient a,serialize b){
  this->size = (int)NUMMOTORS;
  this->targetrpms = (int*) malloc(NUMMOTORS*sizeof(int));
  this->currentrpms = (int*) malloc(NUMMOTORS*sizeof(int));
  this->thrusterVolts = (int*) malloc(NUMMOTORS*sizeof(int));
  this->thrusterTemps = (int*) malloc(NUMMOTORS*sizeof(int));
  this->thrusterAmps = (int*) malloc(NUMMOTORS*sizeof(int));
  this->thrusterStatus = (bool*) malloc(NUMMOTORS);
  initialize();
  printf("Motor: RPM Arrays Initialized\n");
  test();
}

void motor::initialize(){
  for(int i = 0;i < NUMMOTORS;i++){
    targetrpms[i]=0;
    currentrpms[i]=0;
  }
}

void motor::setTargetRPM(int mID,int val){
  targetrpms[mID]=val+5000;
}

void motor::setTargetRPM(int val){
  for(int i = 0;i < NUMMOTORS;i++){
    targetrpms[i]=val+5000;
  }
}

int motor::getTargetRPM(int mID){
  return targetrpms[mID];
}

int* motor::getTargetRPM(){
  return targetrpms;
}

int motor::getCurrentRPM(int mID){
  return currentrpms[mID];
}

int* motor::getCurrentRPM(){
  return currentrpms;
}

int motor::updateCurrentRPMs(){

}

int motor::updateTargetRPMs(){
  tco.tsend(so.iToC(targetrpms));
}

void motor::test(){
  printf("\nMotor class functional\n");
  tco.test();
  so.test();
  printf("\n");
}

motor::~motor(){
  printf("Motor: Shutting Down...\n");
  free(targetrpms);
  free(currentrpms);
  free(thrusterAmps);
  free(thrusterVolts);
  free(thrusterTemps);
  free(thrusterStatus);
  printf("Motor: Integer Arrays freed.");
}
