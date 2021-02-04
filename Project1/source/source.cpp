#include<iostream>
#include<fstream>
#include "source.h"
using namespace std;

int TakeNumberFromUser(int flag){
    int number;
    if (flag==1)
    {
        cout << "Please enter widht: ";
    }
    else if (flag==2)
    {
        cout << "Please enter height: ";
    }
    else if (flag==3)
    {
        cout << "Please enter radious: ";
    }
    
    cin >> number;
    return number;
}
char TakeCharacterFromUser(int flag){
    char a_char;
    if (flag==1)
    {
        cout << "Please enter the main container shape (R, C): ";
    }
    else
    {
        cout << "Please enter the small container shape (R, C): ";
    }
    
    cin >> a_char;
    return a_char;

}
container cont(){
    container conta;
    char c;
    bool result;
    int weight,height,rad,side;
    c=TakeCharacterFromUser(1);
    result=CheckValidtyOfCharacter(c);
    while(result==false)
    {
        cout << "Enter a valid main container shape!\n";
        c=TakeCharacterFromUser(1);
        result=CheckValidtyOfCharacter(c);
    }
    switch (c)
    {
    case 'R':
        
        height=TakeNumberFromUser(2);
        while (height<0)
        {
            cout << "Please enter a valid height!\n";
            height=TakeNumberFromUser(2);
        }
        
        weight=TakeNumberFromUser(1);
        while (weight<0)
        {
            cout << "Please enter a valid weight!\n";
            weight=TakeNumberFromUser(1);
        }
        conta.main_shape=shape::rectangle;
        conta.rect1.weight=weight;
        conta.rect1.height=height;
        break;
    case 'C':
        
        rad=TakeNumberFromUser(3);
        while (rad<0)
        {
            cout << "Please enter a valid radious!\n";
            rad=TakeNumberFromUser(3);
        }
        conta.main_shape=shape::circle;
        conta.circ1.rad=rad;
        break;
    default:
        cout << "Please enter a valid shape!\n";
        break;
    }
    c=TakeCharacterFromUser(2);
    result=CheckValidtyOfCharacter(c);
    while(result==false)
    {
        cout << "Enter a valid small container shape (R, C)!\n";
        c=TakeCharacterFromUser(2);
        result=CheckValidtyOfCharacter(c);
    }
    switch (c)
    {
    case 'R':
        
        height=TakeNumberFromUser(2);
        while (height<0)
        {
            cout << "Please enter valid height!\n";
            height=TakeNumberFromUser(2);
        }
        
        weight=TakeNumberFromUser(1);
        while (weight<0)
        {
            cout << "Please enter a valid weight!\n";
            weight=TakeNumberFromUser(1);
        }
        conta.small_shape=shape::rectangle;
        conta.rect2.weight=weight;
        conta.rect2.height=height;
        break;
    case 'C':
        
        rad=TakeNumberFromUser(3);
        while (rad<0)
        {
            cout << "Please enter a valid radious!\n";
            rad=TakeNumberFromUser(3);
        }
        conta.small_shape=shape::circle;
        conta.circ2.rad=rad;
        break;
    default:
        cout << "Please enter a valid shape!\n";
        break;
    }
    return conta;
}
bool CheckValidtyOfCharacter(const char input){
    if (input=='R'|| input=='C')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void makefile(container a_cont){
    ofstream outstream;
    outstream.open("akif.svg");
    outstream << "<svg version=\"vrs\" baseProfile=\"full\" width=\"full\" height=\"full\" xmlns=\"http://www.w3.org/2000/svg\">";
    if (a_cont.main_shape==shape::rectangle)
    {
        
        outstream << "<rect width=\"" 
            << a_cont.rect1.weight << "\" height=\"" << a_cont.rect1.height  << "\" fill=\"red\" />" << "\" fill=\"rec\" />" ;
        if (a_cont.small_shape==shape::rectangle)
        {
            if (a_cont.rect2.height <= a_cont.rect1.height && a_cont.rect2.weight<=a_cont.rect1.weight)
            {
                outstream << "<rect width=\"" 
            << a_cont.rect2.weight << "\" height=\"" << a_cont.rect2.height << "\" fill=\"green\" />" << "\" fill=\"rec\" />" << "</svg>";
            }
            else if (a_cont.rect2.height >= a_cont.rect1.height && a_cont.rect2.weight<=a_cont.rect1.weight)//rotate
            {
                 outstream << "<rect width=\"" 
            << a_cont.rect2.height << "\" height=\"" << a_cont.rect2.weight << "\" fill=\"green\" />" << "\" fill=\"rec\" />" << "</svg>";
            }
            else
            {
                outstream  << "</svg>";
                cout << "There is no space for your small shape !\n";
                cout << "The empty area (red) in container is " << a_cont.rect1.weight*a_cont.rect1.height << endl;
            }
            
        }
        if (a_cont.small_shape==shape::circle)
        {
            if (a_cont.circ2.rad*2 <= a_cont.rect1.height && a_cont.circ2.rad*2<=a_cont.rect1.weight)
            {
                outstream  << " <circle cx=\"" << a_cont.circ2.rad <<"\" cy=\"" << a_cont.circ2.rad <<"\" r=\"" << a_cont.circ2.rad << "\" fill=\"green\" />" 
            << "</svg>";
            
            }
            else
            {
                outstream  << "</svg>";
                cout << "There is no space for your small shape !\n";
                cout << "The empty area (red) in container is " << a_cont.rect1.weight*a_cont.rect1.height << endl;
            }
            
        }
        
        
       /* outstream  << " <circle cx=\"" << a_cont.circ2.rad <<"\" cy=\"" << a_cont.circ2.rad <<"\" r=\"" << a_cont.circ2.rad << "\" fill=\"green\" />" 
            << "</svg>";*/
           
    }
    if (a_cont.main_shape==shape::circle)
    {
        
        outstream  << " <circle cx=\"" << a_cont.circ1.rad <<"\" cy=\"" << a_cont.circ1.rad <<"\" r=\"" << a_cont.circ1.rad << "\" fill=\"red\" />";
        if (a_cont.small_shape==shape::rectangle)
        {
            if (a_cont.rect2.height <= a_cont.circ1.rad*2 && a_cont.rect2.weight<=a_cont.circ1.rad*2)
            {
                outstream << "<rect width=\"" 
            << a_cont.rect2.weight << "\" height=\"" << a_cont.rect2.height << "\" fill=\"green\" />" << "\" fill=\"rec\" />" << "</svg>";
            }
            else
            {
                outstream  << "</svg>";
                cout << "There is no space for your small shape !\n";
                cout << "The empty area (red) in container is " << 3.14*a_cont.circ1.rad*a_cont.circ1.rad << endl;
            }
            
        }
        if (a_cont.small_shape==shape::circle)
        {
            if (a_cont.circ2.rad*2 <= a_cont.circ1.rad*2 && a_cont.circ2.rad*2<=a_cont.circ1.rad*2)
            {
                outstream  << " <circle cx=\"" << a_cont.circ2.rad <<"\" cy=\"" << a_cont.circ2.rad <<"\" r=\"" << a_cont.circ2.rad << "\" fill=\"green\" />" 
            << "</svg>";
            }
            else
            {
                outstream  << "</svg>";
                cout << "There is no space for your small shape !\n";
                cout << "The empty area (red) in container is " << 3.14*a_cont.circ1.rad*a_cont.circ1.rad << endl;
            }
            
        }
        
        
       /* outstream  << " <circle cx=\"" << a_cont.circ2.rad <<"\" cy=\"" << a_cont.circ2.rad <<"\" r=\"" << a_cont.circ2.rad << "\" fill=\"green\" />" 
            << "</svg>";*/
           
    }
}
container checkshape(int flag,char shape){

    container conta;
    switch (shape)
    {
    case 'R':
        
        conta.rect1.height=TakeNumberFromUser(2);
        while (conta.rect1.height<0)
        {
            cout << "Please enter a valid height!\n";
            conta.rect1.height=TakeNumberFromUser(2);
        }
        
        conta.rect1.weight=TakeNumberFromUser(1);
        while (conta.rect1.weight<0)
        {
            cout << "Please enter a valid weight!\n";
            conta.rect1.weight=TakeNumberFromUser(1);
        }
        conta.main_shape=shape::rectangle;
        break;
    case 'C':
        
        conta.circ1.rad=TakeNumberFromUser(3);
        while (conta.circ1.rad<0)
        {
            cout << "Please enter a valid radious!\n";
            conta.circ1.rad=TakeNumberFromUser(3);
        }
        conta.main_shape=shape::circle;
        break;
    default:
        cout << "Please enter a valid shape!\n";
        break;
    }
}
