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
    //time_t data_modyfikacji;
    //printf("%lld\n", (long long) data_modyfikacji);
    //double data_modyfikacji_;
    //data_modyfikacji=getLastModificationTime("/home/michal/Documents/ProjectDemon/demonlib.h");
    //data_modyfikacji_=difftime(data_modyfikacji,0);
    //printf("%g\n",data_modyfikacji_);
    
   //nie jestem pewien czy dziala poprawnie
   //probowalem wyswietlic czas w bardziej czytelnej formie niz ciag cyfr metoda ze StackOverflow ale póki co bez zalozonego skutku
   //update: probowalem innych metod na printf zwracanej wartosci w innej formie niz ciag liczb, bez sukcesu
   //na stacku ktos napisal ze sie nie da, mysle ze to mozliwe :p
   
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

    //==================================================================
    updateFile("/home/michal/Documents/ProjectDemon/source","/home/michal/Documents/ProjectDemon/target",100);
    //funkcja nie kopiuje plikow znajujacych sie w katalogu source do katalogu target

    //==================================================================
    clearCatalogs("/home/michal/Documents/ProjectDemon/source","/home/michal/Documents/ProjectDemon/target",1);
    //niezaleznie od parametru recurSync, funkcja nie zmienia nic w zawartosciach katalogow
    return 0;
}
