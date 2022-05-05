BIN=../bin
OBJ=../obj
INC=../inc
SRC=../src
CC=g++

all: $(BIN)/serv $(BIN)/cli

$(BIN)/serv: $(SRC)/server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	$(CC) -o $(BIN)/serv $(SRC)/server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o

$(BIN)/cli: $(SRC)/client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	$(CC) -o $(BIN)/cli $(SRC)/client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o



	

	



$(OBJ)/fcfs.o: $(SRC)/fcfs.cpp $(INC)/class.h
	$(CC) -c $(SRC)/fcfs.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/rr.o: $(SRC)/rr.cpp $(INC)/class.h
	$(CC) -c $(SRC)/rr.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/priority.o: $(SRC)/priority.cpp $(INC)/class.h
	     $(CC) -c $(SRC)/priority.cpp
	     mv -f *.o $(OBJ)/
$(OBJ)/sjf.o: $(SRC)/sjf.cpp $(INC)/class.h
	$(CC) -c $(SRC)/sjf.cpp
	mv -f *.o $(OBJ)/

	

