#include<iostream>
#include<vector>
using namespace std;
template<class T>
T maxElement(T arr[],int size);
int main(){

    int numbers[5]={5,17,-3,7,11};
    int maxN;
    maxN=maxElement(numbers,5);
    cout << "Your max element is: " << maxN << endl;

}
template<class T>
T maxElement(T arr[],int size){
    static T max=arr[0];
    if (size==0)//base case
    {
        return max;
    }
    else
    {
        if (arr[0] > max)
        {
            max=arr[0];
        }
        maxElement(&arr[1],size-1);
    }
    return max;
    
    
}