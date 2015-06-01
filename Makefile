OBJS = opcodes.o parsing.o playground.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


playground : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o playground

opcodes.o: opcodes.cpp
	$(CC) $(CFLAGS) opcodes.cpp

parsing.o: parsing.cpp
	$(CC) $(CFLAGS) parsing.cpp

playground.o: opcodes.h playground.cpp
	$(CC) $(CFLAGS) playground.cpp

clean:
	rm *.o playground
