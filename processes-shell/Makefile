CC = gcc
CFLAGS = -Wall -Werror

OBJS = wish.o

TARGET = wish

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

wish.o: wish.c
	$(CC) $(CFLAGS) -c wish.c


.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
