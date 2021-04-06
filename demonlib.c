#include "demonlib.h"

off_t getSize(char* path)
{   
    struct stat size;
    if(!stat(path, &size))
        return size.st_size;
    syslog(LOG_ERR, "Error while getting size, file: %s", path);
    exit(EXIT_FAILURE);
}
mode_t getChmod(char* path)
{
    struct stat mod;
    if(!stat(path, &mod))
        return mod.st_mode; 
    syslog(LOG_ERR, "Error while getting chmod, file: %s", path);
    exit(EXIT_FAILURE);
}
time_t getLastModificationTime(char* path)
{
    struct stat lastModTime;
    if(!stat(path, &lastModTime))
        return lastModTime.st_mtim;
    syslog(LOG_ERR, "Error while getting last modification time, file: %s", path);
    exit(EXIT_FAILURE);
}
time_t getLastAccesTime(char* path)
{
    struct  stat lastAccesTime;
    if(!stat(path, &lastAccesTime))
        return lastAccesTime.st_atim;
    syslog(LOG_ERR, "Error while getting last access time, file %s", path);
    exit(EXIT_FAILURE);   
}
void logHandler()
{
    syslog(LOG_INFO, "Demon woke up - SIGUSR1");
}
char* compareCatalogs(char* sourcePath, char* targetPath)
{




}
void updateFile(char* sourcePath, char* targetPath)
{
    int sourceFile;
    int targetFile; 
    if(sourceFile = open(sourcePath, O_RDONLY))
    {
        syslog(LOG_ERR, "Error while opening file %s", sourcePath);
    }
    if(sourceFile = open(targetPath, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU))
    {
        syslog(LOG_ERR, "Error while opening file %s", targetPath);
    }

    char* bufor[32];
    ssize_t readSourceState;
    ssize_t writeTargetState;

    while((readSourceState = read(sourceFile, bufor, sizeof(bufor)))>0)
    {
        writeTargetState = write(targetFile, bufor, readSourceState);
        if(readSourceState != writeTargetState)
        {
            perror("Erorr while coping from %s to %s", sourcePath, targetPath);
            exit(EXIT_FAILURE);
        }
    }
    close(sourceFile);
    close(targetFile);

    updateFileChmod(sourcePath, targetFile);
    updateLastModFileTime(sourceFile, targetFile);
    syslog(LOG_INFO, "%s was copied", sourcePath);
}
int updateFileChmod(char* sourcePath, char* targetPath)
{
    mode_t sourceChmod = getChmod(sourcePath);
    if(!chmod(sourcePath, sourceChmod)) 
    {
        syslog(LOG_ERR, "Error while changing chmod, file: %s", targetPath);
        exit(EXIT_FAILURE);
    }
}
int updateLastModFileTime(char* sourcePath, char* targetPath)
{
    struct utimbuf time;
    time.actime = getLastAccesTime(sourcePath);
    time.modtime = getLastModificationTime(sourcePath);
    if(!utime(targetPath, &time))
    {
        syslog(LOG_ERR, "Error while modifing time of last modification, file: %s", targetPath);
        exit(EXIT_FAILURE);
    }
}