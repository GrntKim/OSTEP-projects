#include "string_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_vector* init_vector() {
    string_vector* v = malloc(sizeof(string_vector));
    if (v == NULL) return NULL;

    v->arr = (char**)malloc(sizeof(char*) * INITIAL_CAPACITY);
    if (v->arr == NULL) {
        free(v);
        return NULL;
    }
    v->size = 0;
    v->capacity = INITIAL_CAPACITY;
    return v;
}

int push_back(string_vector* v, const char* src) {
    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * EXPAND_FACTOR;

        char** new_arr = realloc(v->arr, sizeof(char*) * new_capacity);
        if (new_arr == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        v->arr = new_arr;
        v->capacity = new_capacity;
    }

    size_t len = strlen(src) + 1;
    char* buffer = (char*)malloc(len);
    if (buffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    strcpy(buffer, src);
    v->arr[v->size] = buffer;
    v->size++;

    return 0;
}

void free_vector(string_vector* v) {
    if (v == NULL) return;

    for(size_t i = 0; i < v->size; i++)
        free(v->arr[i]);
    free(v->arr);
    free(v);
}
