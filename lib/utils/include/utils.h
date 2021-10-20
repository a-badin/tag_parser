#ifndef UTILS_H
#define UTILS_H

#include "tag.h"
#include "error.h"

void init_attribute(attribute_t* attribute);
attribute_t* create_attribute();
void* free_attribute(attribute_t* attribute);

error_t set_attribute_name(attribute_t* attribute, const char* name);
error_t set_attribute_value(attribute_t* attribute, const char* value);


void init_tag(tag_t* tag);
tag_t* create_tag();
error_t add_attribute(tag_t* tag, const attribute_t* attribute);

void* free_tag(tag_t* tag);

error_t parse_tag_from_string(const char* str, tag_t* tag);

#endif // UTILS_H
