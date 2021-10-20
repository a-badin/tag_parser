#include "tag.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "attribute.h"
#include "error.h"

void init_tag(tag_t* tag)
{
    if(tag == NULL)
        return;

    tag->attributes = NULL;
    tag->name = NULL;
    tag->attributes_count = 0;
}

tag_t* create_tag()
{
    tag_t* tag = (tag_t*)malloc(sizeof(tag_t));
    init_tag(tag);
    return tag;
}

void clear_tag(tag_t* tag)
{
    if(tag == NULL)
        return;

    for(int i = 0; i < tag->attributes_count; ++i) {
        clear_attribute(&tag->attributes[i]);
    }
    free(tag->attributes);
}

tag_t* free_tag(tag_t* tag)
{
    clear_tag(tag);
    free(tag);
    return NULL;
}

error_t add_tag_attribute(tag_t* tag, const attribute_t* attribute)
{
    if(tag == NULL || attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;

    int size = tag->attributes_count; 
    attribute_t* buf = realloc(tag->attributes, sizeof(attribute_t) * size * 2 + 1);
    if(buf == NULL)
        return ERROR_MEMORY_ALLOCATION_ERROR;

    tag->attributes = buf;
    init_attribute(&tag->attributes[size]);
    set_attribute_name(&tag->attributes[size], attribute->name);
    set_attribute_value(&tag->attributes[size], attribute->value);
    tag->attributes_count += 1;

    return ERROR_OK;
}

error_t set_tag_name(tag_t* tag, const char* name)
{
    if(tag == NULL || name == NULL)
        return ERROR_NULL_PTR_REFERENCE;

    return copy_string(&tag->name, name, strlen(name));
}
