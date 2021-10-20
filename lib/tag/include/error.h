#ifndef ERROR_H
#define ERROR_H
#include <stdbool.h>

typedef enum {
    ERROR_OK = 0,
    ERROR_MEMORY_ALLOCATION_ERROR,
    ERROR_NULL_PTR_REFERENCE
} error_t;

#endif // ERROR_H
