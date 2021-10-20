#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "error.h"

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

static void deinit_attribute(attribute_t* attribute)
{
    if(attribute == NULL) return;
    free(attribute->name);
    free(attribute->value);
}

void* free_attribute(attribute_t* attribute)
{
    deinit_attribute(attribute);
    free(attribute);
    return NULL;
}

static error_t copy_string(char** dest, const char* src, unsigned long size)
{
    if(src == NULL || dest == NULL)
        return ERROR_NULL_PTR_REFERENCE;

    char* buf = realloc(*dest, size + 1);
    if(buf == NULL)
        return ERROR_MEMORY_ALLOCATION_ERROR;

    memcpy(buf, src, size);
    buf[size] = '\0';
    *dest = buf;

    return ERROR_OK;
}

error_t set_attribute_name(attribute_t* attribute, const char* name)
{
    if(attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    return copy_string(&attribute->name, name, strlen(name));
}

error_t set_attribute_value(attribute_t* attribute, const char* value)
{
    if(attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    return copy_string(&attribute->value, value, strlen(value));
}

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

void deinit_tag(tag_t* tag)
{
    if(tag == NULL) return;
    for(int i = 0; i < tag->attributes_count; ++i) {
        deinit_attribute(&tag->attributes[i]);
    }
    free(tag->attributes);
}

void* free_tag(tag_t* tag)
{
    deinit_tag(tag);
    free(tag);
    return NULL;
}

error_t add_attribute(tag_t* tag, const attribute_t* attribute)
{
    if(tag == NULL || attribute == NULL)
        return ERROR_NULL_PTR_REFERENCE;

    int size = tag->attributes_count; 
    attribute_t* buf = realloc(tag->attributes, sizeof(attribute_t) * size * 2 + 1);
    if(buf == NULL)
        return ERROR_MEMORY_ALLOCATION_ERROR;

    tag->attributes = buf;
    set_attribute_name(&buf[size], attribute->name);
    set_attribute_value(&buf[size], attribute->value);
    tag->attributes_count += 1;

    return ERROR_OK;
}

typedef enum {
  PARSER_STATE_TAG_START,
  PARSER_STATE_TAG_OPEN_CLOSE,
  PARSER_STATE_TAG_NAME,
  PARSER_STATE_TAG_END_OR_ATTRIBUTE,
  PARSER_STATE_TAG_ATTRIBUTE_NAME,
  PARSER_STATE_TAG_ATTRIBUTE_VALUE_START,
  PARSER_STATE_TAG_ATTRIBUTE_VALUE,
  PARSER_STATE_TAG_DONE,
  PARSER_STATE_ERROR
} parser_state_t;

parser_state_t parse_start(char c)
{
    if(c != '<')
        return PARSER_STATE_ERROR;
    return PARSER_STATE_TAG_OPEN_CLOSE;
}

parser_state_t parse_open_close(char c, unsigned long* pos, bool* is_closed_tag)
{
    if(c == '/')
        *is_closed_tag = true;
    else
        *pos -= 1;
    return PARSER_STATE_TAG_NAME;
}

parser_state_t parse_tag_name(char c, const char* str, unsigned long size)
{
    if('a' <= c && c <= 'z' || '0' <= c && c <= '9' || c == '-')
        return PARSER_STATE_TAG_NAME;

    return PARSER_STATE_TAG_END_OR_ATTRIBUTE;
}

parser_state_t parse_end_or_attribute(char c)
{
    if(c == ' ') {
        return PARSER_STATE_TAG_ATTRIBUTE_NAME;
    } else if(c == '>')
        return PARSER_STATE_TAG_DONE;

    return PARSER_STATE_ERROR;
}

parser_state_t parse_attribute_name(char c)
{
    if('a' <= c && c <= 'z' || '0' <= c && c <= '9' || c == '-')
        return PARSER_STATE_TAG_ATTRIBUTE_NAME;
    else if (c == '=')
        return PARSER_STATE_TAG_ATTRIBUTE_VALUE_START;

    return PARSER_STATE_ERROR;
}

parser_state_t parse_attribute_value_start(char c)
{
    if(c == '"')
        return PARSER_STATE_TAG_ATTRIBUTE_VALUE;

    return PARSER_STATE_ERROR;
}

parser_state_t parse_attribute_value(char c)
{
    if(c == '"')
        return PARSER_STATE_TAG_END_OR_ATTRIBUTE;

    return PARSER_STATE_TAG_ATTRIBUTE_VALUE;
}

error_t parse_tag_from_string(const char* str, tag_t* tag)
{
    if(str == NULL || tag == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    bool is_closed_tag = false;
    unsigned long size = strlen(str);
    if(size == 0)
        return ERROR_NULL_PTR_REFERENCE;

    printf("'%s'\n", str);
    parser_state_t state = PARSER_STATE_TAG_START;

    attribute_t tmp_attribute = {};

    unsigned long buf_start = 0;
    for(unsigned long i = 0; i < size; ++i)
    {
        char cur_char = str[i];
        switch(state) {
            case PARSER_STATE_TAG_START:
                state = parse_start(cur_char);
                break;
            case PARSER_STATE_TAG_OPEN_CLOSE:
                state = parse_open_close(cur_char, &i, &is_closed_tag);
                buf_start = i + 1;
                break;
            case PARSER_STATE_TAG_NAME:
                state = parse_tag_name(cur_char, str + buf_start, i - buf_start);
                if(state == PARSER_STATE_TAG_END_OR_ATTRIBUTE) {
                    copy_string(&tag->name, str + buf_start, i - buf_start);
                    i = i - 1;
                }
                break;
            case PARSER_STATE_TAG_END_OR_ATTRIBUTE:
                state = parse_end_or_attribute(cur_char);
                if(state == PARSER_STATE_TAG_ATTRIBUTE_NAME)
                    buf_start = i + 1;
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_NAME:
                printf("%lu:'%c'%d\n", i, cur_char, state);
                state = parse_attribute_name(cur_char);
                if(state == PARSER_STATE_TAG_ATTRIBUTE_VALUE_START)
                    copy_string(&tmp_attribute.name, str + buf_start, i - buf_start);
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_VALUE_START:
                state = parse_attribute_value_start(cur_char);
                buf_start = i + 1;
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_VALUE:
                state = parse_attribute_value(cur_char);
                if(state == PARSER_STATE_TAG_END_OR_ATTRIBUTE) {
                    copy_string(&tmp_attribute.value, str + buf_start, i - buf_start);
                    add_attribute(tag, &tmp_attribute);
                }
                break;
            default:;
        }
        if(state == PARSER_STATE_ERROR) {
            printf("Error on %lu\n", i);
            return ERROR_PARSING_TAG;
        }
    }

    return ERROR_OK;
}
