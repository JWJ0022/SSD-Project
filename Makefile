CC = g++
OBJS = io.o main.o ssd.o testapp.o

main.o : src/main.cpp
	$(CC) -c src/main.cpp
		
ssd.o : inc/ssd.h src/ssd.cpp
	$(CC) -c src/ssd.cpp
		
io.o : inc/io.h src/io.cpp
	$(CC) -c src/io.cpp

testapp.o : test/testapp.h test/testapp.cpp
	$(CC) -c test/testapp.cpp

clean:
	rm -f $(OBJS) main

main : ${OBJS}
	${CC} ${OBJS} -o main
