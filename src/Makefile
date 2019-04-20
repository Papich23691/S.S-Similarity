CC = g++
SRC = main.cpp py_util.c nlp.cpp linear_space_util.cpp
OBJ = run
INCLUDE_DIR = ../include
CFLAGS+=$(shell python3-config --cflags)
LDFLAGS+=$(shell python3-config --ldflags)

all:
	@$(CC) $(SRC) -I$(INCLUDE_DIR) $(CFLAGS) $(LDFLAGS) -w -o $(OBJ) -std=c++11
$(info Run ./run in src)
