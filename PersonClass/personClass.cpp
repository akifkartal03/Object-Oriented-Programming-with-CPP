#include<iostream>
#include<string>
using namespace std;
class Person{
public:
	Person();
	static int getNumberOfPerson(){return objectNumber;}
	bool operator==(const Person& p2);
	bool operator!=(const Person& p2);
	void operator++(int a);
	friend ostream& operator<<(ostream& outputStr,const Person& p1);
	bool operator<(const Person& p2);
	int getAge(){return age;}
private:
	string fn,ln;
	int age=10;
	bool gender=false;
	static int objectNumber;
};
int Person::objectNumber=0;
void testMyClass();
int main(){

	testMyClass();
	return 0;
}
Person::Person(){
	int c;
	cout << "enter fn: ";
	cin >> fn;
	cout << "enter ln: ";
	cin >> ln;
	do {
		cout << "enter age: ";
	 	cin >> age;
	}while(age<0);
		cout << "enter gender(1-male / 2- female: ";
	cin >> c;
	if (c==1)
	{
		gender=true;
	}
	else if(c==2){
		gender=false;
	}
	else{
		gender=true;
	}
	objectNumber++;
}
bool Person::operator==(const Person& p2){
	if (fn==p2.fn && ln==p2.ln && age==p2.age && gender==p2.gender)
		return true;
	else
		return false;
}
bool Person::operator!=(const Person& p2){
	return !(*this==p2);
}
void Person::operator++(int a){
	age++;
}
ostream& operator<<(ostream& outputstr,const Person& p1){

	outputstr << "Person Information:\n";
	outputstr << "fname: " << p1.fn << endl;
	outputstr <<"lname: " << p1.ln << endl;
	outputstr << "age: " << p1.age << endl;
	return outputstr;
}
bool Person::operator<(const Person& p2){
	return (age<p2.age) ? true:false;
}
void testMyClass(){


	Person ali,veli;
	cout << ali;
	cout << veli;
	cout << "<< was tested....\n";
	if (ali==veli)
	{
		cout << "Both of them are same person !" << endl;
	}
	else{
		cout << "Both of them are different person !" << endl;
	}
	cout << "== was tested....\n";
	if (ali!=veli)
	{
		cout << "Both of them are different person !" << endl;
	}
	else{
		cout << "Both of them are same person !" << endl;
	}
	cout << "!= was tested....\n";
	cout << "ali's age before: " << ali.getAge() << endl;
	ali++;
	cout << "ali's age now: " << ali.getAge() << endl;	
	cout << "++ was tested....\n";
	if (ali<veli)
	{
		cout << "ali is younger than veli!" << endl;
	}
	else{
		cout << "veli is younger than ali!" << endl;
	}
	cout << "< was tested....\n";
	cout << "Total person: " << Person::getNumberOfPerson() << endl;
	cout << "static was tested....\n";

}