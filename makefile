BIN=../bin
OBJ=../obj
INC=../inc

$(BIN)/cli: client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	g++ -o $(BIN)/cli client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o


$(BIN)/serv: server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	g++ -o $(BIN)/serv server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o



$(OBJ)/fcfs.o: fcfs.cpp $(INC)/class.h
	g++ -c fcfs.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/rr.o: rr.cpp $(INC)/class.h
	g++ -c rr.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/priority.o: priority.cpp $(INC)/class.h
	     g++ -c priority.cpp
	     mv -f *.o $(OBJ)/
$(OBJ)/sjf.o: sjf.cpp $(INC)/class.h
	g++ -c sjf.cpp
	mv -f *.o $(OBJ)/
	

