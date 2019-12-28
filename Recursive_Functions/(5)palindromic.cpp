#include<iostream>
#include<vector>
using namespace std;
/*Palindromic number*/
void palindNumber(int number,bool& result);
int findNumberOfDigit(int number);
int getFirstDigit(int numberOfDigit,int number);
int getNumber(int numberOfDigit,int number);
void getResultNumber(bool res);
/*palindromic string*/
void palindString(string str,bool& result);
int sizeOfStr(string str);
void getResultString(bool res);
int main(){
    bool res=true;
    palindNumber(121,res);
    getResultNumber(res);
    res=true;
    palindNumber(120,res);
    getResultNumber(res);
    res=true;
    palindString("kavak",res);
    getResultString(res);
    res=true;
    palindString("akif",res);
    getResultString(res);
}
void palindNumber(int number,bool& result){
    int digit,first,last;
    if (number<10)//base case
    {
        return;
    }
    else
    {
        digit=findNumberOfDigit(number);
        first=getFirstDigit(digit,number);
        last=number%10;
        if (first!=last) //compare first and last digit
        {
           result=false;
        }
        palindNumber(getNumber(digit,number/10),result);
    }
    
}
int findNumberOfDigit(int number){
    int digit=1;
    while(number>10){
        digit++;
        number=number/10;
    }
    return digit;
}
int getFirstDigit(int numberOfDigit,int number){
    int a=1;
    for (int i = 0; i < numberOfDigit-1; i++)
    {
        a=a*10;
    }
    return number/a;
    
}
int getNumber(int numberOfDigit,int number){
    //get rid of first and last digit of function
    int a=1;
    for (int i = 0; i < numberOfDigit-2; i++)
    {
        a=a*10;
    }
    return number%a;
}
void getResultNumber(bool res){
    if (res)
        cout << "This number is a palindromic number.\n";
    else
        cout << "This number is not a palindromic number.\n";
}
void palindString(string str,bool& result){
    int size=sizeOfStr(str);
    if (size<=1)
    {
        return;
    }
    else
    {
        if (str[0]!=str[size-1])
        {
            result=false;
        }
        str[size-1]='\0';//get rid of last element
        palindString(&str[1],result);
    }
}
int sizeOfStr(string str){
    int i;
    for (i = 0; str[i]!='\0'; i++){}
    return i;
}
void getResultString(bool res){
    if (res)
        cout << "This string is a palindromic string.\n";
    else
        cout << "This string is not a palindromic string.\n";
}