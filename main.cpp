#include "list.h"

int main(){
    list* baza = new list();
    baza->WczytajZPliku();
    //baza->add_event(t, t, 130, "LoL", "Najbardziej znana moba");
    baza->Wypisz();
    baza->ZapiszDoPliku();
    return 0;
}
