.PHONY: all clean mysort

all: main.o functions.o
	g++ -Wall -Wextra main.o functions.o -o start
	./start

functions.o: functions.cpp	
	g++ -Wall -Wextra -c functions.cpp -o functions.o

sort.o: sort.cpp
	g++ -Wall -Wextra -c sort.cpp -o sort.o

main.o: main.cpp
	g++ -Wall -Wextra -c main.cpp -o main.o

mysort: functions.o sort.o
	g++ -Wall -Wextra -D MYSORT -c main.cpp -o main.o
	g++ -Wall -Wextra main.o functions.o sort.o -o start
	./start

clean:
	rm functions.o main.o start sort.o