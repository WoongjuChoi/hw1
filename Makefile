CC = gcc
TARGET_MAIN = myshell
TARGET_CHILD = child

$(TARGET_MAIN) : 
		$(CC) -o $(TARGET_MAIN) $(TARGET_MAIN).c && $(CC) -o $(TARGET_CHILD) $(TARGET_CHILD).c
		
clean	:
		rm $(TARGET_MAIN) && rm $(TARGET_CHILD)
				
start	:$(TARGET_MAIN)
		./$(TARGET_MAIN)

build	:
		make clean && make && make start