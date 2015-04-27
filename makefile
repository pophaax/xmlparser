CC = g++
CFLAGS = -g -pedantic -std=c++14
FILES_PARSER = src/xmlparser.cpp pugi/*.cpp
EXECUTABLE = parser
EXECUTABLE_LOG = log
FILES_LOG = src/xml_log.cpp pugi/*.cpp
FILE_LOG = XML_log.o

all: $(FILES_LOG)
	 $(CC) $(CFLAGS) $(FILES_LOG) -o $(FILE_LOG)

parser: $(FILES_PARSER)
	$(CC) $(CFLAGS) $(FILES_PARSER) -o $(EXECUTABLE) 

log: $(FILES_LOG)
	 $(CC) $(CFLAGS) $(FILES_LOG) -o $(EXECUTABLE_LOG) 