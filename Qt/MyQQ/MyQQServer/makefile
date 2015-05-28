.SUFFIXES: .cpp .o
 
CC=g++
 
PARAM=-Wall -g
 
SRCS=pub.cpp \
	work.cpp \
	server.cpp \
	byteArray.cpp \
	clientsql.cpp
 
OBJS=$(SRCS:.cpp=.o)
 
LIB=-lmysqlclient \
 
EXE=qqserver

all:$(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIB)
	@echo '---------Build Success !----------------'

.cpp.o: 
	$(CC) $(PARAM) -o $@ -c $<
		
.PHONY:clean clexe
 
clean:
	rm -f *.o
	rm -f *.core
	 
clexe:
	rm -f $(EXE)
