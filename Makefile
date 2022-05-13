BIN=../bin
OBJ=../obj
INC=../inc
SRC=../src
CC= g++
OFLAG= -o
CFLAG= -c
WFLAG= -Wall -g

all: $(BIN)/serv $(BIN)/cli

serv: $(SRC)/server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	$(CC) $(OFLAG) $(WFLAG) $(BIN)/serv $(SRC)/server.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o

cli: $(SRC)/client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o $(OBJ)/priority.o 			$(OBJ)/sjf.o
	$(CC) $(OFLAG) $(WFLAG) $(BIN)/cli $(SRC)/client.cpp $(OBJ)/fcfs.o $(OBJ)/rr.o 			$(OBJ)/priority.o $(OBJ)/sjf.o


$(OBJ)/fcfs.o: $(SRC)/fcfs.cpp $(INC)/class.h
	$(CC) $(CFLAG) $(WFLAG)  $(SRC)/fcfs.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/rr.o: $(SRC)/rr.cpp $(INC)/class.h
	$(CC) $(CFLAG) $(WFLAG) $(SRC)/rr.cpp
	mv -f *.o $(OBJ)/
$(OBJ)/priority.o: $(SRC)/priority.cpp $(INC)/class.h
	     $(CC) $(CFLAG) $(WFLAG) $(SRC)/priority.cpp
	     mv -f *.o $(OBJ)/
$(OBJ)/sjf.o: $(SRC)/sjf.cpp $(INC)/class.h
	$(CC) $(CFLAG) $(WFLAG)  $(SRC)/sjf.cpp
	mv -f *.o $(OBJ)/
