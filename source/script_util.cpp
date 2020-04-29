#include "script_util.hpp"

#include <cstdarg>
#include <cstdio>

void log_to_sd_out(const char *fmt, ...) 
{
    FILE* f = fopen("/output.log", "a");
    if(f == NULL)
        return;
    va_list myargs;
    va_start(myargs, fmt);
    vfprintf(f, fmt, myargs);
    va_end(myargs);
    fclose(f);
}
