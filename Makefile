CC = g++
SRC = src/main.cpp src/py_util.c src/nlp.cpp src/linear_space_util.cpp
OBJ = src/run
INCLUDE_DIR = include
CFLAGS+=$(shell python3-config --cflags)
LDFLAGS+=$(shell python3-config --ldflags)

all:
	@$(CC) $(SRC) -I$(INCLUDE_DIR) $(CFLAGS) $(LDFLAGS) -w -o $(OBJ) -std=c++11
$(info Run ./run in src)
