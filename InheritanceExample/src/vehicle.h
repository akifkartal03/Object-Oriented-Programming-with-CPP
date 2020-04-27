#ifndef vehicle
#define vehicle
#include<iostream>
#include<string>
#include "person.h"
#include "damageRecord.h"
using std::string;
namespace v{
    class Vehicle{
    public:
        Vehicle();
        Vehicle(string manuName,string ownerName,int ownerID,int cylinder,int prce,int capacityOfDamage);
        /*Big three*/
        Vehicle(const Vehicle& vObject);
        Vehicle& operator=(const Vehicle& rightSide);
        ~Vehicle();
        /*-------------------------------*/
        void addDamageRecord(int day,int month,int year,string position,string explain,int cost);
        string getName() const{return manufacterName;}
        int getCylinder() const{return numberOfCylinder;}
        int getPrice() const{return price;}
        string getOwnerName() const{return owner.getName();}
        int getId() const{return owner.getID();}
        void SetName(string n){manufacterName=n;}
        void SetCylinder(int c){numberOfCylinder=c;}
        void setPrice(int p){price=p;}
    protected:
        damageRecord* damages;
        int damageCapacity;
        int damageSize;
    private: 
        string manufacterName;
        int numberOfCylinder;
        int price;
        Person owner;
    };
}
#endif