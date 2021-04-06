#include "demonlib.h"

off_t GetSize(char* path)
{   
    struct stat size;
    if(!stat(path, &size))
        return size.st_size;
    syslog(LOG_ERR, "Error while getting size, file: %s", path);
    exit(EXIT_FAILURE);
}
mode_t GetChmod(char* path)
{
    struct stat chmod;
    if(!stat(path, &mod))
        return chmod.st_mode; 
    syslog(LOG_ERR, "Error while getting chmod, file: %s", path);
    exit(EXIT_FAILURE);
}
time_t GetLastModificationTime(char* path)
{
    struct stat lastModTime;
    if(!stat(path, &lastModTime))
        return lastModTime.st_mtime;
    syslog(LOG_ERR, "Error while getting last modification time, file: %s", path);
    exit(EXIT_FAILURE);
}