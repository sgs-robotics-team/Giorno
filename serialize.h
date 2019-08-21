/**
    SGS Robotics
    serialize.h

    @author Stephen Yang
    @version 1.2 13/08/19
*/
#ifndef SERIALIZE_H
#define SERIALIZE_H

class serialize{

public:
  serialize(int size);
  ~serialize();

  void initialize();
  void print(int* a);
  void print(unsigned char* a);

  unsigned char* iToC(int *a);
  int* cToI(unsigned char *a);

  char* getNBuf(){ return nbuf; }
  int* getIBuf(){ return ibuf; }
  unsigned char* getCBuf(){ return cbuf; }

  void test();

private:

  unsigned char* convert(int* a);
  int* convert(unsigned char* a);

  int* ibuf;
  unsigned char* cbuf;
  char* nbuf;
  int size;
};

#endif
