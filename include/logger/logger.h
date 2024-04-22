#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
	FILE* file;
} Logger;

Logger* makeLogger(const char *PATH);

void logMessage(Logger* LOGGER, const char* MESSAGE);

void destroyLogger(Logger* LOGGER);
#endif //LOGGER_H