//Plik przeznaczony do testowania funkcji
#include "demonlib.h"
#include <time.h>

void test_getSize();
void test_getLastModTime();
void test_changeCatalogs();
void test_pathToFile();
void test_compareCatalogs();

int main()
{
    //test_getSize();
    //test_getLastModTime();
    //test_pathToFile();
    //test_changeCatalogs();
    test_compareCatalogs();


    return 0;
}
void test_getSize()
{
    //=================================================================
    int waga;
    printf("test_getSize:\n");
    waga=getSize("test.c");
    printf("%d\n",waga);
    //dziala poprawnie
}
void test_getLastModTime()
{
    //==================================================================
    printf("test_getLastModificationTime:\n");
    time_t data_modyfikacji;
    data_modyfikacji=getLastModificationTime("demonlib.h");
    printf("%ld\n", data_modyfikacji);
    //dziala
}
void test_pathToFile()
{
    //==================================================================
    printf("test_pathToFile:\n");
    char *_newpath=pathToFile("/source","a.txt");
    printf("%s\n",_newpath);
    //dziala
}
void test_changeCatalogs()
{
    //==================================================================
    printf("test_changeCatalogs:\n");
    char *_outpath=changeCatalogs("source/a.txt","/source","/target");
    printf("%s\n",_outpath);
    //przykladowe dzialanie: dla powyzszych parametrow tworzy nowa sciezke "/home/michal/Documents/ProjectDemon/target/a.txt"
    //dziala
}
void test_compareCatalogs()
{
    //=================================================================
    printf("test_compareCatalogs:\n");
    char* source = "source";
    char* target = "target";
    bool recu = false;
    int treshold = 500;
    compareCatalogs(source, target, treshold, recu);
    printf("wynik: \n");
}