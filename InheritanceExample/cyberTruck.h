#ifndef cybertruck
#define cybertruck
#include<iostream>
#include "vehicle.h"
#include "person.h"
using namespace std;
namespace v{
    class cyberTruck : public Vehicle{
    public:
        cyberTruck();
        cyberTruck(string manuName,string ownName,int ownID, int cylinderr, int prce,double loadCap,int towCap,bool glass,bool sDrive,int capacityDamage);
        /*Big three*/
        cyberTruck(const cyberTruck& ctObject);
        cyberTruck& operator=(const cyberTruck& rightSide);
        ~cyberTruck();
        double getLoadCap() const {return loadCapacity;}
        int getTowingCap() const{return towingCpacity;}
        bool getSelfDrive() const{return selfDrive;}
        bool getGlass() const {return safetyGlass;}
        void setLoadCapacity(double lc) {loadCapacity=lc;}
        void setTowCap(int tc){towingCpacity=tc;}
        void setSelfDrive(bool d){selfDrive=d;}
        void setGlass(bool glass){safetyGlass=glass;}
        friend ostream& operator<<(ostream& output, const cyberTruck& t);
    private:
        double loadCapacity;
        int towingCpacity;
        bool safetyGlass,selfDrive;  
    };

}
#endif