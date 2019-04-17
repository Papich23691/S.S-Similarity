CC = g++
SRC = main.cpp py_util.c nlp.cpp linear_space_util.cpp
OBJ = test
CFLAGS+=$(shell python3-config --cflags)
LDFLAGS+=$(shell python3-config --ldflags)

all:
	@$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(FLAGS) -o $(OBJ) -std=c++11

