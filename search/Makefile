TARGET_EXEC = search
CC = clang++

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
ASM = $(SRC:.cpp=.S)
BIN = bin
LIBS =

INC_DIR_SRC = -Isrc 

DEBUGFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB) -Wall -g
RELEASEFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB) -O3
ASMFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIBS) -Wall
LDFLAGS = 

.PHONY: all libs clean test

all: 
	$(MAKE) -j8 bld
	$(MAKE) link

dirs:
	mkdir -p ./$(BIN)

link: $(OBJ)
	$(CC) -o $(BIN)/$(TARGET_EXEC) $^ $(LDFLAGS)

bld: 
	$(MAKE) clean
	$(MAKE) dirs
	$(MAKE) obj

obj: $(OBJ)

asm: cleanassembly $(ASM)

%.o: %.cpp
	$(CC) -std=c++20 -o $@ -c $< $(RELEASEFLAGS)

%.S: %.cpp
	$(CC) -std=c++20 -o $@ -S $< $(RELEASEFLAGS)

build: dirs link

run:
	./$(BIN)/$(TARGET_EXEC) 

clean:
	clear
	rm -rf $(BIN) $(OBJ)

cleanassembly:
	rm -rf $(ASM)