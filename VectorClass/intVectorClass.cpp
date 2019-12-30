#include<iostream>
using namespace std;
class GtuVector{
public:
	GtuVector();//no parameter constructor
	GtuVector(int limit);
	/*Big three*/
	GtuVector(const GtuVector& object);
	~GtuVector();
	GtuVector& operator=(const GtuVector& rightSide);
	/*other operations on vector class*/
	GtuVector& operator+=(const GtuVector& rightSide);
	void addElement(int element);
	bool is_full() const;
	int getSize() const ;
	int getCapacity() const;
	void setSize(int s);
	void setCapacity(int c);
	static int getNumberofVector(){return NumberofVect;}
	int& operator[](int index);
	GtuVector intersect(const GtuVector& other);//find common elements between two vector and return them with new vector
	GtuVector concat(const GtuVector& other);//merge two vector and return a new vector
	friend ostream& operator<<(ostream& ouputstr,const GtuVector& v);//print
	GtuVector operator++();//prefix increment
	GtuVector operator++(int);//postfix
private:
	int *a;
	int size;
	int capacity;
	static int NumberofVect;
};
void testMyVector();
int GtuVector::NumberofVect=0;
int main(){
	testMyVector();
}
GtuVector::GtuVector():GtuVector(50){
	/*constructor delegation...*/
}
GtuVector::GtuVector(int limit):capacity(limit),size(0){

	a=new int[capacity];
	NumberofVect++;
}
GtuVector::GtuVector(const GtuVector& object):capacity(object.capacity),size(object.size){

	a=new int[capacity];
	for (int i = 0; i < size; ++i)
	{
		a[i]=object.a[i];
	}
	NumberofVect++;
}
GtuVector::~GtuVector(){
	delete[] a;
	NumberofVect--;
}
GtuVector& GtuVector::operator=(const GtuVector& rightSide){

	if (capacity<=rightSide.size)
	{
		delete[] a;
		a=new int[rightSide.capacity];
		capacity=rightSide.capacity;
	}
	size=rightSide.size;
	for (int i = 0; i < size; ++i)
	{
		a[i]=rightSide.a[i];
	}
	return *this;
}
GtuVector& GtuVector::operator+=(const GtuVector& rightSide){

	int newSize,newCap;
	newSize=size+rightSide.size;
	newCap=capacity+rightSide.capacity;
	if (capacity<=newSize)
	{
		capacity=newSize*2;
		GtuVector temp(capacity);
		for (int i = 0; i < size; ++i)
		{
			temp.a[i]=a[i];
		}
		delete[] a;
		a=new int[capacity];
		for (int i = 0; i < size; ++i)
		{
			a[i]=temp.a[i];
		}
	}
	for (int i = size; i < newSize; ++i)
	{
		a[i]=rightSide.a[i-size];
	}
	size=newSize;
	capacity=newCap;
	return *this;
}
void GtuVector::addElement(int element){
	if (size==capacity)
	{
		capacity=size*2;
		GtuVector temp(capacity);
		for (int i = 0; i < size; ++i)
		{
			temp.a[i]=a[i];
		}
		delete[] a;
		a=new int[capacity];
		*this=temp;
	}
	a[size]=element;
	size++;

}
/*inline member functions*/
inline bool GtuVector::is_full() const{
	return (size==capacity) ? true:false;
	//same as return (size==capacity)
}
inline int GtuVector::getSize() const{ 
	return size;
}
inline int GtuVector::getCapacity() const{
	return capacity;
}
inline void GtuVector::setSize(int s){
	size=s;
}
inline void GtuVector::setCapacity(int c){
	capacity=c;
}
int& GtuVector::operator[](int index){
	if (index>size || index<0)
	{
		cout << "Your index value is not valid!";
		exit(1);
	}
	return a[index];
}
GtuVector GtuVector::intersect(const GtuVector& other){

	int newSize,newCapacity,k=0;
	//size can be maximum smaller vector's size.
	newSize=(size<other.size) ? size:other.size;
	newCapacity=newSize*2;
	GtuVector interVect(newCapacity);
	interVect.setCapacity(newCapacity);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < other.size; j++)
		{
			if (a[i]==other.a[j])
			{
				interVect.a[k]=a[i];
				k++;
			}
		}
	}
	interVect.setSize(k);
	return interVect;
}
GtuVector GtuVector::concat(const GtuVector& other){
	//preCondition: Don't add same elements.
	int newSize,newCapacity,k=0,minSize,bigger;
	newSize=size+other.size;
	newCapacity=newSize*2;
	GtuVector concatVect(newCapacity);
	concatVect.setCapacity(newCapacity);
	if (size<other.size)
	{
		minSize=size;
		bigger=2;
	}
	else{
		minSize=other.size;
		bigger=1;
	}
	for (int i = 0; i < minSize; ++i)
	{
		if (a[i]!=other.a[i])
		{
			concatVect.a[k]=a[i];
			k++;
		}
	}
	if (bigger==1)
	{
		for (int i = minSize; i <size; ++i)
		{
			concatVect.a[k]=a[i];
			k++;
		}
	}
	else{

		for (int i = minSize; i <other.size; ++i)
		{
			concatVect.a[k]=other.a[i];
			k++;
		}
	}
	concatVect.setSize(k);
	return concatVect;
}

ostream& operator<<(ostream& ouputstr,const GtuVector& v){

	ouputstr << "your int vector is: ";
	for (int i = 0; i < v.getSize(); ++i){
		(i==v.getSize()-1) ? ouputstr << v.a[i] << endl : ouputstr << v.a[i] << ", ";
	}
	return ouputstr;
}
GtuVector GtuVector::operator++(int ignoreMe){
	//postfix
	//this operator just increment capacity by one
	GtuVector temp(capacity+1);
	temp=*this;//assingment operator will make deep copy 
	temp.capacity++;
	return temp;  
}
GtuVector GtuVector::operator++(){
	//prefix
	//this operator just increment capacity by two
	GtuVector temp(capacity+2);
	temp=*this; //assingment operator will make deep copy 
	temp.capacity=capacity+2;
	return temp; 
}
void testMyVector(){

	GtuVector v1(20),v2,v3;//v1 has 20 capacity , v2 has 50 capacity,v3 has 50
	for (int i = 0; i < 10; ++i)
	{
		v1.addElement(i);
	}
	for (int i = 7; i <30 ; ++i)
	{
		v2.addElement(i);
	}
	cout << "first values of vectors" << endl;
	cout << v1;
	cout << v2;
	cout << "after += values of vectors" << endl;
	v1+=v2;
	cout << v1;
	cout << "after intersect values of vectors" << endl;
	v3=	v1.intersect(v2);
	cout << v3;
	cout << "after concat values of vectors" << endl;
	cout << v1.concat(v2);
	cout << GtuVector::getNumberofVector() << endl;
	
}
