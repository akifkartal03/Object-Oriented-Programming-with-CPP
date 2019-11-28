#include "owner.h"
#include "viewer.h"
#include "document.h"
#include <fstream>
using namespace eagle;
bool checkUserType(int value);
int operateViewer(vector<Owner> owners);
int operateOwner(vector<Owner>& owners);
Owner createAccount(vector<Owner>& owners);
int main(){
    vector<Owner> bloggers;
    int getUserType=1;
    while (getUserType!=0)
    {
        cout << "Welcome to Our Blog System " << endl;
        cout << "Who are you?"<< endl;
        cout << "[1] I am a visiter"<< endl;
        cout << "[2] I am a blogger"<< endl;
        cout << "[3] Create a blogger account"<< endl;
        cout << "[0] Exit."<< endl;
        cout << "Answer: ";
        cin >> getUserType;
        while (!checkUserType(getUserType))
        {
            cout << "Please enter a correct value: ";
            cin >> getUserType;
        }
        switch (getUserType)
        {
        case 1:
            getUserType=operateViewer(bloggers);
            break;
        case 2:
            getUserType=operateOwner(bloggers);
            break;
         case 3:
            bloggers.push_back(createAccount(bloggers));
            break;
        case 0:
            exit(1);break;
        default:
            break;
        }
    }
    return 0;
}
bool checkUserType(int value){
    return (value<0 || value>3) ? false:true; 
}
int operateViewer(vector<Owner> owners){
    cout << endl;
    Viewer v1;
    int choice=1,choosenBlogger,cPost;
    while (choice!=0)
    {
        v1.menu();
        cout << "Choice: ";
        cin >> choice;
        while (!checkUserType(choice))
        {
            cout << "Please enter a correct value: ";
            cin >> choice;
        }
        cout << endl;
        if (choice==1)
        {
            if (owners.size()==0)
            {
                cout << "There is no blogger yet.\n\n";
                return 10;
            }
            cout << "Please Choose a Blogger: " << endl;
            for (int i = 0; i < owners.size(); i++)
            {
                cout << i+1 << ") " << owners[i].getName() << endl;
            }
            cout << "Enter Blogger Number: ";
            cin >> choosenBlogger;
            cout << endl;
            if (owners[choosenBlogger-1].getSize()==0)
            {
                cout << "this blogger has not a post\n\n";
                return 10;
            }
            owners[choosenBlogger-1].showPosts();
            cout << "Enter Post Number to read: ";
            cin >> cPost;
            cout << endl;
            cout << owners[choosenBlogger-1].getPost(cPost-1).getTitle() << endl;
            cout << owners[choosenBlogger-1].getPost(cPost-1).getText() << endl;
            v1.addReadPost(owners[choosenBlogger-1].getPost(cPost-1));
        }
        else if (choice==2)
        {
            v1.showReadPost();
        }
        else if (choice==0)
        {
            return 10;
        }
    }
    
}
int operateOwner(vector<Owner>& owners){
    cout << endl;
    int ID,user,choice=1;
    string password;
    bool is_true=false;
    cout << "Enter Your ID: ";
    cin >> ID;
    cin.ignore();
    cout << "Enter Your Password: ";
    getline(cin,password);
    while (!is_true)
    {
        for (int i = 0; i < owners.size(); i++)
        {
            if (owners[i].check(ID,password))
            {
                is_true=true;
                user=i;
            }
            
        }
        if (!is_true)
        {
            cout << "Your Informations is wrong enter again!" << endl;
            cout << "Enter Your ID: ";
            cin >> ID;
            cin.ignore();
            cout << "Enter Your Password: ";
            getline(cin,password);
        }
    }
    while (choice!=0)
    {
        cout << endl;
        owners[user].menu();
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        while (choice<0 || choice>5)
        {
            cout << "Please Enter Correctly!" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();
        }
        cout << endl;
        if (choice==1)
        {
            string title,text;
            Document d1;
            cout << "Enter your Post Title: ";
            getline(cin,title);
            cout << "Enter your Post Text: ";
            getline(cin,text);
            d1.setTitle(title);
            d1.setText(text);
            d1.setOwner(owners[user].getPostOwner());
            owners[user].newPost(d1);
        }
        else if (choice==2)
        {
            if (owners[user].getSize()==0)
            {
                cout << "you have not post yet.\n";
            }
            else
            {
                string title;
                cout << "Enter your Post Title that you want to delete: ";
                getline(cin,title);
                if (owners[user].deletePost(title))
                {
                    cout << "Your post is deleted. " << endl; 
                }
                else
                {
                    cout << "Your post is not found! " << endl;
                }
            }
            
        }
        else if (choice==3)
        {
            owners[user].showPosts();
        }
        else if (choice==4)
        {
            owners[user].showDeletedPost();
        }
        else if (choice==5)
        {
            cout << "Your Name: " << owners[user].getName() << endl;
            cout << "Your ID: " << owners[user].getID() << endl;
            cout << "Your Password: " << owners[user].getPassword() << endl;
            cout << "Your Post Number: " << owners[user].getSize() << endl;
        }
        else if (choice==0)
        {
            return 10;
        }

    }
    
}
Owner createAccount(vector<Owner>& owners){
    cout << endl;
    string name,password;
    int ID,same=0;bool is_in=true;
    Owner tempOwner;
    cout << "Enter your ID: ";
    cin >> ID;
    while (is_in)
    {
        if (owners.size()==0)
        {
            is_in=false;
        }
        for ( int i = 0; i < owners.size(); i++)
        {
            if (owners[i].getID()==ID)
            {
                same++;
            }
            
        }
        if (same==0)
        {
            is_in=false;
        }
        else
        {
            same=0;
            cout << "This ID already Taken!" << endl;
            cout << "Please Enter Again: ";
            cin >> ID;
        }
        
    }
    
    cin.ignore();
    cout << "Enter your Password: ";
    getline(cin,password);
    cout << "Enter your Name: ";
    getline(cin,name);
    tempOwner.setName(name);
    tempOwner.setID(ID);
    tempOwner.setPassword(password);
    cout << "\nYour account is created succesfully. You can entry and share a post.\n\n";
    return tempOwner;
}
