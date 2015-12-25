OBJS = out/opcodes.o out/parsing.o out/playground.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


playground : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o out/playground

out/opcodes.o: opcodes.cpp
	$(CC) $(CFLAGS) opcodes.cpp -o out/opcodes.o

out/parsing.o: parsing.cpp
	$(CC) $(CFLAGS) parsing.cpp -o out/parsing.o

out/playground.o: playground.cpp
	$(CC) $(CFLAGS) playground.cpp -o out/playground.o

clean:
	rm out/*
