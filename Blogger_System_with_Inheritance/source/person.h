#ifndef PERSON
#define PERSON
#include<iostream>
using std::string;
namespace eagle{
    class Person{
    public:
        Person();
        Person(string nameValue,int id,string passwordValue);
        string getName() const{return name;}
        int getID() const{return ID;}
        string getPassword() const{return password;}
        void setPassword(string p){password=p;}
        void setID(int id){ID=id;}
        void setName(string n){name=n;}
        bool checkInformation(int id, string passwordValue);
    private:
        string name;
        int ID;
        string password;
    };
}
#endif