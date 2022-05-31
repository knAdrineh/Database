/*
 Adrineh Khodaverdian
 Professor Biehl
 CS/IS 212
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int NAME_LEN = 21;
const int AGE_LEN = 3;
const int RECORD_LEN = NAME_LEN + AGE_LEN + 2;

int main()
{
    int numRecords = 0;
    bool found = false;
    string temp_name = "";
    int temp_age = 0;
    
    int age, choice, count, record, count_deleted = 0;
    string name,temp;
    char change;
    char filename[] = "sample.dat";
    fstream iofile(filename, ios::in | ios::out);
    ws(iofile);  //skips all the white spaces
    getline(iofile, name, ',');
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >> age;
        cout << name << " " << age << endl;
        numRecords++;
        ws(iofile);
        getline(iofile, name, ',');
        if(name[0] == '~')
            count_deleted++;
    }
    iofile.close();
    cout << "\nHave " << numRecords-count_deleted << " records" << endl;
    cout << "Have " << count_deleted << " deleted records " << endl;
    do
    {
        cout << "\nAdrineh's Dumb Database\n"
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
                found = false;
            if (numRecords > 0)
                iofile.open(filename, ios::in | ios::out);
            else
                iofile.open(filename, ios::in | ios::out | ios::app);
                iofile.seekg(0,ios::beg);
            cout << "Enter name: ";
            getline(cin, temp_name);
            cout << "Enter age: ";
            cin >> temp_age;
            for(int i = 1; i<=numRecords; i++)
            {
               
                ws(iofile);
                getline(iofile, name, ',');
                iofile>> age;
                if(name[0]=='~'){
                    iofile.seekp(( i- 1) * RECORD_LEN, ios::beg);
                    iofile << setw(NAME_LEN) << temp_name << ","
                        << setw(AGE_LEN) << temp_age << endl;
                    i = numRecords; //to stop the loop
                    found = true;
                    count_deleted--;
                }
            }
            if(!found){
                iofile.seekp(0, ios::end);
                
                iofile << setw(NAME_LEN) << name << ","
                    << setw(AGE_LEN) << age << endl;
                numRecords++;
            }
            iofile.close();
            break;
        case 2:
            iofile.open(filename, ios::in | ios::out);
            cout << "Enter record number: ";
            cin >> record;
            if (record > numRecords)
            {
                cout << "Record does not exist\n";
            }
            else
            {
                iofile.seekg((record - 1) * RECORD_LEN, ios::beg);
                ws(iofile);
                getline(iofile, name, ',');
                iofile >> age;
                cout << "Record " << record << " " << name << " " << age << endl;
                cout << "Change name? (y|n) ";
                cin >> change;
                getline(cin, temp); // phantom newline
                if (change == 'y' || change == 'Y') {
                    cout << "Enter name: ";
                    getline(cin, name);
                }
                cout << "Change age?  (y|n) ";
                cin >> change;
                getline(cin, temp);
                if (change == 'y' || change == 'Y') {
                    cout << "Enter age: ";
                    cin >> age;
                }
                iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << name << ","
                    << setw(AGE_LEN) << age << endl;
            }
            iofile.close();
            break;
        case 3:
            iofile.open(filename, ios::in | ios::out);
            iofile.seekg(0, ios::beg);
            ws(iofile);
            getline(iofile, name, ',');
            count = 1;
            while (!iofile.eof() && !iofile.fail())
            {
                iofile >> age;
                cout << "Record " << count << " " << name << " " << age << endl;
                count++;
                ws(iofile);
                getline(iofile, name, ',');
            }
            iofile.close();
            break;
        case 4:
            iofile.open(filename, ios::in | ios::out);
            iofile.seekg(0, ios::beg);
            ws(iofile);
            choice = 0;
                
            while( choice !=1 && choice!=2){
                
                cout << "Sort by age or name (1 or 2) : ";
                cin>> choice;
                if(choice==1){
                    cout << "Sorted by Age"<<endl;
                    for(int i = 1; i<=numRecords; i++){
                        for(int j = i+1; j<=numRecords; j++){
                            iofile.seekg((i - 1) * RECORD_LEN, ios::beg);
                            ws(iofile);
                            getline(iofile, name, ',');
                            iofile >> age;
                            
                            iofile.seekg((j - 1) * RECORD_LEN, ios::beg);
                            ws(iofile);
                            getline(iofile, temp_name, ',');
                            iofile >> temp_age;
                            
                            if(age > temp_age){
                                iofile.seekp(( i- 1) * RECORD_LEN, ios::beg);
                                iofile << setw(NAME_LEN) << temp_name << ","
                                    << setw(AGE_LEN) << temp_age << endl;
                                
                                iofile.seekp((j- 1) * RECORD_LEN, ios::beg);
                                iofile << setw(NAME_LEN) << name << ","
                                    << setw(AGE_LEN) << age << endl;
                            }
                        }
                    }
                    iofile.close();
                }
                else if (choice==2){
                    cout << "Sorted by Name"<<endl;
                    for(int i = 1; i<=numRecords; i++){
                        for(int j = i+1; j<=numRecords; j++){
                            iofile.seekg((i - 1) * RECORD_LEN, ios::beg);
                            ws(iofile);
                            getline(iofile, name, ',');
                            iofile >> age;
                            
                            iofile.seekg((j - 1) * RECORD_LEN, ios::beg);
                            ws(iofile);
                            getline(iofile, temp_name, ',');
                            iofile >> temp_age;
                            
                            if(name[0] > temp_name[0] && name[0]!='~' && temp_name[0]!='~'){
                                iofile.seekp(( i- 1) * RECORD_LEN, ios::beg);
                                iofile << setw(NAME_LEN) << temp_name << ","
                                    << setw(AGE_LEN) << temp_age << endl;
                                
                                iofile.seekp((j- 1) * RECORD_LEN, ios::beg);
                                iofile << setw(NAME_LEN) << name << ","
                                    << setw(AGE_LEN) << age << endl;
                            }
                        }
                    }
                    iofile.close();
                }

            }

            
            break;
        case 5:
            if(numRecords == 0)
                cout << "Database is empty " <<endl;
            else{
                cout << "Enter name to search for: " ;
                getline(cin,temp_name);
                    
                iofile.open(filename, ios::in | ios::out);
                iofile.seekg(0,ios::beg);
                ws(iofile);
                getline(iofile, name, ',');
        
                count = 1;
                while (!iofile.eof() && !iofile.fail() && !found)
                {
                    iofile>>age;
                    iofile.ignore();
               
                    if(temp_name.compare(name)==0){
                        cout << "Found record of  " << name << " at " << count;
                        found = true;
                    }
     
                    ws(iofile);
                    getline(iofile, name, ',');
                    count++;
                    
                }
                if(!found)
                    cout << "Record not found" << endl;
              
                iofile.close();
            }

            break;
        case 6:
            iofile.open(filename, ios::in | ios::out);
            cout << "Enter record number: ";
            cin >> record;
            if (record > numRecords)
            {
                cout << "Record does not exist\n";
            }
            else
            {
                iofile.seekg((record - 1) * RECORD_LEN, ios::beg);
                ws(iofile);
                getline(iofile, name, ',');
                iofile >> age;
                cout << "Record " << record << " " << name << " " << age << endl;
                cout << "Are you sure you want to delete the record? (y|n) ";
                cin >> change;
                getline(cin, temp); // phantom newline
                if (change == 'y' || change == 'Y') {
                    name = '~' + name;
                    iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
                    iofile << setw(NAME_LEN) << name << ","
                        << setw(AGE_LEN) << age << endl;
                    count_deleted++;
                }
            }
            iofile.close();
            break;
        case 0:
            cout << "Quit\n";
            break;
        default: cout << "Invalid selection\n";
            break;
        }
    } while (choice != 0);

}
