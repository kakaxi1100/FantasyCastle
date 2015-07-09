.SUFFIXES: .cpp .o
 
CC=g++510
 
PARAM=-Wall -g

CFLAG=-std=c++11
 
SRCS=pub.cpp \
	work.cpp \
	server.cpp \
	byteArray.cpp \
	clientsql.cpp \
	clientinfo.cpp
 
OBJS=$(SRCS:.cpp=.o)
 
LIB=-lmysqlclient \
 
EXE=qqserver

all:$(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIB)
	@echo '---------Build Success !----------------'

.cpp.o: 
	$(CC) $(PARAM) -o $@ -c $< $(CFLAG)
		
.PHONY:clean clexe
 
clean:
	rm -f *.o
	rm -f *.core
	 
clexe:
	rm -f $(EXE)
