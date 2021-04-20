#include <sys/types.h>
#include "demonlib.h"


int main(int argc, char** argv)
{
    openlog("PROJEKT", LOG_PID|LOG_CONS, LOG_USER);
    char* sourcePath = NULL;
    char* targetPath = NULL;
    bool recurSync = false;
    int threshold = 4096;
    int sleepTimeSeconds = 5 * 60;
    struct stat file;
    if(argc<5)
    {
        printf("Too few args\n");
        syslog(LOG_ERR, "Too few arguments");
        exit(EXIT_FAILURE);
    }


    pid_t ProcessID, SessionID;

    ProcessID = fork();
    printf("ProcessID %d\n", ProcessID);
    if(ProcessID<0)
    {
        syslog(LOG_ERR, "Wrong child ID");
        printf("Wrong child ID");
        exit(EXIT_FAILURE);
    }
    else if(ProcessID>0)
    {
        //exit(EXIT_SUCCESS);
    }

    umask(0);

    SessionID = setsid();
    printf("SessionID %d\n", SessionID);
    if(SessionID<0)
    {
        syslog(LOG_ERR, "Wrong SessionID");
        printf("Wrong SessionID");
        exit(EXIT_FAILURE);
    }
    printf("Przed whilem");
    int parameter;
    while((parameter = getopt(argc, argv, "i:o:t:y:r")) != -1)
    {
        switch(parameter)
        {
            case 'i': 
            {   
                char* check = optarg;
                if(stat(check, &file) == 0)
                {
                    if(file.st_mode &S_IFDIR)
                    {
                        sourcePath = optarg;
                    }
                    else
                    {
                        syslog(LOG_ERR, "Not a source folder");
                        printf("Not a source folder");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            }
            case 'o':
            {
               char* check = optarg;
                if(stat(check, &file) == 0)
                {
                    if(file.st_mode &S_IFDIR)
                    {
                        targetPath = optarg;
                    }
                    else
                    {
                        syslog(LOG_ERR, "Not a target folder");
                        printf("Not a target folder");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            case 't':
            {
                sleepTimeSeconds = atoi(optarg);
                break;
            }
            case 'r':
            {
                recurSync = true;
                break;
            }
            case 'y':
            {
                threshold = atoi(optarg);
                break;
            }
        }
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    syslog(LOG_INFO, "Synchro-Demon");
    printf("Synchro-Demon");
    if(signal(SIGUSR1, logHandler)==SIG_ERR)
    {
        syslog(LOG_ERR, "Signal Error!");
        printf("Signal Error");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        clearCatalogs(sourcePath, targetPath, targetPath, recurSync);
        compareCatalogs(sourcePath, targetPath, threshold, recurSync);
        syslog(LOG_INFO, "Demon has gone to sleep");
        printf( "Demon has gone to sleep");
        if((sleep(sleepTimeSeconds))==0)
        {
            syslog(LOG_INFO, "Demon awake");
            printf("Demon awake");
        }
    }

    closelog();
    exit(EXIT_SUCCESS);
    return 0;

} 
