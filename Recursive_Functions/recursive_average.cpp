#include<iostream>
#include<vector>
using namespace std;
template<class T>
double average(vector<T> v);
int main(){

 double avg;
 vector<int> v1;
 v1.push_back(5);
 v1.push_back(10);
 v1.push_back(15);
 v1.push_back(5);
 avg=average(v1);
 cout << "Average is: " << avg << endl;

}
template<class T>
double average(vector<T> v){
    static T sum=0;
    static int size=v.size();
    if (v.size()==0) //base case
    {
        return 0;
    }
    else //recursive case
    {
        sum=sum+v[v.size()-1];
        v.pop_back();
        average(v);
    }
    return sum/(double)size;
}
