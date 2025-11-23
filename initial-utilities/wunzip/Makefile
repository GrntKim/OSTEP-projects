CC = gcc
CFLAGS = -Wall -Werror

OBJS = wunzip.o

TARGET = wunzip

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

wunzip.o: wunzip.c
	$(CC) $(CFLAGS) -c wunzip.c

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
