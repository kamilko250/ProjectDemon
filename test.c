//Plik przeznaczony do testowania funkcji
#include "demonlib.h"
#include <time.h>

void test_getSize();
void test_getLastModTime();
void test_changeCatalogs();
void test_pathToFile();
void test_compareCatalogs();
void test_getLastAccesTime();
void test_updateFile();

int main()
{
    //test_getSize();
    //test_getLastModTime();
    //test_pathToFile();
    //test_changeCatalogs();
    //test_getLastAccesTime();
    //test_updateFile();
    
    //=======================================================================
    //test_compareCatalogs();
    //w momencie gdy zawartosc source i target sa identyczne, wyrzuca jednoczesnie komunikat, ze znaleziono i nieznaleziono plik
    //nie dziala gdy plik target jest pusty (nie wypisuje nic)
    //kiedy w target oba pliki sie zgadzaja, ale jest jeszcze jakis dodatkowy, funkcja wypisuje to samo co w przypadku 2 zgodnych, nie wiem czy tu dziala dobrze czy komunikat wynika z tego samego bledu co przy identycznych katalogach
    //gdy jeden plik w target sie zgadza a inny nie lub gdy w target znajduje sie inny plik, dziala poprawnie
    //gdy pliki w obu katalogach jest po jednym pliku i sa identyczne, funkcja dziala poprawnie

    //PODSUMOAWNIE: Nie dziala gdy w target jest pusty, gdy w targecie jest wiecej niz jeden plik (identyczny z tymi w source)
    //UWAGA!!! Raz funkcja uszkodzila plik w katalogu target, powod nieznany
    //=======================================================================


    return 0;
}
void test_updateFile()
{
    printf("test_getLastAccesTime (btw Access pisze sie z 2 s ;):\n");
    updateFile("source/a.txt","target/a.txt",100);
    //funkcja zmienia zawartosc pliku w katalogu target np a.txt na taka z pliku w katalogu source
    //dziala poprawnie
}
void test_getLastAccesTime()
{
    printf("test_getLastAccesTime (btw Access pisze sie z 2 s ;):\n");
    time_t at;
    at=getLastAccesTime("/home/michal/Documents/ProjectDemon/source/a.txt");
    printf("%ld\n", at);
    //dziala poprawnie
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
<<<<<<< HEAD
=======
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
>>>>>>> b1eae295ce4d9ff5eb7e421c6b9f8cbef1caa0e2
    printf("test_changeCatalogs:\n");
    char *_outpath=changeCatalogs("source/a.txt","/source","/target");
    printf("%s\n",_outpath);
    //przykladowe dzialanie: dla powyzszych parametrow tworzy nowa sciezke "/home/michal/Documents/ProjectDemon/target/a.txt"
    //dziala
<<<<<<< HEAD
=======

    //==================================================================
    updateFile("/home/michal/Documents/ProjectDemon/source","/home/michal/Documents/ProjectDemon/target",100);
    //funkcja nie kopiuje plikow znajujacych sie w katalogu source do katalogu target

    //==================================================================
    clearCatalogs("/home/michal/Documents/ProjectDemon/source","/home/michal/Documents/ProjectDemon/target",1);
    //niezaleznie od parametru recurSync, funkcja nie zmienia nic w zawartosciach katalogow
    return 0;
>>>>>>> b1eae295ce4d9ff5eb7e421c6b9f8cbef1caa0e2
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