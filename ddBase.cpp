/*
 Adrineh Khodaverdian
 Professor Biehl
 CS/IS 212
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "DumbDataBase.hpp"

using namespace std;



int main()
{
    DumbDataBase data("sample.dat");

    string current_name = "";
    int age, current_age = 0;
    
    int choice,record;
    string name,temp;
    do
    {
        cout << "\nYour name's Dumb Database\n"
            << "1 - Add record\n"
            << "2 - Change record\n"
            << "3 - Print all records\n"
            << "4 - Sort records\n"
            << "5 - Search records\n"
            << "6 - Delete record\n"
            << "0 - Quit\n"
            << "Enter choice: ";
        cin >> choice;
        getline(cin, temp); // phantom newline
        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            getline(cin, current_name);
            cout << "Enter age: ";
            cin >> current_age;
            data.addItem(current_name, current_age);
            break;
        case 2:
                cout << "Enter record number to replace : " ;
                cin>> record;
                cout << "Enter new name : " ;
                cin.ignore();
                getline(cin,current_name);
                cout << "Enter new age : ";
                cin >> current_age;
                cout << "Replacing  ";
                data.replaceItem(record, current_name, current_age);
                
            break;
        case 3:
            data.printData();
            break;
        case 4:
            choice = 0;
            while( choice !=1 && choice!=2){
                cout << "Sort by age or name (1 or 2) : ";
                cin>> choice;
                if(choice==1){
                    cout << "Sorted by Age"<<endl;
                    data.sortByAge();
                }
                else if (choice==2){
                    cout << "Sorted by Name"<<endl;
                    data.sortByName();
                }
            }
            break;
        case 5:
            cout << "Enter name to search for: " ;
            cin.ignore();
            getline(cin,current_name);
            record = data.getRecordNum(current_name, data.searchRecord(current_name));
            if(data.searchRecord(current_name)==0)
            {
                cout << "Name not found in the data base ." << endl;
            }
            else {
                cout << "Found record of  " << current_name << " at " << record << endl;
                cout << current_name << " is " << data.searchRecord(current_name) << " ." <<endl;
            }
            break;
        case 6:
            cout << "Enter record number: ";
            cin >> record;
            data.deleteRecord(record);
            break;
        case 0:
            cout << "Quit\n";
            break;
        default: cout << "Invalid selection\n";
            break;
        }
    } while (choice != 0);

}
