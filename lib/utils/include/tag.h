#ifndef TAG_H
#define TAG_H
#include <stdbool.h>

typedef struct {
    char* name;
    char* value;
} attribute_t;

typedef struct {
    char* name;
    bool is_closed;
    attribute_t* attributes;
    unsigned attributes_count;
} tag_t;

#endif // TAG_H
