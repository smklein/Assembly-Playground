OBJS = out/x86.o out/parsing.o out/playground.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++14 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


playground : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o out/playground

out/x86.o: x86.cpp
	$(CC) $(CFLAGS) x86.cpp -o out/x86.o

out/parsing.o: parsing.cpp
	$(CC) $(CFLAGS) parsing.cpp -o out/parsing.o

out/playground.o: playground.cpp
	$(CC) $(CFLAGS) playground.cpp -o out/playground.o

clean:
	rm out/*
