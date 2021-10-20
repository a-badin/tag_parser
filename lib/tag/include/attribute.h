#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include "errors.h"

typedef struct {
    char* name;
    char* value;
} attribute_t;

void init_attribute(attribute_t* attribute);
attribute_t* create_attribute();
attribute_t* free_attribute(attribute_t* attribute);

void clear_attribute(attribute_t* attribute);

error_t set_attribute_name(attribute_t* attribute, const char* name);
error_t set_attribute_value(attribute_t* attribute, const char* value);

#endif // ATTRIBUTE_H
