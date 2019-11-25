#include<iostream>
#include "person.h"
using namespace std;
namespace v{
    Person::Person():Person("",0){
    }
    Person::Person(string n,int id):name(n),ID(id){
    }
    Person& Person::operator=(const Person& rightside){
        setID(rightside.getID());
        setName(rightside.getName());
    }

}