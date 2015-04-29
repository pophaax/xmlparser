CC = g++
CFLAGS = -g -pedantic -std=c++14
FILES_PARSER = src/xmlparser.cpp pugi/*.cpp
EXECUTABLE = parser
EXECUTABLE_LOG = log
SOURCE_LOG = src/xml_log.cpp pugi/*.cpp
HEADER_LOG = src/xml_log.h pugi/*.hpp
FILE_LOG = XML_log.o

all : $(SOURCE_LOG) $(HEADER_LOG)
	 $(CC) $(CFLAGS) $(SOURCE_LOG) -c -o $(FILE_LOG)

parser : $(FILES_PARSER)
	$(CC) $(CFLAGS) $(FILES_PARSER) -o $(EXECUTABLE) 

log : $(SOURCE_LOG)
	 $(CC) $(CFLAGS) $(SOURCE_LOG) -o $(EXECUTABLE_LOG) 