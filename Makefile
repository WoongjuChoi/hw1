CC = gcc
TARGET = child
$(TARGET) : 
		$(CC) -o $(TARGET) $(TARGET).c
		
clean	:
		rm $(TARGET)
				
complie	:
		make
		
start	:$(TARGET)
		./$(TARGET)