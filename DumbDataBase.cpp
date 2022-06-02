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
    string find_name = "";
    int find_age = 0;
    this->filename = filename;
    fstream iofile(filename, ios::in | ios::out);
    ws(iofile);  //skips all the white spaces
    getline(iofile, find_name, ',');
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >> find_age;
        ws(iofile);
        getline(iofile, find_name, ',');
        if(find_name[0] == '~')
            count_deleted++;
        else{
            numRecords++;
        }
    }
    iofile.close();
    printData();
   

    
}
void DumbDataBase::addItem(const string& temp_name, const int& temp_age){

    string find_name="";
    int find_age =0;
    if (numRecords > 0)
        iofile.open(filename, ios::in | ios::out);
    else
        iofile.open(filename, ios::in | ios::out | ios::app);
    
    
    if(count_deleted>0){
        iofile.seekg(0, ios::beg);
        ws(iofile);
        getline(iofile, find_name, ',');
        while (!iofile.eof() && !iofile.fail())
        {
            
            iofile >> find_age;
            //cout << name << " " << age << endl;
          
            if(find_name[0] == '~'){
                // update database
                iofile.seekp((numRecords - 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << temp_name << ","<< setw(AGE_LEN) << temp_age << endl;
         
            }
            ws(iofile);
            getline(iofile, find_name, ',');
       
        }
  

        count_deleted--;
    }else{
        iofile.seekp(0, ios::end);
        iofile << setw(NAME_LEN) << temp_name << ","<< setw(AGE_LEN) << temp_age << endl;
    }

   
    numRecords++;
    
    iofile.close();
}
void DumbDataBase::replaceItem(const int& record, const string& n, const int& a){
    string find_name = "";
    int find_age = 0;
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
        getline(iofile, find_name, ',');
        iofile >> find_age;
        cout << "Record " << record << " " << find_name << " " << find_age << endl;
        iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
        iofile << setw(NAME_LEN) << n << ","
            << setw(AGE_LEN) << a << endl;
    }
    iofile.close();
    
}
void DumbDataBase::printData(){
    int count = 0;
    string find_name = "";
    int find_age = 0;
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);
    getline(iofile, find_name, ',');
    count = 1;
    while (!iofile.eof() && !iofile.fail())
    {
        iofile >> find_age;
        if(find_name[0]!=DELETED){
            cout << "Record " << count << " " << find_name << " " << find_age << endl;
            count++;
        }
      
        ws(iofile);
        getline(iofile, find_name, ',');
    }
   
    cout << "\nDeleted  " << count_deleted << "\n " << endl;
    iofile.close();
    

}
void DumbDataBase::sortByName(){
    string find_name = "";
    int find_age = 0;
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);
    string temp_name = "";
    int temp_age = 0;
    for(int i = 1; i<=numRecords; i++){
        for(int j = i+1; j<=numRecords; j++){
            iofile.seekg((i - 1) * RECORD_LEN, ios::beg);
            ws(iofile);
            getline(iofile, find_name, ',');
            iofile >> find_age;
            
            iofile.seekg((j - 1) * RECORD_LEN, ios::beg);
            ws(iofile);
            getline(iofile, temp_name, ',');
            iofile >> temp_age;
            
            if(find_name[0] > temp_name[0] && find_name[0]!='~' && temp_name[0]!='~'){
                iofile.seekp(( i- 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << temp_name << ","
                    << setw(AGE_LEN) << temp_age << endl;
                
                iofile.seekp((j- 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << find_name << ","
                    << setw(AGE_LEN) << find_age << endl;
            }
        }
    }
    iofile.close();
    
}
void DumbDataBase::sortByAge(){
    string find_name = "";
    int find_age = 0;
    
    string temp_name = "";
    int temp_age = 0;
    
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0, ios::beg);
    ws(iofile);

    for(int i = 1; i<=numRecords; i++){
        for(int j = i+1; j<=numRecords; j++){
            iofile.seekg((i - 1) * RECORD_LEN, ios::beg);
            ws(iofile);
            getline(iofile, find_name, ',');
            iofile >> find_age;
            
            iofile.seekg((j - 1) * RECORD_LEN, ios::beg);
            ws(iofile);
            getline(iofile, temp_name, ',');
            iofile >> temp_age;
            
            if(find_age > temp_age){
                iofile.seekp(( i- 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << temp_name << ","
                    << setw(AGE_LEN) << temp_age << endl;
                
                iofile.seekp((j- 1) * RECORD_LEN, ios::beg);
                iofile << setw(NAME_LEN) << find_name << ","
                    << setw(AGE_LEN) << find_age << endl;
            }
        }
    }
    iofile.close();
    
}

int DumbDataBase::getRecordNum(string n, int a){
    int count =0;
    int found_rec = 0;
    bool found = false;
    
    string find_name = "";
    int find_age = 0;
  
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0,ios::beg);
    ws(iofile);
    getline(iofile, find_name, ',');

    count = 1;
    while (!iofile.eof() && !iofile.fail() && !found)
    {
        iofile>>find_age;
        iofile.ignore();
   
        if(n.compare(find_name)==0 && find_age ==a){
         
            found_rec = count;
            found = true;
        }
        ws(iofile);
        getline(iofile, find_name, ',');
        count++;
        
    }
    iofile.close();
    return found_rec;
}
int DumbDataBase::searchRecord(const string& n){

    int found_age = 0;
    string find_name = "";
    int find_age = 0;
    bool found = false;
  
    iofile.open(filename, ios::in | ios::out);
    iofile.seekg(0,ios::beg);
    ws(iofile);
    getline(iofile, find_name, ',');


    while (!iofile.eof() && !iofile.fail() && !found)
    {
        iofile>>find_age;
        iofile.ignore();
   
        if(n.compare(find_name)==0){
            found = true;
            found_age = find_age;
        }

        ws(iofile);
        getline(iofile, find_name, ',');

        
    }
    iofile.close();
    return found_age;
        

}
void DumbDataBase::deleteRecord(const int& record){
    string find_name = "";
    int find_age = 0;
    iofile.open(filename, ios::in | ios::out );
    iofile.seekg(0,ios::beg);
    ws(iofile);
    getline(iofile, find_name, ',');

    if (record > numRecords)
    {
        cout << "Record does not exist\n";
    }
    else
    {
        iofile.seekg((record - 1) * RECORD_LEN, ios::beg);
        ws(iofile);
        getline(iofile, find_name, ',');
        
        iofile >> find_age;
        find_name[0] ='~';
        cout << "record is " << find_name << " " << find_age << " is now deleted \n"<< endl;
        iofile.seekp((record - 1) * RECORD_LEN, ios::beg);
        iofile << setw(NAME_LEN) << find_name << ","
            << setw(AGE_LEN) << find_age << endl;
        count_deleted++;
        numRecords--;
        
    }
    iofile.close();
    
}

