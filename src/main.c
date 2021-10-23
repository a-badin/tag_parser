#include <stdio.h>

#include "tag_parser.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
      fprintf(stderr, "Empty input\n");
      return -1;
    }

    tag_t tag;
    init_tag(&tag);

    tag_error_t error = parse_tag_from_string(argv[1], &tag);
    if (error != ERROR_OK)
    {
      fprintf(stderr, "Invalid input\n");
      return -1;
    }

    printf("<%s", tag.is_closed ? "/" : "");
    printf("%s\n", tag.name);
    for (unsigned long i = 0; i < tag.attributes_count; ++i)
    {
        const attribute_t* attribute = &tag.attributes[i];
        printf("  %s=\"%s\"", attribute->name, attribute->value);
    }
    printf("\n>\n");

    return 0;
}
