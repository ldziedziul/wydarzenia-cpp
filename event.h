#include <string>
#include <time.h>

//zabezpieczenie zeby dokladnie raz zaincludowac ten plik
#ifndef EVENT_H
#define EVENT_H

using namespace std;

struct event {
    time_t date;
    int duration;
    string group;
    string description;

    event *next;    //wskaznik na nastepny elemnt
    event();        //konstruktor
};

#endif /* EVENT_H */

