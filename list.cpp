#include <iostream>
#include <fstream>
#include "list.h"

//konstruktor listy
list::list(){
    first = NULL;
}

void list::Wypisz(){
    // wskaznik na pierszy element listy
    event *temp = first;

    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << "Data wydarzenia: ";
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d", localtime(&temp->date));
        cout << buff;
        strftime(buff, 20, "%H:%M", localtime(&temp->time));
        cout << " " << buff << endl;
        cout << "Spotkanie bedzie trwalo: " << temp->duration << endl;
        cout << "Docelowa grupa: " << temp->group << endl;
        cout << "Opis:\n"<< temp->description <<"\n"<< endl;
        temp=temp->next;
    }
}

void list::add_event(struct event e)
{
    event *new_event = new event;    // tworzy nowy element listy

    // wypełniamy naszymi danymi
    new_event->date = e.date;
    new_event->time = e.time;
    new_event->duration = e.duration;
    new_event->group = e.group;
    new_event->description = e.description;

    if (first==0) // sprawdzamy czy to pierwszy element listy
    {
        // jeżeli tak to nowy element jest teraz poczštkiem listy
        first = new_event;
    }

    else
    {
        // w przeciwnym wypadku wędrujemy na koniec listy
        event *temp = first;

        while (temp->next)
        {
            // znajdujemy wskanik na ostatni element
            temp = temp->next;
        }

        temp->next = new_event;  // ostatni element wskazuje na nasz nowy
        new_event->next = 0;     // ostatni nie wskazuje na nic
    }
}

void list::ZapiszDoPliku()
{
    ofstream plik;
    plik.open("dane.txt");

    event *temp = first;

    while (temp != 0)
    {
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d", localtime(&temp->date));
        plik << buff << " ";
        strftime(buff, 20, "%H:%M", localtime(&temp->time));
        plik << buff << " ";
        plik << temp->duration << endl;
        plik << temp->group << endl;
        plik << temp->description;
        if (temp->next){
        plik << endl;
        }

        temp = temp->next;
    }

    plik.close();
}

void list::WczytajZPliku()
{

    struct event e;
    struct tm tm;

    ifstream plik;
    plik.open("dane.txt");

    event *new_event = new event();
    char buff[20];
    while(!plik.eof())
    {
        plik >> buff;
        strptime(buff, "%Y-%m-%d", &tm);
        e.date = mktime(&tm);

        plik >> buff;
        strptime(buff, "%H:%M", &tm);
        e.time = mktime(&tm);

        plik >> e.duration;
        string delete_line;
        getline( plik, delete_line);
        getline( plik, e.group);
        getline( plik, e.description);

        add_event(e);
    }

    plik.close();
}