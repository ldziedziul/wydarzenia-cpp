#include "list.h"

int main(){
    list* baza = new list();
    baza->WczytajZPliku();
    //baza->menu();
//baza->search_date("2016-01-07 16:50");
  //  baza->UsunEventPoDacie("2016-01-06 12:50");
    baza->Sortuj();
    baza->Wypisz();
    baza->ZapiszDoPliku();
    return 0;
}
