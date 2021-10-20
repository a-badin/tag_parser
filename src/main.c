#include <stdio.h>
#include "tag.h"
#include "utils.h"

int main()
{
    tag_t tag = {};
    error_t error = parse_tag_from_string("</home at=\"value\" width=\"986\">", &tag);
    printf("<%s", tag.is_closed ? "/" : "");
    printf("%s", tag.name);
    for (int i = 0; i < tag.attributes_count; ++i)
    {
        const attribute_t* attribute = &tag.attributes[i];
        printf(" %s=\"%s\"", attribute->name, attribute->value);
    }
    printf(">\n");

    return 0;
}
