#include<iostream>
#include "date.h"
using namespace std;
namespace v{
    Date::Date():Date(1,1,1){}
    Date::Date(int dayValue,int monthValue,int yearValue):day(dayValue),month(monthValue),year(yearValue){
        testDate();
    }
    void Date::input(int dayValue,int monthValue,int yearValue){
        day=dayValue;
        month=monthValue;
        year=yearValue;
    }
    void Date::output() const{
        cout << day;
        switch (month)
        {
        case 1 :
            cout << " January ";
            break;
        case 2 :
            cout << " February ";
            break;
        case 3 :
            cout << " March ";
            break;
        case 4 :
            cout << " April ";
            break;
        case 5 :
            cout << " May ";
            break;
        case 6 :
            cout << " June ";
            break;
        case 7 :
            cout << " July ";
            break;
        case 8 :
            cout << " August ";
            break;
        case 9 :
            cout << " September";
            break;
        case 10 :
            cout << " Octamber ";
            break;
        case 11 :
            cout << " November ";
            break;
        case 12 :
            cout << " December ";
            break;
        default:
            cout << "Error!";
            break;
        }
        cout << year;
    }
     void Date::testDate(){
        if ((month < 1) || (month > 12))
        {
            cout << "Illegal month value!\n";
            exit(1);
        }
        if ((day < 1) || (day > 31))
        {
            cout << "Illegal day value!\n";
            exit(1);
        }
        if ((year < 1) || (year > 2030))
        {
            cout << "Illegal year value!\n";
            exit(1);
        }
    }
}