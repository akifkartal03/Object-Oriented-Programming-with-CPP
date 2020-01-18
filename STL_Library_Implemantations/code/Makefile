hw6 : main.o GTUIterator.o GTUIteratorConst.o GTUContainer.o GTUSet.o GTUVector.o MyException.o
	g++ main.o GTUIterator.o GTUIteratorConst.o GTUContainer.o GTUSet.o GTUVector.o MyException.o -o run 

main.o : main.cpp
	g++ -c main.cpp -std=c++11

iter.o : GTUIterator.cpp
	g++ -c GTUIterator.cpp -std=c++11

constIter.o : GTUIteratorConst.cpp
	g++ -c GTUIteratorConst.cpp -std=c++11

cont.o : GTUContainer.cpp
	g++ -c GTUContainer.cpp -std=c++11

set.o : GTUSet.cpp
	g++ -c GTUSet.cpp -std=c++11

vector.o : GTUVector.cpp
	g++ -c GTUVector.cpp -std=c++11

excp.o : MyException.cpp
	g++ -c MyException.cpp -std=c++11

clean :
	rm *.o run