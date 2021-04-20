/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>*/
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
    if(argc<5)
    {
        printf("Too few args\n");
        syslog(LOG_ERR, "Too few arguments");
        exit(EXIT_FAILURE);
    }


    pid_t ProcessID, SessionID;

    // pid_t itd...





    int parameter;
    while((parameter = getopt(argc, argv, "i:o:t:y:r")) != -1)
    {
        switch(parameter)
        {
            case 'i': 
            {   
                sourcePath = optarg;
                //sprawdzenie sciezki
                break;
            }
            case 'o':
            {
                targetPath = optarg;
                //sprawdzenie sciezki
                break;
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
    if(signal(SIGUSR1, LogHandler())==SIG_ERR)
    {
        syslog(LOG_ERR, "Signal Error!");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        clearCatalogs(sourcePath, targetPath, targetPath, recurSync);
        compareCatalogs(sourcePath, targetPath, threshold, recurSync);
        //czesc wlasciwa demona

    }

    
    printf("source: %s\ntarget: %s\nrecurency: %s\nthreshold: %d\nsleep time: %d\n", sourcePath, targetPath, recurSync ? "true":"false", threshold, sleepTimeSeconds);
    closelog();
    exit(EXIT_SUCCESS);
    return 0;

} 