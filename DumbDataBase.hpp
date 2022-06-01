//
//  DumbDataBase.hpp
//  dumbDataBase
//
//  Created by Adrineh Khodaverdian on 5/30/22.
//

#ifndef DumbDataBase_hpp
#define DumbDataBase_hpp

#include <fstream>
using std::string;
const int NAME_LEN = 21;
const int AGE_LEN = 3;
const int RECORD_LEN = NAME_LEN + AGE_LEN + 2;
const char DELETED = '~';


class DumbDataBase{
private:
    std::fstream iofile;
    string nameOfDatabase;
    string filename;
    string name;
    int age;
    int numRecords;
    int count_deleted;
public:
    DumbDataBase(const string& fName);
    void addItem(const string& name, const int& age);
    void replaceItem(const int& record,const string& n, const int& a);
    void printData();
    void sortByName();
    void sortByAge();
    int getRecordNum(string n, int a);
    int searchRecord(const string& n);
    void deleteRecord(const int& recNum);
    
};
#endif /* DumbDataBase_hpp */
