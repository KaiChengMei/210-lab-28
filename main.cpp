#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);

void sort(list<Goat> trip);
void find(list<Goat> trip, const string &name); 
void totalage(const list<Goat> &trip);
void nextyear(list<Goat> &trip);
void reverse(list<Goat> &trip);
void deletecolor(list<Goat> &trip, const string &color);
void older60(list<Goat> &trip, const string &age);
void copy_trip(const list<Goat>& trip);

int main_menu();

int main() {
    srand(time(0));


    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorted goats by age:\n";
                sort(trip);
                display_trip(trip);
                break;
            case 5:
                cout << "Find a goat by name:\n";
                {
                    string n;
                    cout << "Enter name: ";
                    cin >> n;
                    find(trip, n);
                }
                break;
            case 6:
                totalage(trip);
                break;
            case 7:
                nextyear(trip);
                break;
            case 8:
                reverse(trip);
                break;
            case 9:
                {
                    string c;
                    cout << "Enter color you want to delete: ";
                    cin >> c;
                    deletecolor(trip, c);
                }
                break;
            case 10:
                older60(trip, "age");
                break;
            case 11:
                copy_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }


    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sorted goats\n";
    cout << "[5] Find goats\n";
    cout << "[6] Total age\n";
    cout << "[7] Next year(everyone age+1)\n";
    cout << "[8] Reverse list\n";
    cout << "[9] Delete color\n";
    cout << "[10] Any older than 60\n";
    cout << "[11] Copy trip\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}


void display_trip(list<Goat> trip) {
    int i = 1;
    for (auto gt: trip)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}



void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

int select_goat(list<Goat> trip) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trip);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trip.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
// 4
void sort(list<Goat> trip) {
    trip.sort([](const Goat &a, const Goat &b) {return a.get_age() < b.get_age();});
    cout << "Goat sorted" << endl;
}
// 5
void find(list<Goat> trip, const string &name) {
    auto it = find_if(trip.begin(),trip.end(), [name](const Goat&g) {return g.get_name() == name;});
    cout << "Found: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
}

//6
void totalage(const list<Goat> &trip) {
    int total = accumulate(trip.begin(), trip.end(),0,[](int sum, const Goat &g) {return sum + g.get_age(); });
    cout << "Total age is: " << total << endl;
}

//7
void nextyear(list<Goat> &trip) {
    for_each(trip.begin(), trip.end(), [](Goat &g) { g.set_age(g.get_age() + 1); });
    cout << "Each goat's age increased by 1." << endl;
}

//8
void reverse(list<Goat> &trip) {
    trip.reverse();
    cout << "Goat reversed." << endl;
}

//9 
void deletecolor(list<Goat> &trip, const string &color) {
    trip.remove_if([color] (const Goat &g) {return g.get_color() == color;});
    cout << "Goat with color: " << color << " were removed." << endl;
}

//10
void older60(list<Goat> &trip, const string &age) {
    bool elder = any_of(age.begin(), age.end(), [] (int age) {return age > 60;});
    cout << "Is ther any older than 60? :";
    if (elder) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}

//11
void copy_trip(const list<Goat>& trip) {
    list<Goat> tripCopy;
    copy(trip.begin(), trip.end(), back_inserter(tripCopy) );
    cout << "Trip copied. " << endl << "Copy size: " << tripCopy.size() << endl;
    display_trip(tripCopy);
}
