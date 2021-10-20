#ifndef TAG_PARSER_H
#define TAG_PARSER_H

#include "tag.h"

tag_error_t parse_tag_from_string(const char* str, tag_t* tag);

#endif // TAG_PARSER_H
