/*  Author: Akif Kartal  
/*  Location: TURKEY  
/* Include neccasary files 
/* Since we have templates because of compiler we need to include .cpp files */
#include "GTUContainer.h"
#include "GTUContainer.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUVector.cpp"
#include "GTUVector.h"
using namespace eagle; //my namespace through whole code
/*Global functions*/
template<class GTUIterator,class T>
GTUIterator find(GTUIterator& first,GTUIterator& last,const T& value);
template<class GTUIterator, class UnaryPredicate>
GTUIterator find_if (GTUIterator first, GTUIterator last, UnaryPredicate pred);
template<class GTUIterator, class Function>
Function for_each(GTUIterator first, GTUIterator last, Function print);
/*My other helper functions*/
void testMyClasses();
void testVector();
void testSet();
void testGlobalFunctions();
bool is_my_name(string str);//for find_if()
void show_my_vector(string str);//for for_each()

int main(){
  testMyClasses();
  return 0;
}
template<class GTUIterator,class T>
GTUIterator find(GTUIterator& first,GTUIterator& last,const T& value){
  //find the key value in the range [first,last)  
  while (first!=last) {
    if (*first==value){
      return first; //if you find return iterator
    }
    ++first;
  }
  return last; // if you don't find return last iterator
}
template<class GTUIterator, class UnaryPredicate>
GTUIterator find_if (GTUIterator first, GTUIterator last, UnaryPredicate pred)
{
  //find the iterator value in the range [first,last) if pred returns true
  while (first!=last) {
    if (pred(*first)){
      return first; //if you find return iterator
    }
    ++first;
  }
  return last; // if you don't find return last iterator
}
template<class GTUIterator, class Function>
Function for_each(GTUIterator first, GTUIterator last, Function print)
{
  //call the parameter function for every element in the range [first,last)
  while (first!=last) {
    print(*first);
    ++first;
  }
  return print;
}
void testMyClasses(){
  //test my vector and set classes with all method that they have.
  int choice=1;
  while (choice!=0)
  {
    cout << "\nWelcome to HW6 " << endl;
    cout << "[1] Test Set(type char)"<< endl;
    cout << "[2] Test Vector(type int)"<< endl;
    cout << "[3] Test Global fuctions(type string)"<< endl;
    cout << "[0] Exit."<< endl;
    cout << "Answer: ";
    while(!(cin >> choice)){ //input checking
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Please Enter a number: ";
    }
    while (choice<0 || choice>3) //input checking
    {
      cout << "Please enter a correct value: ";
      while(!(cin >> choice)){
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Please Enter a number: ";
      }
    }
    /*check input from keyboard*/
    if (choice==1)
    {
      testSet();
    }
    else if (choice==2)
    {
      testVector();
    }
    else if (choice==3)
    {
      testGlobalFunctions();
    }
    //0 will evaluate in the loop condition   
  }
    
}
void testVector(){
  //test my vector class with all method that it has.
  cout << "\n****Welcome to vector test Program.****\n";
  try
  {
    GTUVector<int> v; //create a integer vector and call neccesary method
    cout << "\nInformations About your integer vector.\n";
    cout << "Empty: ";
    if (v.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << v.size() << endl;
    cout << "Max size: " << v.max_size() << endl;
    cout << "\nInserting...\n";
    for (int i = 1; i <= 20; i++)
    {
      v.insert(i); // the other overload of insert will be used in testGlobal fuction
    }
    cout << "\nTracing with vector iterator after inserting...\n";
    GTUVector<int>::baseIterator p; //create a iterator from vector class
    for (p=v.begin(); p!=v.end(); p++)
    {
        cout << *p << endl; 
    }
    cout << "\nErasing some of them...\n";
    for (int i = 5; i < 10; i++)
    {
      v.erase(i);
    }
    cout << "\nTracing with GTUIterator after erasing...\n";
    GTUIterator<int> iter; //create a iterator from GTUIterator class
    for (iter=v.begin(); iter!=v.end(); iter++)
    {
        cout << *iter << endl; 
    }
    /*Test index operator and methods*/
    cout << "Your 5th element of vector: ";
    cout << v[5] << endl;
    cout << "\nChanging of 5th element: ";
    v[5]=-5;
    cout << v[5] << endl;
    cout << "\nFirst element of vector: ";
    cout << *v.begin()<< endl;
    cout << "\nLast element of vector: ";
    cout << *(--v.end())<< endl;
    cout << "\nInformations About your integer vector.\n";
    cout << "Empty: ";
    if (v.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << v.size() << endl;
    cout << "Max size: " << v.max_size() << endl;
    cout << "\nClearing Vector...\n"; 
    v.clear();
    cout << "\nInformations About your integer vector.After cleaning\n";
    cout << "Empty: ";
    if (v.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << v.size() << endl;
    cout << "Max size: " << v.max_size() << endl;
    cout << "\nTesting Second overload of insert function for vector with string...\n";
    /*test set second overload of insert with string*/
    GTUVector<string> s1;
    GTUVector<string>::baseIterator c;
    c=s1.begin();
    s1.insert(c,"Thank you."); //position and value
    c++;
    s1.insert(c,"Have a nice day!");
    for_each(s1.begin(),s1.end(),show_my_vector);//show the vector context
  }
  catch(const MyException e) //catch errors
  {
    cerr << e.getExceptionDetails() << endl;
    cerr << "Test is stopping..." << endl;
  }
}
void testSet(){
  //test my set class with all method that it has.
  cout << "\n****Welcome to Set test Program.****\n";
  try
  {
    GTUSet<char> s; //create a char type set
    /*Test methods*/
    cout << "\nInformations About your char set.\n";
    cout << "Empty: ";
    if (s.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << s.size() << endl;
    cout << "Max size: " << s.max_size() << endl;
    cout << "\nInserting...\n";
    for (int i = 97; i <= 117; i++)
    {
      s.insert(char(i)); //insert them by using converting from ascii code to a character
    }
    cout << "\nTracing with set iterator after inserting...\n";
    GTUSet<char>::baseIterator p; //create a iterator from vector class
    for (p=s.begin(); p!=s.end(); p++)
    {
        cout << *p << endl; 
    }
    cout << "\nErasing some of them...\n";
    for (int i = 105; i < 110; i++)
    {
      s.erase(char(i)); //erase some of them by using converting from ascii code to a character
    }
    cout << "\nTracing with GTUIterator after erasing...\n";
    GTUIterator<char> iter; //create a iterator from GTUIterator class
    for (iter=s.begin(); iter!=s.end(); iter++)
    {
        cout << *iter << endl; 
    }
    /*Test methods*/
    cout << "\nFirst element of set: ";
    cout << *s.begin()<< endl;
    cout << "\nLast element of set: ";
    cout << *(--s.end())<< endl;
    cout << "\nInformations About your char set.\n";
    cout << "Empty: ";
    if (s.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << s.size() << endl;
    cout << "Max size: " << s.max_size() << endl;
    cout << "\nClearing Set...\n"; 
    s.clear();
    cout << "\nInformations About your char set.After cleaning\n";
    cout << "Empty: ";
    if (s.empty())
      cout << "Yes\n";
    else
      cout << "No\n";
    cout << "Size: " << s.size() << endl;
    cout << "Max size: " << s.max_size() << endl;
    cout << "\nTesting Second overload of insert function for set with string...\n";
    /*test set second overload of insert with string*/
    GTUSet<string> s1;
    GTUSet<string>::baseIterator c;
    c=s1.begin();
    s1.insert(c,"Thank you."); //position and value
    c++;
    s1.insert(c,"Have a nice day!");
    for_each(s1.begin(),s1.end(),show_my_vector);//show my set

  }
  catch(const MyException e)
  {
    //catch exceptions
    cerr << e.getExceptionDetails() << endl;
    cerr << "Test is stopping..." << endl;
  }
  
}
void testGlobalFunctions(){

  /* a testable vector with constant iterator*/
  cout << "\nVector is creating with position and string names..." << endl;
  GTUVector<string> s1; //create a vector of string
  GTUVector<string>::baseIterator p; //inner vector iterator
  p=s1.begin();
  /*insert element in the vector by using second overloading of insert method*/
  s1.insert(p,"akif");
  ++p;
  s1.insert(p,"ali");
  ++p;
  s1.insert(p,"derya");
  ++p;
  s1.insert(p,"metin");
  ++p;
  s1.insert(p,"abbas");
  ++p;
  s1.insert(p,"elif");
  /* create 3 const inner iterator */
  GTUVector<string>::const_baseIterator first;
  GTUVector<string>::const_baseIterator last;
  GTUVector<string>::const_baseIterator result;
  first=s1.begin();
  last=s1.end();
  cout << "\nYour vector: \n\n";
  for_each(first,last,show_my_vector);//show my vector by using for_ach function
  first=s1.begin();
  last=s1.end();
  /*find() function test*/
  cout << "\n***find() function test result*** \n";
  cout << "\nSearch for ""metin"" \n";
  result=find(first,last,"metin");
  if (result!=last)
  {
    std::cout << "Your request found in vector: " << *result << endl;
  }
  else
  {
    std::cout << "Your request not found in vector\n";
  }
  /*first and last has changed in the find() fuction*/
  first=s1.begin();
  last=s1.end();
  cout << "\nSearch for ""ahmet"" \n";
  result=find(first,last,"ahmet");
  if (result!=last)
  {
    std::cout << "Your request was found in vector: " << *result << endl;
  }
  else
  {
    std::cout << "Your request not found in vector\n";
  }
  /*find_if() function test check is my name in vector?*/
  cout << "\n***find_if() function test result*** \n";
  first=s1.begin();
  last=s1.end();
  cout << "\nSearch for my_name\n";
  result=find_if(first,last,is_my_name); //my_name() function searchs for "akif"
  if (result!=last)
  {
    std::cout << "This is your name: " << *result << endl;
  }
  else
  {
    std::cout << "There is no your name in the vector\n";
  }
  cout << "\nErase and search for my_name\n";
  s1.erase("akif"); //erase akif from vector
  first=s1.begin();
  last=s1.end();
  result=find_if(first,last,is_my_name); //search for again
  if (result!=last)
  {
    std::cout << "This is your name: " << *result << endl;
  }
  else
  {
    std::cout << "There is no your name in the vector\n";
  }
  cout << "\n***for_each() function test result*** \n";
  first=s1.begin();
  last=s1.end();
  cout << "\nYour vector is\n\n";
  for_each(first,last,show_my_vector); //show my vector

}
bool is_my_name(string str){
  return str=="akif"; //search for "akif"
}
void show_my_vector(string str){
  cout << str << endl; //print str to the screen
}