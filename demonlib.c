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
char* compareCatalogs(char* sourcePath, char* targetPath, int threshold)
{
    DIR* sourceDir = opendir(sourcePath);
    DIR* targetDir = opendir(targetPath);
    struct dirent sourceStreamDirFile;
    struct dirent targetStreamDirFile;
    char* startDir;
    if(!(startDir = getcwd(NULL,0)))
    {
        perror("Error getcwd");
        exit(EXIT_FAILURE);
    }
    while((sourceStreamDirFile = readdir(sourceDir)))
    {
        if(sourceStreamDirFile->d_type != DT_DIR)
        {
            opendir(targetPath);
            while((targetStreamDirFile = readdir(targetDir)))
            {
                if(targetStreamDirFile->d_type != DT_DIR)
                {
                    char* sourceFilePath = pathToFile(sourcePath, sourceStreamDirFile->d_name);

                    if(!strcmp(sourceStreamDirFile->d_name, targetStreamDirFile->d_name))//znaleziony plik
                    {
                        char* targetFilePath = pathToFile(targetPath, targetStreamDirFile->d_name);
                        if(getLastModificationTime(sourceFilePath) != getLastModificationTime(targetFilePath))//sprawdz date edycji 
                        {
                            truncate(targetFilePath, 0); //usun zawartosc pliku
                            updateFile(sourceFilePath, targetFilePath, threshold); //zrob kopiowanie 
                            syslog(LOG_INFO, "File %s was updated", sourceFilePath);
                            break;
                        }
                    }
                    else//nie udalo sie znalezc pliku
                    {
                        char* targetFilePath = pathToFile(targetPath, targetStreamDirFile->d_name);
                        updateFile(sourceFilePath, targetFilePath, threshold); //utworz plik i skopiuj zawartosc
                        syslog(LOG_INFO, "File %s was created", targetFilePath);
                    }
                }
            }
            closedir(targetStreamDirFile);
        }
    }


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
    int size= getSize(char *sourcePath);
    if ( size > threshold)
    {
       char* map = (char*) mmap(0,size, PROT_READ, MAP_SHARED | MAP_FILE, sourceFile, 0)
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
               perror("Error while coping from %s to %s", sourcePath, targetPath);
               exit(EXIT_FAILURE);
           }
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
void clearCatalogs(char* sourcePath, char* targetPath, bool recurSync)
{
    struct dirent* file;
    DIR * path, *del;
    path = opendir(targetPath);
    while(( file = readdir (path)))
    {
        if((file->d_type)==DT_DIR)
        {
            if(recurSync)
            {
                if( !( strcmp(file->d_name, ".")== 0 || (file->d_name, "..")== 0))
                {
                    char* newPath = pathToFile(sourcePath, file->d_name);// tutaj ścieżka do danego pliku w source (tego pliku może nie być właśnie to będziemy sprawdzać)
                    delete(newPath,targetPath, recurSync);
                    char * pathToDelete = changeCatalogs(newPath, sourcePath, targetPath); //ścieżka do danego pliku w target
                    if(!(del=opendir(newPath))) 
                    {
                        remove(pathToDelete);
                        syslog(LOG_INFO, "Deleted catalog %s", pathToDelete);
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
            char* newPath = pathToFile(sourcePath, file->d_name);// tutaj ścieżka do danego pliku w source (tego pliku może nie być właśnie to będziemy sprawdzać)
            if(access(newPath,F_OK)== -1 )
            {
                char* pathToDelete = changeCatalogs(newPath, sourcePath, targetPath);; //tutaj ścieżka do pliku w target (ten plik jest w source ale nie ma go w source, dlatego go usuwamy) na razie takie komenty żeby wiedziec na szybko co trzeba napisać później zakomentuję cały kod ładnie po ang. 
                remove(pathToDelete);
                syslog(LOG_INFO, "Deleted file %s", pathToDelete);
            }
        }
    }
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
char* changeCatalogs(char* newPath, char* sourcePath, char* targetPath)
{
    char* path = newPath+strlen(sourcePath);
    char* outPath = malloc(strlen(targetPath)+strlen(path)+2);
    strcpy(outPath,targetPath);
    strcat(outPath,path);
    return outPath;
}