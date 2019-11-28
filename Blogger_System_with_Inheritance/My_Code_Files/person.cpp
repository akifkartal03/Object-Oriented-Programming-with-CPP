#include "person.h"
namespace eagle{
    Person::Person():Person("",0,""){
    }
    Person::Person(string nameValue,int id,string passwordValue):name(nameValue),ID(id),password(passwordValue){
    }
    bool Person::checkInformation(int id, string passwordValue){
        if (id==ID && passwordValue==password)
             return true;
        else
            return false;
    }

}