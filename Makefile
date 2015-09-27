#Define required macros here
SHELL= /bin/sh

File=BankersAlgorithm

OBJS=main.o
CFLAG=-Wall -g
CC=g++
INCLUDE=
LIBS=-lm -lstdc++

Banker:${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}
clean:
	-rm -f *.o core *.core
main.o:
	${CC} -c ${File}/main.cpp

