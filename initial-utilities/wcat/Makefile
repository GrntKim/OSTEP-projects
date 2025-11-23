CC = gcc
CFLAGS = -Wall -Werror

OBJS = wcat.o

TARGET = wcat

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

wcat.o: wcat.c
	$(CC) $(CFLAGS) -c wcat.c

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
