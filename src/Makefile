CC = g++

SRC = main.cpp py_util.c nlp.cpp linear_space_util.cpp
OBJ = run
INCLUDE_DIR = ../include
CFLAGS+=$(shell python3-config --cflags)
LDFLAGS+=$(shell python3-config --ldflags)
INCLUDE_PYTHON = ./

ifeq ($(OS),Windows_NT)
	INCLUDE_PYTHON=C:\Python36\include
	STD=gnu++11
else
	STD=c++11
endif

all:
	@$(CC) $(SRC) -I$(INCLUDE_PYTHON) -I$(INCLUDE_DIR) $(CFLAGS) $(LDFLAGS) -w -o $(OBJ) -std=$(STD)
	$(info Run ./run)
	$(info To use the more accurate but slower model use "en_core_web_lg")
	$(info Otherwise use "en_core_web_sm")

clean:
	@rm -rf ./run ./run.dSYM 
