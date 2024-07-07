CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11

all: main

main: main.cpp
	$(CC) $(CFLAGS) -o RubyShell main.cpp

clean:
	rm -f main