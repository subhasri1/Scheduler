
serv: server.cpp fcfs.o rr.o priority.o
	g++ -o serv server.cpp fcfs.o rr.o priority.o

fcfs.o: fcfs.cpp class.h
	g++ -c fcfs.cpp
	
rr.o: rr.cpp class.h
	g++ -c rr.cpp
	
priority.o: priority.cpp class.h
	     g++ -c priority.cpp
