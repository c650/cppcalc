CC=g++
CFLAGS = -Wall -Werror --std=c++11

# Sources
SRC= ./src/*.cpp
OUT= ./bin/calculator.out

build: ${SRC}
	${CC} ${CFLAGS} -o ${OUT} ${SRC}

.PHONY: clean

clean:
	rm ./bin/*.out
