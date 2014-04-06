CC = g++
CFLAGS = -g -pedantic -std=c++11
FILES = src/*.cpp pugi/*.cpp
EXECUTABLE = parser

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(EXECUTABLE) 