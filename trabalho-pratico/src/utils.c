#include "utils.h"
#include <stdio.h>

bool utils_cents_para_string_em_euros(int64_t precoc, char *buf, size_t tam)
{
    int n = snprintf(buf, tam, "%" PRId64 ".%02" PRId64, precoc / 100, precoc % 100);

    if (n < 0)
        return false;

    if ((size_t)n >= tam)
        return false;

    return true;
}