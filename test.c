//Plik przeznaczony do testowania funkcji
#include "demonlib.h"

int main()
{
    int waga;
    printf("test_getSize:\n");
    waga=getSize("/home/michal/Documents/ProjectDemon/test.c");
    printf("%d\n",waga);
    return 0;
}