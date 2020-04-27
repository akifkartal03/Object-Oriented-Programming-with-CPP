#ifndef damagerecord
#define damagerecord
#include<iostream>
#include "date.h"
using namespace std;
namespace v{
    class damageRecord{
    public:
        damageRecord();
        damageRecord(int day,int month,int year,string loc,string exp,int cst);
        void getDate() const {damageDate.output();}
        int getCost() const{return cost;}
        string getLocation() const{return location;}
        string getExplain() const {return explain;}
        void setDate(int day,int month,int year) {damageDate.input(day,month,year);}
        void setLocation(string loc){location=loc;}
        void setCost(int c){cost=c;}
        void setExplain(string exp){explain=exp;}
    private:
        Date damageDate;
        string location;
        string explain;
        int cost; 
    };
}
#endif