OBJS = parsing.o playground.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


playground : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o playground

parsing.o: parsing.cpp
	$(CC) $(CFLAGS) parsing.cpp

playground.o: playground.cpp
	$(CC) $(CFLAGS) playground.cpp

clean:
	rm *.o playground
