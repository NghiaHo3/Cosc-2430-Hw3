#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "ArgumentManager.h"

template <class Type>
class myStack
{
public:
void initializeStack();
//Function to initialize the stack to an empty state.
//Postcondition: stackTop = 0;
bool isEmptyStack() const;
//Function to determine whether the stack is empty.
//Postcondition: Returns true if the stack is empty,
// otherwise returns false.
bool isFullStack() const;
//Function to determine whether the stack is full.
//Postcondition: Returns true if the stack is full,
// otherwise returns false.
void push(const Type& newItem);
//Function to add newItem to the stack.
//Precondition: The stack exists and is not full.
//Postcondition: The stack is changed and newItem is
// added to the top of the stack.
Type top() const;
//Function to return the top element of the stack.
//Precondition: The stack exists and is not empty.
//Postcondition: If the stack is empty, the program
// terminates; otherwise, the top element of the stack
// is returned.
void pop();
//Function to remove the top element of the stack.
//Precondition: The stack exists and is not empty.
//Postcondition: The stack is changed and the top element is
// removed from the stack.
myStack(int stackSize = 10);
//Constructor
//Create an array of the size stackSize to hold
//the stack elements. The default stack size is 100.
//Postcondition: The variable list contains the base address
// of the array, stackTop = 0, and maxStackSize = stackSize
myStack(const myStack<Type>& otherStack);
//Copy constructor
~myStack();
//Destructor
//Remove all the elements from the stack.
//Postcondition: The array (list) holding the stack
// elements is deleted.
void doubleStackSize();
const myStack<Type>& operator=(const myStack<Type>&);
//Overload the assignment operator.
private:
int maxStackSize; //variable to store the maximum stack size
int stackTop; //variable to point to the top of the stack
Type *list; //pointer to the array that holds the stack elements
Type *list2;//pointer that will point to a 2nd array. This for when you need to double the stack size
};
bool checkNumber(string userWord);
bool checkPunct(string &userWord);
string erasePunct(string &userWord);
string eraseWS(string &userWord);
using namespace std;
int main(int argc, char* argv[])
{

    ifstream ifs("2.txt");
    ofstream ofs("out.txt");

    ///////////////////////////////////////////////////////////////////////////////
    /*
    if(argc<2)
    {
        cout<<"Usage: reverse \"A=<file>;C=<file>\""<<endl;
    }
    ArgumentManager am(argc, argv);
    //initializing input and output stream variable with their correspond file call
    ifstream ifs((am.get("A")).c_str());
    ofstream ofs((am.get("C")).c_str());
    //initializing line and studentInfo object
    */
    /////////////////////////////////////////////////////////////////////////////////
    string word;
    int count=0;
    int maxCount=10;
    int timeDoubled=0;
    myStack<string> wordStack(maxCount);//intiallizing the stack with desired size
    while(ifs>>word){
        if(!checkNumber(word)&&!checkPunct(word)){
        eraseWS(word);
        count++;
        //if(count>maxCount){
        if(wordStack.isFullStack()){
            wordStack.doubleStackSize();
            maxCount*=2;
            timeDoubled++;
        }
        wordStack.push(word);
        }
    }

    while(!wordStack.isEmptyStack()){
        cout<<wordStack.top()<<" ";
        ofs<<wordStack.top()<<" ";
        wordStack.pop();

    }
    cout<<"\n"<<timeDoubled<<endl;
    ofs<<"\n"<<timeDoubled<<endl;



}
//Function that erase whitespace in a nonempty line
string eraseWS(string &userWord){
        //for loop that go through all char in a line and eliminate all whitespace
        int size = userWord.length();
        for(int j = 0; j<=size; j++)
        {
            for(int i = 0; i <=j; i++)
            {
                if(userWord[i] == ' ' && userWord[i+1] == ' ')
                {
                    userWord.erase(userWord.begin() + i);
                }
                else if(userWord[0]== ' ')
                {
                    userWord.erase(userWord.begin());
                }
                else if(userWord[i] == '\0' && userWord[i-1]== ' ')
                {
                    userWord.erase(userWord.end() - 1);
                }
            }
        }
        return userWord;
    }
bool checkPunct(string &userWord){
    char x=userWord.at(0);
    if(ispunct(x)){
       if(x=='"'||
          x=='('){
        userWord.erase(0,1);
       }
       else{
        return true;
       }
    }
    char y=userWord.at(userWord.length()-1);
    if(ispunct(y)){
        if(y==')'||
           y==','||
           y=='.'||
           y==';'||
           y==':'||
           y=='?'||
           y=='\"'||
           y=='!'){
        userWord.erase(userWord.length()-1,1);
        }
        else{
            return true;
        }
    }
    for(int i=0; i<userWord.length();i++)
    {
        if(ispunct(userWord.at(i))){
                if(userWord.at(i)=='\''){
                    return false;
                }
           return true;
        }
    }
    return false;
}
bool checkNumber(string userWord)
{
    for(int i=0; i<userWord.length();i++){
        if(isdigit(userWord.at(i))){
            return true;
        }

    }
    return false;
}

template <class Type>
void myStack<Type>::initializeStack()
{
stackTop = 0;
}//end initializeStack

template <class Type>
bool myStack<Type>::isEmptyStack() const
{
return(stackTop == 0);
}//end isEmptyStack

template <class Type>
bool myStack<Type>::isFullStack() const
{
return(stackTop == maxStackSize);
} //end isFullStack

template <class Type>
void myStack<Type>::push(const Type& newItem)
{
if (!isFullStack())
{
list[stackTop] = newItem; //add newItem at the top
stackTop++; //increment stackTop
}
else
cout << "Cannot add to a full stack." << endl;
}//end push

template <class Type>
Type myStack<Type>::top() const
{
assert(stackTop != 0); //if stack is empty, terminate the
//program
return list[stackTop - 1]; //return the element of the stack
//indicated by stackTop - 1
}//end top

template <class Type>
void myStack<Type>::pop()
{
if (!isEmptyStack())
stackTop--; //decrement stackTop
else
cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void myStack<Type>::doubleStackSize()
{
maxStackSize*=2;
list2=new Type[maxStackSize];
for(int i=0;i<stackTop;i++){
list2[i]=list[i];
}
delete []list;
list=list2;
}

template <class Type>
myStack<Type>::myStack(int stackSize)
{
if (stackSize <= 0)
{
cout << "Size of the array to hold the stack must "
<< "be positive." << endl;
cout << "Creating an array of size 100." << endl;
maxStackSize = 100;
}
else
maxStackSize = stackSize; //set the stack size to
//the value specified by
//the parameter stackSize
stackTop = 0; //set stackTop to 0
list = new Type[maxStackSize]; //create the array to
//hold the stack elements
}//end constructor

template <class Type>
myStack<Type>::~myStack() //destructor
{
delete [] list; //deallocate the memory occupied
//by the array
}//end destructor

template <class Type>
myStack<Type>::myStack(const myStack<Type>& otherStack)
{
list = NULL;
copyStack(otherStack);
}//end copy constructor

template <class Type>
const myStack<Type>& myStack<Type>::operator=
(const myStack<Type>& otherStack)
{
if (this != &otherStack) //avoid self-copy
copyStack(otherStack);
return *this;
} //end operator=

