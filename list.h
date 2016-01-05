#include "event.h" //ladujemy info o strukturze event

//zabezpieczenie zeby dokladnie raz zaincludowac ten plik
#ifndef LIST_H
#define LIST_H

using namespace std;

struct list {
    event *first; //wskaznik na pczatek listy
    void add_event(struct event e);
    // void delete_event ();
    void ZapiszDoPliku();
    void Wypisz();
    void WczytajZPliku();
    list();
};

#endif /* LIST_H */

