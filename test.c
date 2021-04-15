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
    //test_compareCatalogs();
    

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
    /*printf("test_getLastModificationTime:\n");
    time_t data_modyfikacji;
    double data_modyfikacji_;
    data_modyfikacji=getLastModificationTime("/home/michal/Documents/ProjectDemon/demonlib.h");
    data_modyfikacji_=difftime(data_modyfikacji,0);
    printf("%g\n",data_modyfikacji_);
    */
   //nie jestem pewien czy dziala poprawnie
   //probowalem wyswietlic czas w bardziej czytelnej formie niz ciag cyfr metoda ze StackOverflow ale póki co bez zalozonego skutku
}
void test_pathToFile()
{

//==================================================================
   printf("test_pathToFile:\n");
   char *_newpath=pathToFile("/source","a.txt");
   printf("%s\n",_newpath);
   //dla powyzszych argumentow zwrocil sciezke "/home/michal/Documents/ProjectDemon/source/a.txt"
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
    printf("1");
    char* source = "/source";

    printf("2");
    char* target = "/target";

    printf("3");
    bool recu = false;

    int treshold = 500;
    compareCatalogs(source, target, treshold, recu);
    printf("wynik: ");
}