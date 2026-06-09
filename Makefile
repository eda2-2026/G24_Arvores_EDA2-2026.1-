CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cacador
SRCS   = src/main.c src/rbtree.c

all: $(TARGET)

$(TARGET): $(SRCS) src/rbtree.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
