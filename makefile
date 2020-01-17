CC=g++
INCLUDES=transferclient.h serialize.h motor.h transferclient.cpp serialize.cpp motor.cpp
STD=-std=c++11
FLAGS=-Wall -g -lm

all: tfc ser mtr main

tfc:
	$(CC) $(FLAGS) -c transferclient.h transferclient.cpp $(STD)
ser:
	$(CC) $(FLAGS) -c serialize.h serialize.cpp $(STD)
mtr:
	$(CC) $(FLAGS) -c motor.h motor.cpp $(STD) serialize.h serialize.cpp

main: 
	$(CC) $(FLAGS) main.cpp $(STD) motor.o serialize.o transferclient.o 
