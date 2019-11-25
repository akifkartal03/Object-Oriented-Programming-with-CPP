#include<iostream>
#include  "cyberTruck.h"
using namespace std;
namespace v{
    cyberTruck::cyberTruck():cyberTruck("","",0,1,0,0.0,0,false,true,1){
        /*delegation*/
    }
    cyberTruck::cyberTruck(string manuName,string ownName,int ownID, int cylinderr, int prce,double loadCap,int towCap,bool glass,bool sDrive,int capacityDamage):
        Vehicle(manuName,ownName,ownID,cylinderr,prce,capacityDamage),loadCapacity(loadCap),towingCpacity(towCap),selfDrive(sDrive),safetyGlass(glass){
    }
    cyberTruck::cyberTruck(const cyberTruck& ctObject):
        Vehicle(ctObject),loadCapacity(ctObject.loadCapacity),towingCpacity(ctObject.towingCpacity),selfDrive(ctObject.selfDrive),safetyGlass(ctObject.safetyGlass){
    }
    cyberTruck& cyberTruck::operator=(const cyberTruck& rightSide){
        Vehicle::operator=(rightSide);
        loadCapacity=rightSide.loadCapacity;
        towingCpacity=rightSide.towingCpacity;
        selfDrive=rightSide.selfDrive;
        safetyGlass=rightSide.safetyGlass;
    }
    ostream& operator<<(ostream& output,const cyberTruck& t){
        output << "\t*****Information of Your CyberTruck*****" << endl;
        output << "Manufacturer’s Name: " << t.getName()  << endl;
        output << "Owner’s Name: " << t.getOwnerName()  << endl;
        output << "Owner’s ID: " << t.getId()  << endl;
        output << "Number of Cylinder: " << t.getCylinder()  << endl;
        output << "Load Capacity: " << t.getLoadCap()  << endl;
        output << "Towing Capacity: " << t.getTowingCap()  << endl;
        output << "Price Of Truck: " << t.getPrice()  << "$" << endl;
        if (t.getGlass())
            output << "Safety Glass: " << "Yes" << endl;
        else
            output << "Safety Glass: " << "No" << endl;
        if (t.getSelfDrive())
            output << "Self Drive: " << "Yes" << endl;
        else
            output << "Self Drive: " << "No" << endl;
        if (t.damageSize>0)
        {
            for (int i = 0; i <t.damageSize; i++)
            {
                cout << "***Your CyberTruck's " << i+1 << ". Damage Information***" << endl;
                cout << "Damage Date: "; t.damages[i].getDate(); cout << endl;
                cout << "Damage Location: " << t.damages[i].getLocation() << endl;
                cout << "Damage Information: " << t.damages[i].getExplain() << endl;
                cout << "Damage Cost: " << t.damages[i].getCost() << "$" << endl;

            }
            
        }
         
    }
    cyberTruck::~cyberTruck(){
        //base class destructor will call
    }

}