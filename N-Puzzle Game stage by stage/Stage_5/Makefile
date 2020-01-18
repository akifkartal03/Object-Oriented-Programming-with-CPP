hw6 : main.o AbstractBoard.o BoardArray1D.o BoardArray2D.o BoardVector.o
	g++ main.o AbstractBoard.o BoardArray1D.o BoardArray2D.o BoardVector.o -o run 

main.o : main.cpp
	g++ -c main.cpp -std=c++11

abs.o : AbstractBoard.cpp
	g++ -c AbstractBoard.cpp -std=c++11

b1d.o : BoardArray1D.cpp
	g++ -c BoardArray1D.cpp -std=c++11

b2d.o : BoardArray2D.cpp
	g++ -c BoardArray2D.cpp -std=c++11

bv.o : BoardVector.cpp
	g++ -c BoardVector.cpp -std=c++11

clean :
	rm *.o run