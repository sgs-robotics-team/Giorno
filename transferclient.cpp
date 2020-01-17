
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "transferclient.h"

#define PORT 50008
#define HOST "127.0.0.2"
#define HEADERSIZE 5

#define RECV 125
#define SEND 255

#define ON 255
#define OFF 1

struct header{
  char state; //255 for send,125 for recv
  char returnsize; //return string buffer size
  char active; //1 for off,255 for on (motor activity)
  uint16_t msgsize;//sent message size (should be 8 byte)
};

void transferclient::htonHead(struct header h,char* buf){
  uint16_t u16;
  char s;
  s = h.state;
  memcpy(buf+0,&s,1);
  s = h.returnsize;
  memcpy(buf+1,&s,1);
  s = h.active;
  memcpy(buf+2,&s,1);
  u16 = htons(h.msgsize);
  memcpy(buf+3,&u16,2);
}

void transferclient::htonAttach(struct header h,char* buf,unsigned char* data){
  htonHead(h,buf+0);
  memcpy(buf+HEADERSIZE,data,strlen((char*)data));
}

transferclient::transferclient(){ //CONSTRUCTOR
  sock = 0;
  this->returnsize = 9;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("ERROR: Couldn't create socket\n");
  }else{
    printf("Transferclient: Socket created\n");
  }
  if(tconnect()){
    printf("Transferclient: Connected succesfully at %s:%d\n",HOST,PORT);
  }
}

bool transferclient::tconnect(){
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, HOST, &serv_addr.sin_addr)<=0)
  {
      printf("ERROR: Invalid address or address '%s' not supported\n",HOST);
      return false;
  }
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
      printf("ERROR: Connection failed at %s:%d\n",HOST,PORT);
      return false;
  }
  return true;
}

int transferclient::tsend(unsigned char* data){
  int bufsize = HEADERSIZE+strlen((char*)data);
  printf("%d",(int)strlen((char*)data));
  char buffer[bufsize];
  header h1 = {(char)SEND,(char)returnsize,(char)ON,(uint16_t)strlen((char*)data)};
  htonAttach(h1,buffer,data);
  buffer[bufsize]='\0';
  int val = (send(sock,buffer,bufsize,0)!=-1)?1:-1;
  return val;
}

char* transferclient::rsend(unsigned char* data){
  int bufsize = HEADERSIZE+strlen((char*)data);
  char buffer[bufsize];
  header h1 = {(char)RECV,(char)returnsize,(char)ON,(uint16_t)strlen((char*)data)};
  htonAttach(h1,buffer,data);
  buffer[bufsize]='\0';
  send(sock,buffer,bufsize,0);
  bufsize = 1024;
  char* rbuf = (char*) malloc(bufsize);
  int valread = read(sock,rbuf,bufsize);
  return rbuf;
}

int transferclient::csend(){
  int bufsize = HEADERSIZE;
  char buffer[bufsize];
  header h1 = {(char)OFF,(char)OFF,(char)OFF,(uint16_t)bufsize};
  htonHead(h1,buffer);
  send(sock,buffer,bufsize,0);
}

int transferclient::ssend(char* data){
  int val =(send(sock,data,strlen(data),0)!=-1)?1:-1;
  return val;
}

void transferclient::test(){
  printf("Transferclient class functional\n");
}

transferclient::~transferclient(){
  printf("Transferclient: Shutting down...\n");
  csend();
  close(sock);
  printf("Transferclient: Socket closed.\n");
}
