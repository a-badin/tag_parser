#ifndef TAG_H
#define TAG_H

#include <stdbool.h>

#include "attribute.h"
#include "error.h"

typedef struct {
    char* name;
    bool is_closed;
    attribute_t* attributes;
    unsigned attributes_count;
} tag_t;


void init_tag(tag_t* tag);
tag_t* create_tag();
tag_t* free_tag(tag_t* tag);
void clear_tag(tag_t* tag);

error_t set_tag_name(tag_t* tag, const char* name);
error_t add_tag_attribute(tag_t* tag, const attribute_t* attribute);


#endif // TAG_H
