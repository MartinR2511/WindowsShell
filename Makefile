CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11

all: main

main: main.cpp commands.cpp
	$(CC) $(CFLAGS) -o RubyShell main.cpp commands.cpp

clean:
	rm -f main