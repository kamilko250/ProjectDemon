#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

off_t GetSize(char* path);
mode_t GetChmod(char* path);
time_t GetLastModificationTime(char* path);
void LogHandler();
