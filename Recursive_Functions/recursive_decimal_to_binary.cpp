#include<iostream>
#include<vector>
using namespace std;
void decimalToBinaryRecursive(int number);
int main(){

    decimalToBinaryRecursive(20);
    cout << endl;
    decimalToBinaryRecursive(-30);
    cout << endl;
    return 0;

}
void decimalToBinaryRecursive(int number){
    if (number<0)//check number
    {
        if (number>=-1)//base case 
        {
            cout << "Your number is negatif result is: ";
            cout << -1*number;
        }
        else //recursive case
        {
            decimalToBinaryRecursive(number/2);
            cout << -1*(number%2);
        }
        
    }
    else
    {
        if (number<=1) //base case
        {
            cout << "Your result is: ";
            cout << number;
        }
        else //recursive case
        {
            decimalToBinaryRecursive(number/2);
            cout << number%2;
        }
    }
    
}