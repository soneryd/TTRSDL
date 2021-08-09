OBJS = src/main.cpp src/Renderer.cpp src/Tetris.cpp src/Tetromino.cpp

SRC_DIR = src
CC = g++

LINKER_FLAGS = -lSDL2
OBJ_NAME = TTRSDL

.PHONY: all clean
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

