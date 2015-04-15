CC = g++
CFLAGS = -g -pedantic -std=c++14
FILES = src/*.cpp pugi/*.cpp
EXECUTABLE = parser

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(EXECUTABLE) 

FILES_LOG = src/xml_log.cpp pugi/*.cpp
EXECUTABLE_LOG = log

log: $(FILES_LOG)
	 $(CC) $(CFLAGS) $(FILES_LOG) -o $(EXECUTABLE_LOG) 