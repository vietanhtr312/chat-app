#include "utils.h"

void log_message(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;
    char time_buffer[20];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Print the time before the log message
    fprintf(stdout, "[%s]  |  CONSOLE LOG  |  ", time_buffer);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");

    va_end(args);
}