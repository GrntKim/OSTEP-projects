#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 8
#define EXPAND_FACTOR    2

typedef struct {
    char** arr;
    size_t size;
    size_t capacity;
} string_vector;

string_vector* init_vector();
int push_back(string_vector* v, const char* src);
void free_vector(string_vector* v);

#endif
