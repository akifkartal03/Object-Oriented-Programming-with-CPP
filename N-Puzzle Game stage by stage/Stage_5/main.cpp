#include "BoardArray1D.h"
#include "BoardArray2D.h"
#include "BoardVector.h"
using namespace eagle;//my namespace
bool CheckMoves(AbstractBoard *ptrArr[],int size);//global function
/*helper functions*/
void getPossibleMoves(AbstractBoard *ptr,char directions[4]);
void testMyCode();
void testMyGlobalFuntion();
void menu1();
void menu2();
string getFileName();
/*a template function to test different type three class*/
template<class T>
void testMyObjects(T& object);
int AbstractBoard::number_Of_Board=0;//initiliaze static variable
int main(){  
    testMyCode();
    return 0;
}
void testMyCode(){
    int choice=1;
    while (choice!=0)
    {
        menu1();
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please Enter a number: ";
        }
        while (choice<0 || choice>4)
        {
            cout << "Please enter a value between 0 and 4: ";
            while(!(cin >> choice)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please Enter a number : ";
            }
        }
        if (choice==1)
        {
            /*test with temp Board Vector*/
            BoardVector tempV;
            testMyObjects(tempV);
            
        }
        else if (choice==2)
        {
            /*test with temp 1D Board*/
            BoardArray1D temp1D;
            testMyObjects(temp1D);
        }
        else if (choice==3)
        {
            /*test with temp 2D Board */
            BoardArray2D temp2D;
            testMyObjects(temp2D);
        }
        else if (choice==4)
        {
            //test global funciton
            testMyGlobalFuntion();
        }
        
    }
    
}
bool CheckMoves(AbstractBoard *ptrArr[],int size){
    char pDirections[4],temp;
    bool result;
    for (int i = 0; i < size-1; i++){
        getPossibleMoves(ptrArr[i],pDirections);//get possible directon of first puzzle
        result=false;//set the result to false
        for (int j = 0; j < 4; j++)
        {
            if (pDirections[j]!='S')
            {
               if (pDirections[j]=='L')
               {
                   temp=ptrArr[i]->lastMove();//save current last move
                   ptrArr[i]->move('L');//make a temp move to the left
                   if (*ptrArr[i]==*ptrArr[i+1])//check the puzzlles
                   {
                       result=true;//update the result
                   }
                   ptrArr[i]->move('R');//move to orijinal puzzle
                   ptrArr[i]->setLastMove(temp);//update last maove
                   ptrArr[i]->setNumberOfMoves(); //number_of_moves-=2
               }
               else if (pDirections[j]=='R')
               {
                   temp=ptrArr[i]->lastMove();
                   ptrArr[i]->move('R');//make a temp move to the right
                   if (*ptrArr[i]==*ptrArr[i+1])
                   {
                       result=true;
                   }
                   ptrArr[i]->move('L');
                   ptrArr[i]->setLastMove(temp);
                   ptrArr[i]->setNumberOfMoves(); 
               }
               else if (pDirections[j]=='U')
               {
                   temp=ptrArr[i]->lastMove();
                   ptrArr[i]->move('U');//make a temp move to the right
                   if (*ptrArr[i]==*ptrArr[i+1])
                   {
                       result=true;
                   }
                   ptrArr[i]->move('D');
                   ptrArr[i]->setLastMove(temp);
                   ptrArr[i]->setNumberOfMoves(); 
               }
               else if (pDirections[j]=='D')
               {
                   temp=ptrArr[i]->lastMove();
                   ptrArr[i]->move('D');//make a temp move to the right
                   if (*ptrArr[i]==*ptrArr[i+1])
                   {
                       result=true;
                   }
                   ptrArr[i]->move('U');
                   ptrArr[i]->setLastMove(temp);
                   ptrArr[i]->setNumberOfMoves(); 
               }
            }
            
        }
        if (result==false)//if we didn't find the one of the possible return false
        {
            return false;
        }
    }
    return result;
    
}
void getPossibleMoves(AbstractBoard *ptr,char directions[4]){
    //this funtion returns possible directions of parameter's puzzle
    for (int i = 0; i < ptr->getRow(); i++)
    {
        for (int j = 0; j < ptr->getColumn(); j++)
        {
            if (ptr->operator()(i,j)==-1)
            {
                if (j-1>=0 && ptr->operator()(i,j-1)!=0)
                    directions[0]='L';
                else
                    directions[0]='S';
                if (j+1<ptr->getColumn() && ptr->operator()(i,j+1)!=0)
                    directions[1]='R';
                else
                    directions[1]='S';
                if (i-1>=0 && ptr->operator()(i-1,j)!=0)
                    directions[2]='U';
                else
                    directions[2]='S';
                if (i+1<ptr->getRow() && ptr->operator()(i+1,j)!=0)
                    directions[3]='D';
                else
                    directions[3]='S';
            }
            
        }
        
    }
    
}
void menu1(){

    cout << "Welcome to HW5 " << endl;
    cout << "[1] Create a Vector Board Object"<< endl;
    cout << "[2] Create a 1D Board Object"<< endl;
    cout << "[3] Create a 2D Board Object"<< endl;
    cout << "[4] Test Global Fuction"<< endl;
    cout << "[0] Exit."<< endl;
    cout << "Answer: ";
}
void menu2(){
    cout << "\n[1] Test print"<< endl;
    cout << "[2] Test readFromFile"<< endl;
    cout << "[3] Test writeToFile"<< endl;
    cout << "[4] Test reset "<< endl;
    cout << "[5] Test setSize"<< endl;
    cout << "[6] Test move"<< endl;
    cout << "[7] Test is_solved"<< endl;
    cout << "[8] Test operator()"<< endl;
    cout << "[9] Test NumberOfBoards"<< endl;
    cout << "[10] Test numberofMoves"<< endl;
    cout << "[11] Test lastMove"<< endl;
    cout << "[0] Main Page."<< endl;
    cout << "NOTE: == operator is tested in test global function.(It is meaningless here)" << endl;
    cout << "NOTE_2: Your board will be updated after some choices. i.e reset" << endl;
    cout << "Answer: ";

}
string getFileName(){
    string name;
    cout << "Enter  a File Name: ";
    cin >> name;
    return name;
}
template<class T>
void testMyObjects(T& object){
    //test my function that is common among my class
    //the "==" operator is tested in global function
    int subChoice=1,row,column,i1,i2;
    char direction;
    cout << "\n***An 3X3 board created succesfully.*** " << endl;
    object.print();
    while (subChoice!=0)
    {
        menu2();
        while(!(cin >> subChoice)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please Enter a number: ";
        }
        while (subChoice<0 || subChoice>11)
        {
            cout << "Please enter a correct value: ";
            while(!(cin >> subChoice)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please Enter a number: ";
            }
        }
        switch (subChoice)
        {
        case 1:
            object.print();break;
        case 2:
            object.readFromFile(getFileName());
            object.print();
            break;
        case 3:
            object.writeToFile(getFileName());
            cout << "Your puzzle saved succesfully." << endl;
            object.print();
            break;
        case 4:
            object.reset();
            object.print();
            break;
        case 5:
            cout << "Enter  a Row vaule: ";
            cin >> row;
            cout << "Enter  a Column vaule: ";
            cin >> column;
            object.setSize(row,column,row*column);
            cout << "Your Puzzle created again.\n";
            object.print();
            break;
        case 6:
            cout << "Enter Your Direction(Upper Case): ";
            cin >> direction;
            while (!object.move(direction))
            {
                cout << "***You can not move this direction!***\n";
                cout << "Enter Your Direction(Upper Case) Again: ";
                cin >> direction;
            }
            object.print();
            break;
        case 7:
            if (object.is_solved())
            {
                cout << "\nYour puzzle was already solved.\n";
            }
            else
            {
                cout << "\nYour puzzle is not solved yet.\n"; 
            }
            object.print();
            break;
        case 8:
            cout << "Enter first index: ";
            cin >> i1;
            cout << "Enter second index: ";
            cin >> i2;
            cout << "\nYour Cell Context is : " << object.operator()(i1,i2) << endl;
            object.print();
            break;
        case 9:
            cout << "\nNumber of Boards created so far : " << object.NumberOfBoards() << endl;
            cout << "*Some of them might come from test global function!" << endl;
            object.print();
            break;
        case 10:
            cout << "\nNumber of moves this board made : " << object.numberofMoves() << endl;
            object.print();
            break;
        case 11:
            cout << "\nThe last move of this board: " << object.lastMove() << endl;
            object.print();
            break;
        default:
            break;
        }
            
    }

}
void testMyGlobalFuntion(){
    //this function tests my global function
    AbstractBoard *ptrArr[4];//create an array of AbstractBoard pointers  
    BoardArray1D boards[4]; //create four 1D object to keep moves
    BoardArray2D b1;//create a 2d object
    for (int i = 0; i < 4; i++) boards[i].readFromFile("akif.txt"); //fill the board
    boards[1].move('R');//move 
    boards[2]=boards[1];
    boards[2].move('R');//move
    boards[3]=boards[2];
    boards[3].move('D');//move
    for (int i = 0; i < 4; i++) //push it the moves to the array of pointers
    {
        ptrArr[i]=&boards[i];//push
        ptrArr[i]->print();//print
    }
    /*test my gloabl function*/
    if (CheckMoves(ptrArr,4))
    {
        cout << "\nYour Moves are Correct!\n\n";
    }
    else
    {
        cout << "\nYour Moves are Invalid!\n\n";
    }
    b1.readFromFile("akif.txt");//fill 2D object
    ptrArr[3]=&b1;//push it an invalid move and test again
    for (int i = 0; i < 4; i++) ptrArr[i]->print(); //print agin
    if (CheckMoves(ptrArr,4))
    {
        cout << "\nYour Moves are Correct!\n\n";
    }
    else
    {
        cout << "\nYour Moves are Invalid!\n\n";
    }
    
}