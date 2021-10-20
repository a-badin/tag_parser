#include "attribute.h"

#include <stdlib.h>
#include <string.h>

#include "utils.h"

void init_attribute(attribute_t* attribute)
{
    if(attribute == NULL)
        return;

    attribute->name = NULL;
    attribute->value = NULL;
}

attribute_t* create_attribute()
{
    attribute_t* attribute = (attribute_t*)malloc(sizeof(attribute_t));
    init_attribute(attribute);
    return attribute;
}

void clear_attribute(attribute_t* attribute)
{
    if(attribute == NULL)
        return;

    free(attribute->name);
    attribute->name = NULL;
    free(attribute->value);
    attribute->value = NULL;
}

attribute_t* free_attribute(attribute_t* attribute)
{
    clear_attribute(attribute);
    free(attribute);
    return NULL;
}

tag_error_t set_attribute_name(attribute_t* attribute, const char* name)
{
    if(attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    return copy_string(&attribute->name, name, strlen(name));
}

tag_error_t set_attribute_value(attribute_t* attribute, const char* value)
{
    if(attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    return copy_string(&attribute->value, value, strlen(value));
}

