CC = gcc

TARGET = 32163740hw1

MAIN_SOURCE = 32163740.c

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) $(MAIN_SOURCE)

clean:
	rm -f $(TARGET)