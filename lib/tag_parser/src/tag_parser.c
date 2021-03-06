#include "tag_parser.h"

#include <stdlib.h>
#include <string.h>

#include "tag.h"
#include "attribute.h"

#include "utils.h"

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

static parser_state_t parse_start(char c)
{
    if(c != '<')
        return PARSER_STATE_ERROR;
    return PARSER_STATE_TAG_OPEN_CLOSE;
}

static int is_alpha_num(char c)
{
  int is_alpha = 'a' <= c && c <= 'z';
  int is_caps_alpha = 'A' <= c && c <= 'Z';
  int is_num = '0' <= c && c <= '9';

  return is_alpha || is_caps_alpha || is_num;
}

static parser_state_t parse_open_close(char c, unsigned long* pos, bool* is_closed_tag)
{
    if(c == '/')
        *is_closed_tag = true;
    else
        *pos -= 1;

    return PARSER_STATE_TAG_NAME;
}

static parser_state_t parse_tag_name(char c)
{
    if(is_alpha_num(c))
        return PARSER_STATE_TAG_NAME;

    return PARSER_STATE_TAG_END_OR_ATTRIBUTE;
}

static parser_state_t parse_end_or_attribute(char c)
{
    if(c == ' ') {
        return PARSER_STATE_TAG_ATTRIBUTE_NAME;
    } else if(c == '>')
        return PARSER_STATE_TAG_DONE;

    return PARSER_STATE_ERROR;
}

static parser_state_t parse_attribute_name(char c)
{
    if(is_alpha_num(c))
        return PARSER_STATE_TAG_ATTRIBUTE_NAME;
    else if (c == '=')
        return PARSER_STATE_TAG_ATTRIBUTE_VALUE_START;

    return PARSER_STATE_ERROR;
}

static parser_state_t parse_attribute_value_start(char c)
{
    if(c == '"')
        return PARSER_STATE_TAG_ATTRIBUTE_VALUE;

    return PARSER_STATE_ERROR;
}

static parser_state_t parse_attribute_value(char c)
{
    if(c == '"')
        return PARSER_STATE_TAG_END_OR_ATTRIBUTE;

    return PARSER_STATE_TAG_ATTRIBUTE_VALUE;
}

tag_error_t parse_tag_from_string(const char* str, tag_t* tag)
{
    if(str == NULL || tag == NULL)
        return ERROR_NULL_PTR_REFERENCE;
    
    bool is_closed_tag = false;

    unsigned long size = strlen(str);
    if(size == 0)
        return ERROR_EMPTY_STRING;

    parser_state_t state = PARSER_STATE_TAG_START;

    attribute_t tmp_attribute;
    init_attribute(&tmp_attribute);

    char* str_buffer = NULL;

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
                state = parse_tag_name(cur_char);
                if(state == PARSER_STATE_TAG_END_OR_ATTRIBUTE) {
                    copy_string(&str_buffer, str + buf_start, i - buf_start);
                    set_tag_name(tag, str_buffer);
                    i = i - 1;
                }
                break;
            case PARSER_STATE_TAG_END_OR_ATTRIBUTE:
                state = parse_end_or_attribute(cur_char);
                if(state == PARSER_STATE_TAG_ATTRIBUTE_NAME)
                    buf_start = i + 1;
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_NAME:
                state = parse_attribute_name(cur_char);
                if(state == PARSER_STATE_TAG_ATTRIBUTE_VALUE_START) {
                    copy_string(&str_buffer, str + buf_start, i - buf_start);
                    set_attribute_name(&tmp_attribute, str_buffer);
                }
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_VALUE_START:
                state = parse_attribute_value_start(cur_char);
                buf_start = i + 1;
                break;
            case PARSER_STATE_TAG_ATTRIBUTE_VALUE:
                state = parse_attribute_value(cur_char);
                if(state == PARSER_STATE_TAG_END_OR_ATTRIBUTE) {
                    copy_string(&str_buffer, str + buf_start, i - buf_start);
                    set_attribute_value(&tmp_attribute, str_buffer);
                    add_tag_attribute(tag, &tmp_attribute);
                }
                break;
            default:;
        }
        if(state == PARSER_STATE_ERROR) {
            free(str_buffer);
            clear_attribute(&tmp_attribute);
            return ERROR_PARSING_TAG;
        }
    }

    free(str_buffer);
    clear_attribute(&tmp_attribute);
    return ERROR_OK;
}
