//Plik przeznaczony do testowania funkcji
#include "demonlib.h"
#include <time.h>

int main()
{
    //=================================================================
    int waga;
    printf("test_getSize:\n");
    waga=getSize("/home/michal/Documents/ProjectDemon/test.c");
    printf("%d\n",waga);
    //dziala poprawnie

    //==================================================================
    //printf("test_getLastModificationTime:\n");
    /*time_t data_modyfikacji;
    double data_modyfikacji_;
    data_modyfikacji=getLastModificationTime("/home/michal/Documents/ProjectDemon/demonlib.h");
    data_modyfikacji_=difftime(data_modyfikacji,0);
    printf("%g\n",data_modyfikacji_);
    */
   //nie jestem pewien czy dziala poprawnie
   //probowalem wyswietlic czas w bardziej czytelnej formie niz ciag cyfr metoda ze StackOverflow ale puki co bez zalozonego skutku
   
   //==================================================================
   printf("test_pathToFile:\n");
   char *_newpath=pathToFile("/home/michal/Documents/ProjectDemon/source","a.txt");
   printf("%s\n",_newpath);
   //dla powyzszych argumentow zwrocil sciezke "/home/michal/Documents/ProjectDemon/source/a.txt"
   //dziala

   //==================================================================
    printf("test_changeCatalogs:\n");
    char *_outpath=changeCatalogs("/home/michal/Documents/ProjectDemon/source/a.txt","/home/michal/Documents/ProjectDemon/source","/home/michal/Documents/ProjectDemon/target");
    printf("%s\n",_outpath);
    //przykladowe dzialanie: dla powyzszych parametrow tworzy nowa sciezke "/home/michal/Documents/ProjectDemon/target/a.txt"
    //dziala
    return 0;
}