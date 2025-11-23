CC = gcc
CFLAGS = -Wall -Werror

OBJS = wzip.o

TARGET = wzip

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

wzip.o: wzip.c
	$(CC) $(CFLAGS) -c wzip.c

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
