/**
    SGS Robotics
    serialize.cpp

    @author Stephen Yang
    @version 1.2 13/08/19
*/
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string.h>

#include "serialize.h"

serialize::serialize(int size){
  this->size = size;
  this->ibuf = (int*) malloc(size*sizeof(int));
  this->cbuf = (unsigned char*) malloc(size*2);
  this->nbuf = (char*) malloc(size);
  initialize();
  printf("Serialize: Buffers Initialized\n");
}

void serialize::initialize(){
  for(int i = 0;i < size;i++){
    ibuf[i]=0;
    nbuf[i]=10;
  }
}

void serialize::print(int* a){
  printf("[");
  for(int i = 0;i < size;i++){
    if(i==size-1){
      printf("%d",a[i]);
      break;
    }
    printf("%d,",a[i]);
  }
  printf("]\n");
}

void serialize::print(unsigned char* a){
  printf("[");
  for(int i = 0;i < size*2;i++){
    if(i==(2*size)-1){
      printf("%c:%d",a[i],a[i]);
      break;
    }
    printf("%c:%d,",a[i],a[i]);
  }
  printf("]\n");
}

unsigned char* serialize::iToC(int *a){
  cbuf = convert(a);
  return cbuf;
}

int* serialize::cToI(unsigned char* a){
  ibuf = convert(a);
  return ibuf;
}

unsigned char* serialize::convert(int* a){
  for(int i = 0;i<size;i++){
    cbuf[2*i] = (char)(a[i]>>8);
    cbuf[2*i+1] = (char)(a[i]&0xff);
  }
  return cbuf;
}

int* serialize::convert(unsigned char* a){
  for(int i = 0;i<size;i++){
    ibuf[i] = (a[2*i]<<8)+a[2*i+1];
  }
  return ibuf;
}

void serialize::test(){
  printf("Serialize class functional\n");
}

serialize::~serialize(){
  printf("Serialize: Shutting down...\n");
  free(ibuf);
  free(cbuf);
  free(nbuf);
  printf("Serialize: Buffers freed.\n");
}
