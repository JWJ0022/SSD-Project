CC = g++
OBJS = io.o ssd.o main.o

main.o : src/main.cpp
	$(CC) $(CXXFLAGS) -c src/main.cpp
		
ssd.o : inc/ssd.h src/ssd.cpp
	$(CC) $(CXXFLAGS) -c src/ssd.cpp
		
io.o : inc/io.h src/io.cpp
	$(CC) $(CXXFLAGS) -c src/io.cpp

clean:
	rm -f $(OBJS) main

main : ${OBJS}
	${CC} ${OBJS} -o main
