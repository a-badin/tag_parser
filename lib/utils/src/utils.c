#include "utils.h"

#include <stdlib.h>
#include <string.h>

tag_error_t copy_string(char** dest, const char* src, unsigned long size)
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
