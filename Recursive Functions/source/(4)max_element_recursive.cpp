#include<iostream>
#include<vector>
using namespace std;
template<class T>
T maxElement(T arr[],int size,T& max);
int main(){

    int numbers[5]={5,17,-3,7,21};
    int maxN=numbers[0];
    maxN=maxElement(numbers,5,maxN);
    cout << "Your max element is: " << maxN << endl;

}
template<class T>
T maxElement(T arr[],int size,T& max){
    if (size==0)//base case
    {
        return max;
    }
    else
    {
        if (arr[size-1] > max)
        {
            max=arr[size-1];
        }
        return maxElement(arr,--size,max);
    }  
}

template<class T>
T maxElement(T arr[],int size){
    if (size == 1)//base case
        return arr[size-1];
    else
    {
        int max = maxElement(arr,size-1);
        return max > arr[size-1] ? max : arr[size-1];
    }  
}
