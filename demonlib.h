#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <utime.h>
#include <fcntl.h>
#include <syslog.h>

off_t getSize(char* path);
mode_t getChmod(char* path);
time_t getLastModificationTime(char* path);
time_t getLastAccesTime(char* path);
void logHandler();
//compare and delete target
void clearCatalogs(char* sourcePath, char* targetPath);
//compare and fill target 
void refillCatalogs(char* sourcePath, char* targetPath, int threshold);
//updates content source->target 
void updateFile(char* sourcePath, char* targetPath,int threshold);
//sets time of last modification source->target 
int updateLastModFileTime(char* sourcePath, char* targetPath);
int updateFileChmod(char* sourcePath, char* targetPath);
