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
        syslog(LOG_ERR, "Too few arguments");
        exit(EXIT_FAILURE);
    }


    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        syslog(LOG_ERR, "Wrong child ID");
        exit(EXIT_FAILURE);
    }
    else if(pid != 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    if(setsid() == -1)
    {
        syslog(LOG_ERR, "Wrong SessionID");
        exit(EXIT_FAILURE);
    }
    if(chdir("/") == -1)
    {
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 256; i++)
    {
        close(i);
    }

    open ("/dev/null", O_RDWR); /* stdin */
    dup (0); /* stdout */
    dup (0);


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
    if(signal(SIGUSR1, logHandler)==SIG_ERR)
    {
        syslog(LOG_ERR, "Signal Error!");
        //printf("Signal Error");
        exit(EXIT_FAILURE);
    }
    int time = sleepTimeSeconds;
    while(1)
    {
        clearCatalogs(sourcePath, targetPath, targetPath, recurSync);
        compareCatalogs(sourcePath, targetPath, threshold, recurSync);
        syslog(LOG_INFO, "Demon has gone to sleep");
        while((time = sleep(time))==0)
        {
        }
            syslog(LOG_INFO, "Demon awake");
        time = sleepTimeSeconds;
    }

    closelog();
    exit(EXIT_SUCCESS);
    return 0;

} 
