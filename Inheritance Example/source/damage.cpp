#include<iostream>
#include "damageRecord.h"
using namespace std;
namespace v{
    damageRecord::damageRecord():damageRecord(1,1,1,"","",0){}
    damageRecord::damageRecord(int day,int month,int year,string loc,string exp,int cst):
    damageDate(day,month,year),location(loc),explain(exp),cost(cst){}
}