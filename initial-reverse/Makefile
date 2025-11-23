CC = gcc
CFLAGS = -Wall -Werror

OBJS = reverse.o string_vector.o

TARGET = reverse

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

reverse.o: reverse.c string_vector.h
	$(CC) $(CFLAGS) -c reverse.c

string_vector.o: string_vector.c string_vector.h
	$(CC) $(CFLAGS) -c string_vector.c

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
