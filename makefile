CC = gcc

Target = shell

MAIN_SOURCE = shell.c

all : $(TARGET)

$(TARGET):
	$(CC) -o $(TARGET) $(MAIN_SOURCE)

clean:
	rm -f $(TARGET)
