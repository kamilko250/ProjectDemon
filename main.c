#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char** argv)
{
    openlog("PROJEKT", LOG_PID|LOG_CONS, LOG_USER);
    char* sourcePath = NULL;
    char* targetPath = NULL;
    bool recurSync = false;
    int threshold = 4096;
    if(argc>=3)
    {
        sourcePath = argv[1];
        targetPath = argv[2];
        
    }
    else
    {
        syslog(LOG_ERR, "Too few arguments");
        exit(EXIT_FAILURE);
    }
    if(argc>=4)
    {
        if( !strcmp(argv[3],"-R"))
        {
            recurSync=true;
            
            if( argc >= 5 && !strcmp(argv[4],"-s"))
            {
                if(argc>=5)
                {
                    int bufor = atoi(argv[5]);
                    if(bufor>0)
                    {
                        threshold = bufor;
                    }
                    else
                    {
                        //raport o błędzie
                    }
                }
            }
        }
        else if( !strcmp(argv[3],"-s"))
        {
            if(argc>=5)
            {
                int bufor = atoi(argv[4]);
                if(bufor>0)
                {
                    threshold = bufor;
                }
                else
                {
                    //raport o błędzie
                }
            }
            else
            {
                //raport o błędzie
            }
        }
        
    }
    printf("%s\n%s\n%s\n%d\n", sourcePath, targetPath, recurSync ? "true":"false", threshold);
    closelog();
    exit(EXIT_SUCCESS);

} 