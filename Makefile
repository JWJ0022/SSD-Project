CC = g++
OBJS = io.o main.o ssd.o

main.o : src/main.cpp
	$(CC) -c src/main.cpp
		
ssd.o : inc/ssd.h src/ssd.cpp
	$(CC) -c src/ssd.cpp
		
io.o : inc/io.h src/io.cpp
	$(CC) -c src/io.cpp

clean:
	rm -f $(OBJS) main

main : ${OBJS}
	${CC} ${OBJS} -o main
