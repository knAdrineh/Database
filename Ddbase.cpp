/*
 Adrineh Khodaverdian
 Professro Biehl
 CS/IS 212
 
 implementation of sort, search, delete and change record
 */

#include "Ddbase.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Ddbase::Ddbase(string f){
    filename = f;
    count = 0;
    deleted = 0;
    fstream iofile(filename, ios::in | ios::out);
    ws(iofile);
    getline(iofile, name, ',');
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >> age;
        if (name[0] != DELETED){
            cout << name << " " << age << endl;
            count++;
        }
        else
            deleted++;
        ws(iofile);
        getline(iofile, name, ',');
    }
    cout << endl;
    iofile.close();
}
void Ddbase::addRecord(string n, int a){
    int temp;
    if (searchRecords(n, temp) == -1){
        if (count > 0)
            iofile.open(filename, ios::in | ios::out);
        else
            iofile.open(filename, ios::in | ios::out | ios::app);
        iofile.seekp(0, ios::end);
        iofile << setw(NAME_LEN) << n << "," << setw(AGE_LEN) << a << endl;
        count++;
        iofile.close();
    }
    else
        cout << n << " already exists\n";
}
void Ddbase::changeRecord(int recNum ,string n, int a){
    iofile.open(filename, ios::in | ios::out);
    ws(iofile);  //skips all the white spaces
    if (recNum > count)
    {
        cout << "Record does not exist\n";
    }
    else
    {
        iofile.seekp((recNum) * RECORD_LEN, ios::beg);
        iofile << setw(NAME_LEN) << n << "," << setw(AGE_LEN) << a << endl;
    }
    iofile.close();
}
bool Ddbase::deleteRecord(string n){
    int temp, recNum;
    bool success = false;
    recNum = searchRecords(n, temp);
    if (recNum>=0)
    {
        iofile.open(filename, ios::in | ios::out);
        iofile.seekp((recNum) * RECORD_LEN, ios::beg);
        iofile << DELETED;
        success = true;
        iofile.close();
        deleted++;
    }
    return success;
}

void Ddbase::printRecords(){
    int count = 0;
   
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);
    getline(iofile, name, ',');
    count = 1;
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >>age;
        if(name[0]!=DELETED){
            cout << "Record " << count << " " << name << " " << age<< endl;
            count++;
        }
      
        ws(iofile);
        getline(iofile, name, ',');
    }
   
    cout << "\nDeleted  " <<  deleted << "\n " << endl;
    iofile.close();
}
void Ddbase::sortRecords(){
    string prevName = "";
    int prevAge = 0;
    bool swap ;
    int pass = 1;
    do{
        swap = false;
        iofile.open(filename, ios::in | ios::out);
        iofile.seekg(0, ios::beg);
        ws(iofile);
        getline(iofile, prevName, ',');
        iofile>> prevAge;
        for(int  i = 1; i <= count - pass; i++){
            ws(iofile);
            getline(iofile, name, ',');
            iofile>> age;
            if (prevName > name ){
                iofile.seekp((i-1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << name << "," << setw(AGE_LEN) << age << endl;
                iofile << setw(NAME_LEN) << prevName << "," << setw(AGE_LEN) << prevAge << endl;
                swap =true;
            }
            prevName = name;
            prevAge = age;
        }
        pass++;
        iofile.close();
     } while (swap);
   
}
int Ddbase::searchRecords(string n, int &a){
    int record = -1, recNum=0;
    bool found = false;
    if (count > 0){
        iofile.open(filename, ios::in | ios::out);
        iofile.seekg(0, ios::beg);
        ws(iofile);
        getline(iofile, name, ',');
        while (!iofile.eof() && !iofile.fail() && !found)
        {
            iofile >> age;
            if (name[0] != DELETED && name == n)
                found = true;
            recNum++;
            ws(iofile);
            getline(iofile, name, ',');
        }
        if (found){
            a = age;
            record = recNum-1;
        }
        iofile.close();
    }
    return record;
}
