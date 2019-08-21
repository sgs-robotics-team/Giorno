#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "serialize.h"
#include "transferclient.h"
#include "motor.h"

#define RECV 125
#define SEND 255

int main(){

  //transferclient tco;
  //serialize so((int)NUMMOTORS);
  motor mo;
  printf("\n---START---\n");


  mo.setTargetRPM(500);
  mo.updateTargetRPMs();

  printf("\n---END---\n\n");
  return 0;
}

void loop(){//main loop?
  printf("test");
}


/*
mo.setTargetRPM(99);
for(int i = 0;i < mo.getSize();i++){
  printf("target: %d current: %d\n",mo.getTargetRPM()[i],mo.getCurrentRPM()[i]);
}
*/

/*
transferclient tco;
serialize so((int)NUMMOTORS);

int targetRPM[] = {100,1,5,1,1,1,100,101};

targetRPM[4]=100;

char* rpmcharbuffer = so.toChar(targetRPM);
char* nullbuffer = so.toChar();

//tco.tsend(rpmcharbuffer);
char* readvalues = tco.rsend(nullbuffer);
int i = 0;
while(readvalues[i]!='\0'){
  printf("%c",readvalues[i]);
  i++;
}
//tco.tsend(rpmcharbuffer);
*/
