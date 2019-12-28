#include<iostream>
#include<vector>
using namespace std;
template<class T>
bool findKey(vector<T> v,T key);
void checkResult(bool value);
template<class T>
vector<T> getRepating(vector<T> v);
int main(){
    bool result;
    vector<int> v1;
    vector<int> repeat;
    v1.push_back(5);
    v1.push_back(10);
    v1.push_back(15);
    v1.push_back(5);
    v1.push_back(15);
    result=findKey(v1,10);
    checkResult(result);
    result=findKey(v1,50);
    checkResult(result);
    result=findKey(v1,15);
    checkResult(result);
    repeat=getRepating(v1);
    auto p = repeat.begin();
    cout << "Your repeating values" << endl;
    for ( p=repeat.begin();  p!= repeat.end(); p++)
    {
        cout << *p << endl;
    }
    
}
template<class T>
bool findKey(vector<T> v,T key){
    bool res=false;
    if (v.size()==0) // base case
    {
        return res;
    }
    else
    {
        if (v[v.size()-1]==key)
        {
            return true;
        }
        v.pop_back();
        res=findKey(v,key); 
    }
    return res;
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
vector<T> getRepating(vector<T> v){
    static vector<T> temp;
    if (v.size()==0)
    {
        return temp;
    }
    else
    {
        if (findKey(v,v[v.size()-1]))
        {
            if (v.size()>1)
            {
                auto p = v.begin();
                for ( p=v.begin();  p!= v.end(); p++)
                {
                    if (*p==v[v.size()-1])
                    {
                        break;
                    }
                }
                v.erase(p);
                if (findKey(v,v[v.size()-1]))
                {
                    temp.push_back(v[v.size()-1]);
                }
            }
        }
        v.pop_back();
        getRepating(v);
        
    }
    return temp;
}
