CC = g++
CXXFLAGS = -Wall -02
OBJS = io.o ssd.o main.o

main.o : src/main.cp
	$(CC) $(CXXFLAGS) -c src/main.cpp
		
ssd.o : inc/ssd.h src/ssd.c
	$(CC) $(CXXFLAGS) -c src/ssd.c
		
io.o : inc/io.h src/io.c
	$(CC) $(CXXFLAGS) -c src/io.c

.PHONY: clean	all
clean:
	rm -f $(OBJS) main

main : main.o ssd.o io.o
	${CC} {OBJS} -o main
