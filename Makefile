TARGET_PROGRAM = chat
COMPILER = gcc

#ensure verbose output
CCFLAGS = -Wall -std=c11
LDFLAGS = -lrt

$(TARGET_PROGRAM) : chat.o
	$(COMPILER) -o $(TARGET_PROGRAM) server.o

chat.o :
	$(COMPILER) -c server.c $(CCFLAGS)

clean :
	rm -f *.o $(TARGET_PROGRAM)

debug : CCFLAGS += -DDEBUG -g
debug : $(TARGET_PROGRAM)
