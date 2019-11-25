#ifndef person
#define person
#include<iostream>
using std::string;
namespace v{
    class Person{
    public:
        Person();
        Person(string n,int id);
        string getName() const{return name;}
        int getID() const{return ID;}
        void setID(int id){ID=id;}
        void setName(string n){name=n;}
        Person& operator=(const Person& rightside);
    private:
        string name;
        int ID;
    };
}
#endif