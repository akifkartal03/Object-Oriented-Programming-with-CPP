#include<iostream>
#include<cstdlib>
using namespace std;
class String{
private:
    char *c;
    int lenght;
public:
    String(int size);//constructor
    /*----Big Three-----*/
    ~String();//destructor
    String& operator=(const String& rightSide);//assingment
    String(const String& strObject);//copy constructor
    /*------other operators on string--------*/
    String& operator+(const String& secondString);
    char& operator[](int index);
    friend ostream& operator<<(ostream& outstream ,const String& myStr); //print
    /*-----some function with strings-------*/
    void addEndOfString(char letter,int lastIndex);
    bool is_full() const ;
    int getLenght() const; 
};
void testMyStringClass();
int main(){
    testMyStringClass();
    return 0;
}
String::String(int size):lenght(size){
    c = new char[size];
}
inline int String::getLenght() const{
    return lenght;
}
String& String::operator=(const String& rightSide){

    if (lenght<rightSide.lenght)
    {
        delete[] c;
        c = new char[rightSide.lenght];
        lenght=rightSide.lenght;
    }
    for (int i = 0; i < lenght; i++)
    {
        c[i]=rightSide.c[i];
    }
    return *this;
    
}
String::String(const String& strObject): lenght(strObject.lenght){
    
    c = new char(lenght);
    for (int i = 0; i < lenght; i++)
    {
        c[i]=strObject.c[i];
    }
    
}
String& String::operator+(const String& secondString){
    String temp(lenght);
    for (int i = 0; i < lenght; i++)
    {
        temp.c[i]=c[i];
    }
    delete [] c;
    lenght=temp.lenght+secondString.lenght;
    c = new char(lenght);
    for (int i = 0; i < temp.lenght; i++)
    {
        c[i]=temp.c[i];
    }
    for (int i = 0; i < secondString.lenght; i++)
    {
        addEndOfString(secondString.c[i],temp.lenght);
        temp.lenght++;
    }
    return *this;
}
char& String::operator[](int index){

    if (index>=lenght)
    {
        cout << "Illegal access for your string!" << endl;
        exit(1);
    }
    return c[index];

}
ostream& operator<<(ostream& outstream, const String& myString){
    for (int i = 0; i < myString.lenght; i++)
    {
        outstream << myString.c[i];
    }
    return outstream;
}
void String::addEndOfString(char letter,int lastIndex){
    c[lastIndex]=letter;
}
String::~String(){
    delete [] c;
}
void testMyStringClass(){
    int size,count=0;
    char letter;
    cout << "Enter lenght of your first string: ";
    cin >> size;
    String s1(size);
    for (int i = 0; i < size; i++)
    {
        cout << "Enter" << i+1 << ". letter: ";
        cin >> letter;
        s1.addEndOfString(letter,i);
    }
    cout << "Enter lenght of your second string: ";
    cin >> size;
    String s2(size);
    for (int i = 0; i < size; i++)
    {
        cout << "Enter" << i+1 << ". letter: ";
        cin >> letter;
        s2.addEndOfString(letter,i);
    }
    cout << "Your first string: " << s1 << endl;
    cout << "Your second string: " << s2 << endl;
    cout << "Your total string: " << s1+s2 << endl;
    
}