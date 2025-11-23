CC = gcc
CFLAGS = -Wall -Werror

OBJS = wgrep.o

TARGET = wgrep

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

wgrep.o: wgrep.c
	$(CC) $(CFLAGS) -c wgrep.c

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
