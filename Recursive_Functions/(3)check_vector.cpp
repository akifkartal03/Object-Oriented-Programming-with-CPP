#include<iostream>
#include<vector>
using namespace std;
template<class T>
bool findKey(vector<T> v,T key);
void checkResult(bool value);
template<class T>
vector<T> getRepating(vector<T> v,vector<T>& temp);
int main(){
    bool result;
    vector<int> v1;
    vector<int> repeat;
    v1.push_back(5);
    v1.push_back(10);
    v1.push_back(15);
    v1.push_back(5);
    v1.push_back(15);
    v1.push_back(10);
    v1.push_back(10);
    result=findKey(v1,10);
    checkResult(result);
    result=findKey(v1,50);
    checkResult(result);
    result=findKey(v1,15);
    checkResult(result);
    repeat=getRepating(v1,repeat);
    auto p = repeat.begin();
    cout << "Your repeating values" << endl;
    for ( p=repeat.begin();  p!= repeat.end(); p++)
    {
        cout << *p << endl;
    }
    
}
template<class T>
bool findKey(vector<T> v,T key){
    if (v.size()==0) // base case
    {
        return false;
    }
    else
    {
        if (v[v.size()-1]==key)
        {
            return true;
        }
        v.pop_back();
        return findKey(v,key); 
    }
}
void checkResult(bool value){
    if (value)
    {
        cout << "Your key was found.\n";
    }
    else
    {
        cout << "Your key was not found!\n";
    }
}
template<class T>
vector<T> getRepating(vector<T> v,vector<T>& temp){
    if (v.size()==0)
    {
        return temp;
    }
    else
    {
        T t=v[v.size()-1];
        v.pop_back();
        if (findKey(v,t))
        {
            if (!findKey(temp,t))
                temp.push_back(t);  
        }
        v.push_back(t);
        v.pop_back();
        return getRepating(v,temp);
        
    }
}
