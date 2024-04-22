#include "logger.h"

Logger* makeLogger(const char *PATH)
{
	Logger* newLogger = (Logger*)malloc(sizeof(Logger));
	newLogger->file = fopen(PATH, "w");
	if (!newLogger->file)
	{
		perror("Could not open simulator report");
	}

	time_t currentTime;
    struct tm* localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    fprintf(newLogger->file, "Simulator report created at %s", asctime(localTime));
	return newLogger;
}

void logMessage(Logger* LOGGER, const char* MESSAGE)
{
	fprintf(LOGGER->file, "%s\n", MESSAGE);
	fflush(LOGGER->file);
}

void destroyLogger(Logger* LOGGER)
{
	fclose(LOGGER->file);
	free(LOGGER);
}