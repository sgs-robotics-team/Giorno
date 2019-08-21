CC=g++
INCLUDES=transferclient.h serialize.h motor.h transferclient.cpp serialize.cpp motor.cpp
STD=-std=c++11

all: tctest

tctest: 
	$(CC) main.cpp $(INCLUDES) $(STD)
