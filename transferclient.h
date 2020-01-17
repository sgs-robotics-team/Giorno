
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef TRANSFERCLIENT_H
#define TRANSFERCLIENT_H

class transferclient{

public:
  transferclient();
  ~transferclient();

  bool tconnect();
  int tsend(unsigned char* data);//transfer send
  char* rsend(unsigned char* data);//receive send
  int ssend(char* data);//simple send
  int csend();//close send (header only)

  void test();
private:

  void htonHead(struct header h,char* buf);
  void htonAttach(struct header h,char* buf,unsigned char* data);

  int valread;
  int sock;
  int size;
  int returnsize;

  struct sockaddr_in serv_addr;

};

#endif
