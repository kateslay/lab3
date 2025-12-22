CC = gcc
CFLAGS = -Wall -Wextra
TARGET = program.exe
OBJS = main.o queue.o sortselec.o sortquick.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c queue.h sortselec.h sortquick.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

sortselec.o: sortselec.c sortselec.h queue.h
	$(CC) $(CFLAGS) -c sortselec.c

sortquick.o: sortquick.c sortquick.h queue.h
	$(CC) $(CFLAGS) -c sortquick.c

clean:
	del /Q *.o $(TARGET) 2>nul || true

rebuild: clean all

run: $(TARGET)
	$(TARGET)