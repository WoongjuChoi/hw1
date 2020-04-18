CC = gcc
CFLAGS = -W -WALL
TARGET = Makefileshell

$(TARGET) : hw1_32163215shell.o
	$(CC) $(CFLAGS) -o $(TARGET) hw1_32163215shell.o

clean :
	rm *.o hw1_32163215shell.o
