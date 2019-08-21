#include <iostream>
#include <cstdio>

#include "serialize.h"

int main(){

  serialize soA(8);
  serialize soB(8);
  int targetA[] = {1010,0,5000,-1,65537,1,65536,65535};
  int targetB[] = {100,1,5,1,1,1,100,101};

  soA.print(targetA);
  soB.print(targetB);

  int i = 0;
  soA.iToC(targetA);
  soB.iToC(targetB);

  soA.print(soA.getCBuf());
  soB.print(soB.getCBuf());

  soA.cToI(soA.getCBuf());
  soB.cToI(soB.getCBuf());

  soA.print(soA.getIBuf());
  soB.print(soB.getIBuf());

  printf("\n");
}
