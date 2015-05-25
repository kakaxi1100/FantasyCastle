.SUFFIXES: .cpp .o
 
CC=g++
 
PARAM=-Wall -g
 
SRCS=pub.cpp \
	work.cpp \
	server.cpp \
	byteArray.cpp
 
OBJS=$(SRCS:.cpp=.o)
 
EXE=qqserver

all:$(OBJS)
	$(CC) -o $(EXE) $(OBJS) 
	@echo '---------Build Success !----------------'

.cpp.o: 
	$(CC) $(PARAM) -o $@ -c $<
		
.PHONY:clean clexe
 
clean:
	rm -f *.o
	rm -f *.core
	 
clexe:
	rm -f $(EXE)
