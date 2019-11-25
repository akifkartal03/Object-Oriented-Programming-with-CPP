#include<iostream>
#include "vehicle.h"
using namespace v;
using namespace std;
namespace v{
    Vehicle::Vehicle():Vehicle("","",0,1,0,1){
        /*intentionally left blank*/
        /*constructor delegation*/
    }
    Vehicle::Vehicle(string manuName,string ownerName,int ownerID,int cylinder,int prce,int capacityOfDamage):
        manufacterName(manuName),owner(ownerName,ownerID),numberOfCylinder(cylinder),price(prce),damageCapacity(capacityOfDamage),damageSize(0){

        if (numberOfCylinder < 1 || price < 0 )
        {
            cout << "your values are not valid!" << endl;
            exit(1);
        }
        damages=new damageRecord[damageCapacity];
    }
    Vehicle::Vehicle(const Vehicle& vObject):
        manufacterName(vObject.manufacterName),owner(vObject.owner.getName(),vObject.owner.getID()),numberOfCylinder(vObject.numberOfCylinder),price(vObject.price),damageCapacity(vObject.damageCapacity),damageSize(vObject.damageSize){
        damages=new damageRecord[damageCapacity];
        for (int i = 0; i < damageSize; i++)
        {
            damages[i]=vObject.damages[i];
        }
            
    }
    Vehicle& Vehicle::operator=(const Vehicle& rightSide){

        if (damageCapacity<rightSide.damageSize)
        {
            delete[] damages;
            damageCapacity=rightSide.damageSize*2;
            damages=new damageRecord[damageCapacity];
        }
        damageSize=rightSide.damageSize;
        for (int i = 0; i < damageSize; i++)
        {
            damages[i]=rightSide.damages[i];
        }
        manufacterName=rightSide.manufacterName;
        owner=rightSide.owner;
        numberOfCylinder=rightSide.numberOfCylinder;
        price=rightSide.price;
        return *this;
    }
    void Vehicle::addDamageRecord(int day,int month,int year,string position,string explain,int cost){
        if (damageCapacity==damageSize){

            damageCapacity=damageSize*2;  
            damageRecord* temp = new damageRecord[damageCapacity];
            for (int i = 0; i < damageSize; i++)
            {
                temp[i]=damages[i];
            }
            delete[] damages;
            damages=new damageRecord[damageCapacity];
            for (int i = 0; i < damageSize; i++)
            {
                damages[i]=temp[i];
            }      
        }
        damages[damageSize].setDate(day,month,year);
        damages[damageSize].setLocation(position);
        damages[damageSize].setExplain(explain);
        damages[damageSize].setCost(cost);
        damageSize++;
    }
    Vehicle::~Vehicle(){
        delete[] damages;
    }

}
