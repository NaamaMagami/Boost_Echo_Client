CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: EchoClient
	g++ -o bin/echoExample bin/connectionHandler.o $(LDFLAGS) 

EchoClient: dudu
	
dudu: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
