/*
 Adrineh Khodaverdian
 Professro Biehl
 CS/IS 212
 
 implementation of sort, search, delete and change record 
 */
#include "Ddbase.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int choice;
    int age;
    int record = 0;
    int chance = 0;
    int recordNumber = 0;
    string name;
    Ddbase db("sample.dat");
    do
    {
        cout << "Your Name's Dumb Database\n"
            << "1 – Add record\n"
            << "2 – Change record\n"
            << "3 – Print all records\n"
            << "4 – Sort records by name\n"
            << "5 – Search records by name\n"
            << "6 – Delete record\n"
            << "0 – Quit\n"
            << "\nEnter choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "Name to add: ";
                cin.ignore();
                getline(cin, name);
                cout << "Age is: ";
                cin >> age;
                db.addRecord(name, age);
                break;
            case 2:
                cout << "Name to change: ";
                cin.ignore();
                getline(cin, name);
                recordNumber = db.searchRecords(name, age);
                if (recordNumber>= 0){
                    cout << "Name to add: ";
                    getline(cin, name);
                    cout << "Age is: ";
                    cin >> age;
                    db.changeRecord(recordNumber, name, age);
                }
                else{
                    cout << name << " not found\n";
                }
                break;
            case 3:
                db.printRecords();
                break;
            case 4:
                db.sortRecords();
                break;
            case 5:
                cout << "Name to search for: ";
                cin.ignore();
                getline(cin, name);
                recordNumber = db.searchRecords(name, age);
                if (recordNumber >= 0)
                    cout << name << " with age of "
                         << age << " is at record # "
                         << recordNumber+1 << endl;
                else
                    cout << "Not found\n";
                break;
            case 6:
                cout << "Name to delete: ";
                cin.ignore();
                getline(cin, name);
                if (db.deleteRecord(name))
                    cout << name << " deleted\n";
                else
                    cout << name << " not found\n";
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    } while (choice != 0);
}



