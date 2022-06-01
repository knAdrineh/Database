//
//  DumbDataBase.cpp
//  dumbDataBase
//
//  Created by Adrineh Khodaverdian on 5/30/22.
//

#include "DumbDataBase.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

DumbDataBase::DumbDataBase(const string& filename){
    count_deleted = 0;
    numRecords = 0;
    this->filename = filename;
    fstream iofile(filename, ios::in | ios::out);
    ws(iofile);  //skips all the white spaces
    getline(iofile, name, ',');
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >> age;
        ws(iofile);
        getline(iofile, name, ',');
        if(name[0] == '~')
            count_deleted++;
        else{
            numRecords++;
        }
    }
    iofile.close();

    
}
void DumbDataBase::addItem(const string& temp_name, const int& temp_age){
    bool found = false;
 
    if (numRecords > 0)
        iofile.open(filename, ios::in | ios::out);
    else
        iofile.open(filename, ios::in | ios::out | ios::app);
        iofile.seekg(0,ios::beg);
    
    if(count_deleted>0){
        iofile.seekg(0, ios::beg);
        ws(iofile);
        getline(iofile, name, ',');
        while (!iofile.eof() && !iofile.fail())
        {
            
            iofile >> age;
            //cout << name << " " << age << endl;
          
            if(name[0] == '~'){
                // update database
                iofile.seekp((numRecords - 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << temp_name << ","<< setw(AGE_LEN) << temp_age << endl;
                count_deleted--;
         
            }
            ws(iofile);
            getline(iofile, name, ',');
           
        }
  
        found = true;
    }

    if(!found){
        iofile.seekp(0, ios::end);
        iofile << setw(NAME_LEN) << temp_name << ","<< setw(AGE_LEN) << temp_age << endl;

    }
    numRecords++;
    
    iofile.close();
}
void DumbDataBase::replaceItem(const int& record, const string& n, const int& a){
    string temp;
    iofile.open(filename, ios::in | ios::out);
    ws(iofile);  //skips all the white spaces
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
        iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
        iofile << setw(NAME_LEN) << n << ","
            << setw(AGE_LEN) << a << endl;
    }
    iofile.close();
    
}
void DumbDataBase::printData(){
    int count = 0;
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
    cout << "\nHave " << numRecords << " records" << endl;
    cout << "Have " << count_deleted << " deleted records " << endl;
}
void DumbDataBase::sortByName(){
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);
    string temp_name = "";
    int temp_age = 0;
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
void DumbDataBase::sortByAge(){
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);
    string temp_name = "";
    int temp_age = 0;
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

int DumbDataBase::getRecordNum(string n, int a){
    int count =0;
    int found_rec = 0;
    bool found = false;
  
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0,ios::beg);
    ws(iofile);
    getline(iofile, name, ',');

    count = 1;
    while (!iofile.eof() && !iofile.fail() && !found)
    {
        iofile>>age;
        iofile.ignore();
   
        if(n.compare(name)==0 && age ==a){
         
            found_rec = count;
            found = true;
        }
        ws(iofile);
        getline(iofile, name, ',');
        count++;
        
    }
    iofile.close();
    return found_rec;
}
int DumbDataBase::searchRecord(const string& n){

    int found_age = 0;
    bool found = false;
  
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0,ios::beg);
    ws(iofile);
    getline(iofile, name, ',');


    while (!iofile.eof() && !iofile.fail() && !found)
    {
        iofile>>age;
        iofile.ignore();
   
        if(n.compare(name)==0){
            found = true;
            found_age = age;
        }

        ws(iofile);
        getline(iofile, name, ',');

        
    }
    iofile.close();
    return found_age;
        

}
void DumbDataBase::deleteRecord(const int& record){
    iofile.open(filename, ios::in | ios::out);
    ws(iofile);
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
        name[0] ='~';
        
        iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
        iofile << setw(NAME_LEN) << name << ","
            << setw(AGE_LEN) << age << endl;
        count_deleted++;
        numRecords--;
        
    }
    iofile.close();
    
}

