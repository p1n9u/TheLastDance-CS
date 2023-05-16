.PHONY: all hanoi clean

CC = gcc

OBJS = main.o get.o move.o
INCS = -I./inc
LIBS = -lHanoi
LIB_DIRS = -L./lib -Wl,-rpath,./lib


all: hanoi

hanoi: lib main.o
	$(CC) -o $@ main.o $(LIB_DIRS) $(LIBS) $(INCS)

lib:
	mkdir -p lib
	$(CC) -fPIC -c get.c move.c $(INCS)
	$(CC) -shared -o ./lib/libHanoi.so get.o move.o $(INCS)

clean:
	rm $(OBJS) hanoi
	rm -rf lib