#include<iostream>
using namespace std;
class ComplexNumbers{
public:
	ComplexNumbers(int r,int i);
	ComplexNumbers();
	~ComplexNumbers();
	static int getNumberOfCN(){return numberOfCN;}
	ComplexNumbers operator+(const ComplexNumbers& rightSide);
	ComplexNumbers operator-(const ComplexNumbers& rightSide);
	ComplexNumbers operator*(const ComplexNumbers& rightSide);
	friend ostream& operator<<(ostream& outputstr,const ComplexNumbers& cn2);
	friend istream& operator>>(istream& inputstr,ComplexNumbers& cn2);
	bool operator==(const ComplexNumbers& rightSide);
	ComplexNumbers& operator=(const ComplexNumbers& rightSide);
private:
	static int numberOfCN;
	int real;
	int imag;
};
void testMyClass();
int ComplexNumbers::numberOfCN=0;
int main(){

	testMyClass();
	return 0;
}
ComplexNumbers::ComplexNumbers(int r,int i) : real(r),imag(i){
	numberOfCN++;
}
ComplexNumbers::ComplexNumbers():ComplexNumbers(1,1){
	/*Constructor Delegation*/
}
ComplexNumbers::~ComplexNumbers(){
	numberOfCN--;
}
ComplexNumbers ComplexNumbers::operator+(const ComplexNumbers& rightSide){
	ComplexNumbers temp;
	temp.real=real+rightSide.real;
	temp.imag=imag+rightSide.imag;
	return temp;
}
ComplexNumbers ComplexNumbers::operator-(const ComplexNumbers& rightSide){
	ComplexNumbers temp;
	temp.real=real-rightSide.real;
	temp.imag=imag-rightSide.imag;
	return temp;
}
ComplexNumbers ComplexNumbers::operator*(const ComplexNumbers& rightSide){
	ComplexNumbers temp;
	temp.real=real*rightSide.real-imag*rightSide.imag;
	temp.imag=real*rightSide.imag+imag*rightSide.real;
	return temp;
}
ostream& operator<<(ostream& outputstr,const ComplexNumbers& c){
	outputstr << c.real << " + " << c.imag << "i" << endl;
	return outputstr;
}
istream& operator>>(istream& inputstr, ComplexNumbers& c){
	cout << "Enter real part: ";
	inputstr >> c.real;
	cout << "Enter imaginary part: ";
	inputstr >> c.imag;
	return inputstr;
}

bool ComplexNumbers::operator==(const ComplexNumbers& rightSide){

	return (real==rightSide.real && imag==rightSide.imag) ? true:false;
}
ComplexNumbers& ComplexNumbers::operator=(const ComplexNumbers& rightSide){
	/*
		default assingment operator do same thing 
		I just want tto get writing habit.
	*/
	//member-wise copy
	real=rightSide.real;
	imag=rightSide.imag;
	return *this;
}
void testMyClass(){

	ComplexNumbers number1,number2;
	cin >> number1;
	cin >> number2;
	cout << number1;
	cout << number2;
	cout << "adding result two number: " << number1+number2 << endl;
	cout << "subtraction result two number: " << number1-number2 << endl;
	cout << "multiplication result two number: " << number1*number2 << endl;
	if (number1==number2)
		cout << "Two number are equal!"<< endl;
	else
		cout << "Two number are not equal!"<< endl;
	number1=number2;
	if (number1==number2)
		cout << "Two number are equal!"<< endl;
	else
		cout << "Two number are not equal!"<< endl;
	cout << "Number of objects: " << ComplexNumbers::getNumberOfCN() << endl;
}