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
        return (time_t)lastModTime.st_mtim.tv_sec;
    syslog(LOG_ERR, "Error while getting last modification time, file: %s", path);
    exit(EXIT_FAILURE);
}
time_t getLastAccesTime(char* path)
{
    struct  stat lastAccesTime;
    if(!stat(path, &lastAccesTime))
        return (time_t)lastAccesTime.st_atim.tv_sec;
    syslog(LOG_ERR, "Error while getting last access time, file %s", path);
    exit(EXIT_FAILURE);   
}
void logHandler()
{
    syslog(LOG_INFO, "Demon woke up - SIGUSR1");
}
bool isFileUpToDate(char* sourceFilePath, char* targetFilePath)
{
    if(getLastModificationTime(sourceFilePath) == getLastModificationTime(targetFilePath))
        return true;
    else
        return false;
    
}
bool compareFiles(char* fileNameSource, char* fileNameTarget, char* sourceFilePath, char* targetFilePath, int threshold)
{
    if(!strcmp(fileNameTarget, fileNameSource))
    {
        if(!isFileUpToDate(sourceFilePath, targetFilePath))
        {
            truncate(targetFilePath, 0); 
            //updateFile(sourceFilePath, targetFilePath, threshold);
            syslog(LOG_INFO, "File %s was updated\n", sourceFilePath);
        }
        return true;
    }
    return false;
}
void compareCatalogs(char* sourcePath, char* targetPath, int threshold, bool recurSync)
{
    DIR* sourceDir = opendir(sourcePath);
    DIR* targetDir;
    struct dirent* sourceStreamDirFile;
    struct dirent* targetStreamDirFile;
    
    while((sourceStreamDirFile = readdir(sourceDir)))
    {
        if(sourceStreamDirFile->d_type != DT_DIR)
        {
            char* fileNameSource = sourceStreamDirFile->d_name;
            printf("petla zewnetrzna - source: %s\n",fileNameSource);
            targetDir = opendir(targetPath);
            do
            {
                targetStreamDirFile = readdir(targetDir);
                if(targetStreamDirFile)//znaleziono plik w folderze
                {
                    char* fileNameTarget = targetStreamDirFile->d_name;
                    unsigned char fileType = targetStreamDirFile->d_type;
                    printf("petlwa wewnetrzna - target: %s\n", fileNameTarget);
                    if(fileType != DT_DIR)
                    {
                        printf("typ pliku zgodny\n");
                        char* sourceFilePath = pathToFile(sourcePath, fileNameSource);
                        char* targetFilePath = pathToFile(targetPath, fileNameTarget);
                        
                        if(compareFiles(fileNameSource, fileNameTarget, sourceFilePath, targetFilePath,  threshold))
                        {
                            printf("plik %s zsynchronizowany\n", sourceFilePath);
                            break;
                        }
                        printf("nie odpowiedni plik\n");
                    }
                }
                else//folder jest pusty
                {
                    printf("nic nie znaleziono\n");
                    char* sourceFilePath = pathToFile(sourcePath, fileNameSource);
                    char* targetFilePath = pathToFile(targetPath, fileNameSource);
                    updateFile(sourceFilePath, targetFilePath, threshold);
                    break;
                }
            }while(true);
            closedir(targetDir);
        }
    }
    printf("wszystkie pliki zsynchronizowane\n");
    closedir(sourceDir);
}
void updateFile(char* sourcePath, char* targetPath, int threshold)
{
    int sourceFile;
    int targetFile; 
    if(sourceFile = open(sourcePath, O_RDONLY))
    {
        syslog(LOG_ERR, "Error while opening file %s", sourcePath);
    }
    if(targetFile = open(targetPath, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU))
    {
        syslog(LOG_ERR, "Error while opening file %s", targetPath);
    }

    char* bufor[32];
    ssize_t readSourceState;
    ssize_t writeTargetState;
    int size = getSize (sourcePath);
    if (size > threshold)
    {
       char* map = (char*) mmap(0,size, PROT_READ, MAP_SHARED | MAP_FILE, sourceFile, 0);
       write(targetFile, map, size);
       munmap(map, size);
    }
    else
    {
       while((readSourceState = read(sourceFile, bufor, sizeof(bufor)))>0)
       {
           writeTargetState = write(targetFile, bufor, readSourceState);
           if(readSourceState != writeTargetState)
           {
               syslog(LOG_ERR,"Error while coping from %s to %s",sourcePath, targetPath);
               exit(EXIT_FAILURE);
           }
       }
    }
    close(sourceFile);
    close(targetFile);

    updateFileChmod(sourcePath, targetPath);
    updateLastModFileTime(sourcePath, targetPath);
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
void clearCatalogs(char* sourcePath, char* targetPath,char* currentFile ,bool recurSync)
{
struct dirent* file;
    DIR * path, *del;
    path = opendir(currentFile);
    while(( file = readdir (path)))
    {
        if((file->d_type)==DT_DIR)
        {
            if(recurSync)
            {
               if( !( strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0))
               {
               char* newPath = pathToFile(currentFile, file->d_name);
               clearCatalogs(sourcePath, targetPath, newPath,"1");
               char * pathToDelete = changeCatalogs(newPath, sourcePath);
               if(!(del=opendir(pathToDelete))) 
                    {
                        remove(newPath);
                        syslog(LOG_INFO, "Deleted catalog %s", newPath);
                    }
                    else
                    {
                        closedir(del);
                    }
               }
            }
        }
        else
        {
            char* newPath = pathToFile(currentFile, file->d_name);
            char* pathToDelete = changeCatalogs(newPath, sourcePath);
            if(access(pathToDelete,F_OK)== -1 )
            {
                remove(newPath);
                syslog(LOG_INFO, "Deleted file %s", pathToDelete);
            }
        }
     }
     closedir(path);
}

char* pathToFile(char* sourcePath, char* file)
{
    char* newPath= malloc(strlen(sourcePath)+2+strlen(file));
    strcpy(newPath,sourcePath);
    strcat(newPath,"/");
    strcat(newPath, file);
    newPath[strlen(sourcePath)+1+strlen(file)]='\0';
    return newPath;
}

char* changeCatalogs(char* newPath, char* sourcePath)
{
    char* path = newPath+strlen(sourcePath);
    char* outPath = malloc(strlen(sourcePath)+strlen(path)+2);
    strcpy(outPath,sourcePath);
    strcat(outPath,path);
    return outPath;
}
