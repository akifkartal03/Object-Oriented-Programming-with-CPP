#include<iostream>
#include<string>
#include "vehicle.h"
#include "cyberTruck.h"
using namespace v;
using namespace std;
int main(){
    cyberTruck t1("Tesla","Akif Kartal",1523478,2,49000,15.2,500,false,true,3);
    t1.addDamageRecord(22,11,2019,"Los Angeles in California in USA","Glasses was broken in unveil show",10000000);
    cout << t1;
    return 0;
}
