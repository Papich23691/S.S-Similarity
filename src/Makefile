CC = g++

SRC = main.cpp py_util.cpp nlp.cpp linear_space_util.cpp
OBJ = run
INCLUDE_DIR = ../include
CFLAGS+=$(shell python3-config --cflags)
LDFLAGS+=$(shell python3-config --ldflags)
INCLUDE_PYTHON = ./

ifeq ($(OS),Windows_NT)
	INCLUDE_PYTHON=C:\Python36\include
	STD=gnu++11
else
	STD=c++2a
endif

all:
	@$(CC) $(SRC) -I$(INCLUDE_PYTHON) -I$(INCLUDE_DIR) $(CFLAGS) $(LDFLAGS) -lpython3.9 -w -o $(OBJ) -std=$(STD)
	$(info Run ./run)
	$(info The most accurate model after testing is "en_core_web_md")

clean:
	@rm -rf ./run ./run.dSYM 
