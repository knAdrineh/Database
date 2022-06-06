/*
 Adrineh Khodaverdian
 Professro Biehl
 CS/IS 212
 
 implementation of sort, search, delete and change record
 */
/*
 -----------------------------------------------------
                          Ddbase
 -----------------------------------------------------
 -filename: string
 -iofile: fstream
 -count: integer
 -deleted: integer
 -----------------------------------------------------
 +Ddbase(f:string)
 +addRecord(n:string, a:integer):void
 +changeRecord(n:string, a:integer):void
 +deleteRecord(n:string):boolean
 +printRecords():void
 +sortRecords():void
 +searchRecords(n:string, a:integer):integer
 -----------------------------------------------------
 */
#ifndef Ddbase_hpp
#define Ddbase_hpp

#include <string>
#include <fstream>

using std::string;
using std::fstream;

const int NAME_LEN = 21; // includes comma
const int AGE_LEN = 3;
const int RECORD_LEN = NAME_LEN + AGE_LEN + 2;
const char DELETED = '~';

class Ddbase
{
private:
    string name,filename;
    int age;
    int count;
    int deleted;
    fstream iofile;
public:
    Ddbase(string f);
    void addRecord(string n, int a);
    void changeRecord(int recNum, string n, int a);
    bool deleteRecord(string n);
    void printRecords();
    void sortRecords();
    int searchRecords(string n, int& a);
};

#endif /* Ddbase_hpp */
