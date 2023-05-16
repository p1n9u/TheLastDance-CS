CC = gcc
CFLAGS = -g -c

OBJS = main.o fct.o wrt.o
INCS = -I../spl05_02_large_program

TARGET = pgm

.SUFFIXES : .c .o

.c.o:
	$(CC) $(CFLAGS) $< -o $@ $(INCS)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(INCS)

clean:
	rm $(OBJS) $(TARGET)