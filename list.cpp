#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
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
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&temp->date));
        cout << "Data wydarzenia: " << buff << endl;
        cout << "Spotkanie bedzie trwalo: " << temp->duration << endl;
        cout << "Docelowa grupa: " << temp->group << endl;
        cout << "Opis:\n"<< temp->description << endl;
        temp=temp->next;
    }
}

void list::add_event(struct event e)
{
    event *new_event = new event;    // tworzy nowy element listy

    // wypełniamy naszymi danymi
    new_event->date = e.date;
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
        strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&temp->date));
        plik << buff << " ";
        plik << temp->duration << endl;
        plik << temp->group << endl;
        plik << temp->description;
        if(temp->next)
            plik << endl;
        temp = temp->next;
    }

    plik.close();
}

void list::WczytajZPliku()
{
    struct event e;
    struct tm tm = {0};

    ifstream plik;
    plik.open("dane.txt");

    event *new_event = new event();
    char buff[20];
    while(!plik.eof())
    {
        string date;
        plik >> buff;
        date += buff;
        plik >> buff;
        date += " ";
        date += buff;
        strcpy(buff, date.c_str());
        strptime(buff, "%Y-%m-%d %H:%M", &tm);
        e.date = mktime(&tm);

        plik >> e.duration;
        string delete_line;
        getline( plik, delete_line);
        getline( plik, e.group);
        getline( plik, e.description);

        add_event(e);
    }

    plik.close();
}

void list::add_event_manually(){
    char buff[20];
    struct event e;
    struct tm tm = {0};
    cout << "Dodaj nowe wydarzenie:" << endl;
    cout << "Podaj date wydarzenia, w formacie rok-miesiac-dzien np. 2016-09-12: ";
    cin >> buff;
    strptime(buff, "%Y-%m-%d", &tm);
    e.date = mktime(&tm);
    cout << "Podaj godzinę wydarzenia, w formacie godzina-minuty np. 12:30: ";
    cin >> buff;
    strptime(buff, "%H:%M", &tm);
//    e.time = mktime(&tm);
    cout << "Podaj przewidywany czas trwania zdarzenia w minutach: ";
    cin >> e.duration;
    cout << "Podaj grupe: ";
    cin.sync();
    getline(cin, e.group);
    cout << "Opis wydarzenia: " << endl;
    cin.sync();
    getline(cin, e.description);

    add_event(e);
    system("cls");
    cout << "Wydarzenie dodane pomyslnie." <<endl;
    system("pause");
}

void list::menu(){
    int answer;

    cout << "Menu:" << endl;
    cout << "[0]. Exit." << endl;
    cout << "[1]. Dodaj nowe wydarzenie." << endl;
    cout << "[2]. Wyszukaj zdarzenie." << endl;
    cout << "[3]. Edytuj zdarzenie." << endl;
    cout << "[4]. Usuń zdarzenie." << endl;
    cout << "Podaj interesujaca Cie opcje: ";
    cin >> answer;
    switch(answer){
        case 0:
            return;
        break;
        case 1:{
            system("cls");
            add_event_manually();
        }
        break;
        case 2:{
            string search_string;
            cout << "Wszukaj wydarzenie ze względu na:" << endl;
            cout << "[0].Exit\n[1]. Date\n[2]. Grupe\n[3]. Opis" << endl;
            cin >> answer;
            switch(answer){
                case 0:
                    return;
                case 1:
                    cin.sync();
                    getline(cin, search_string);
                    search_date(search_string);
                break;
                case 2:
                    cin.sync();
                    getline(cin, search_string);
                    search_group(search_string);
                break;
                case 3:
                    cin.sync();
                    getline(cin, search_string);
                    search_description(search_string);
                break;
                default:
                cout << "Podales bledna opcje." << endl;
                system("pause");
                system("cls");
                menu();
                break;
            }
        }
        break;
        default:
            cout << "Podales bledna opcje." << endl;
            system("pause");
            system("cls");
            menu();
        break;
    }
}

void list::search_date(string date){
    event *temp = first;
    cout << "Oto znalezione wydarzenia o podanej dacie " << date << ":" <<endl;
    while(temp){
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&temp->date));
        string str(buff);
        if(str == date) {
            cout << "Data wydarzenia: " << buff << endl;
            cout << "Spotkanie bedzie trwalo: " << temp->duration << endl;
            cout << "Docelowa grupa: " << temp->group << endl;
            cout << "Opis:\n"<< temp->description << endl;
        }
        temp=temp->next;
    }
}

void list::search_group(string group){
    event *temp = first;
    cout << "Oto znalezione wydarzenia po grupie " << group << ":" <<endl;
    while(temp){
        if(temp->group == group) {
            char buff[20];
            strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&temp->date));
            cout << "Data wydarzenia: " << buff << endl;
            cout << "Spotkanie bedzie trwalo: " << temp->duration << endl;
            cout << "Docelowa grupa: " << temp->group << endl;
            cout << "Opis:\n"<< temp->description << endl;
        }
        temp=temp->next;
    }
}

void list::search_description(string description){
    event *temp = first;
    cout << "Oto znalezione wydarzenia po podanym opicie: \"" << description << "\":" <<endl;
    while(temp){
        if(temp->description == description) {
            char buff[20];
            strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&temp->date));
            cout << "Data wydarzenia: " << buff << endl;
            cout << "Spotkanie bedzie trwalo: " << temp->duration << endl;
            cout << "Docelowa grupa: " << temp->group << endl;
            cout << "Opis:\n"<< temp->description << endl;
        }
        temp=temp->next;
    }
}

void list::UsunEventPoDacie(string date)
{
    event *biezacy = first;
    event *poprzedni = NULL;
    char buff[20];
    while(biezacy){
            strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&biezacy->date));
            string str(buff);
            if(str == date){
                if (poprzedni){
                    poprzedni->next = biezacy ? biezacy->next : NULL;
                } else {
                  first = biezacy->next;
                }
                break;
            }
        poprzedni = biezacy;
        biezacy = biezacy->next;
    }
}

bool porownaj(time_t a, time_t b){
    if (a < b)
        return false;

    return true;
}

void list::Sortuj()
{
    bool cosSieZmienilo = false;
    do
    {
        cosSieZmienilo = false;
        event *biezacy = first;
        event *poprzedni = NULL;
        while(biezacy)
        {
            if (biezacy->next) //jesli jest nastepny element
            {
              //  bool trzebaZamienic = porownaj(biezacy,biezacy->next);//TODO napisać
                if (porownaj(biezacy->date,biezacy->next->date))
                {
                    cosSieZmienilo = true;//musimy kolejny raz przeleciec liste, aby sie upewnic czy wszystko jest na swoim miejscu po tej zmianie
                    if (biezacy == first) {
                        first = biezacy->next;
                    }
                    event* tmp = biezacy;
                    biezacy = biezacy->next;
                    tmp->next = biezacy->next;
                    biezacy->next = tmp;
                    if (poprzedni) {
                        poprzedni->next = biezacy;
                    }
                }
            }
            poprzedni = biezacy;
            biezacy = biezacy->next;
        }
    }
    while(cosSieZmienilo);
}
