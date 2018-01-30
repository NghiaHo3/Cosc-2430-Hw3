//Nghia Ho
//ID 1251576
//Hw3
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "ArgumentManager.h"
////////////////////////////////////////////////////////////////////////////////////////////
template <class Type>
class myStack
{
public:
    myStack(int stackSize);
//Constructor
//Initialize different variable in the stack such as
//a new dynamic array and the initial maxStackSize
    ~myStack();
//Destructor
//Remove all the elements from the stack.
    bool isEmptyStack() const;
//Fuction that check if stack is empty
    bool isFullStack() const;
//Function to determine whether the stack is full.
    void push(const Type& newItem);
//Function to add newItem to the stack.
    Type top() const;
//Function to return the top element of the stack.
    void pop();
//Function to remove the top element of the stack.
    void doubleStackSize();
//Function to double the current stack size
private:
    int maxStackSize;
//variable to store the maximum stack size
    int stackTop;
//variable to point to the top of the stack
    Type *list;
//pointer to the array that holds the stack elements
    Type *list2;
//pointer that will point to a 2nd new array.
//This for when I need to double the stack size
};
////////////////////////////////////////////////////////////////////////////////////////////
bool checkNumber(string userWord);
//Function that will check if userWord contain a number
bool checkPunct(string &userWord);
//Function that will check if userWord contain specific punctuation
//Function will also erase specific punctuation at the beginning and end of the userWord
string eraseWS(string &userWord);
//Function that will erase any unnecessary whitespace
////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
int main(int argc, char* argv[])
{
    ifstream ifs("10.txt");
    ofstream ofs("out.txt");

////////////////////////////////////////////////////////////////////////////////////////////
    if(argc<2)
    {
        cout<<"Usage: reverse \"A=<file>;C=<file>\""<<endl;
    }
    ArgumentManager am(argc, argv);
    //initializing input and output stream variable with their correspond file call
    //ifstream ifs((am.get("A")).c_str());
    //ofstream ofs((am.get("C")).c_str());
////////////////////////////////////////////////////////////////////////////////////////////
    string word;
    //word variable
    int myStackSize=10;
    //variable that hold initial stackSize
    int timeDoubled=0;
    //variable that count how many time you have double the stack
    myStack<string> wordStack(myStackSize);
    //intiallizing the stack with desired stack size

    while(ifs>>word)
    {
        //Loop that will process every single word in the file
        eraseWS(word);
        //erasing unnecessary whitespace before we begin
        if(!checkNumber(word)&&!checkPunct(word))
        {
            //if statement to check if the word contain specific number or punctuation
            if(wordStack.isFullStack())
            {
                //if statement to check if the stack is currently full
                wordStack.doubleStackSize();
                //Doubling the current stack size if stack is full
                timeDoubled++;
                //Increasing double counter to keep track of how many time we have double so far
            }
            wordStack.push(word);
            //adding the processed word into the stack
        }
    }

    while(!wordStack.isEmptyStack())
    {
        //Loop to print out the stack
        //cout<<wordStack.top()<<" ";
        ofs<<wordStack.top()<<" ";
        wordStack.pop();
        //outputting the top value in the stack and popping it out
        if(wordStack.isEmptyStack())
        {
            //cout<<"\n"<<timeDoubled<<endl;
            ofs<<"\n"<<timeDoubled<<endl;
            //outputting the amount time time we have doubled so far
        }

    }




}
////////////////////////////////////////////////////////////////////////////////////////////
//Function that will erase any unnecessary whitespace
string eraseWS(string &userWord)
{
    //for loop that go through all char in a line and eliminate all whitespace
    int size = userWord.length();
    //variable that hold the userWord length
    for(int j = 0; j<=size; j++)
        //Loop that go through a word looking for whitespace
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
    //return word without unecessary whitespace
}
////////////////////////////////////////////////////////////////////////////////////////////
//Function that will check if userWord contain specific punctuation
//Function will also erase specific punctuation at the beginning and end of the userWord
bool checkPunct(string &userWord)
{
    char x=userWord.at(0);
    //variable x that store char at the beginning of userWord
    //if(ispunct(x))
    if(!isalpha(x))
    {
        //check if x is a punctuation
        if(x=='\"'||
                x=='(')
        {
            //2nd check to see if x is a punctuation
            userWord.erase(0,1);
            //delete that specific punctuation in userWord
        }
        else
        {
            //if x is not a specific punctuation
            if(x!='\'')
            {
                return true;
            }
        }
    }
    char y=userWord.at(userWord.length()-1);
    //variable y that store char at the end of the userWord
    //if(ispunct(y))
    if(!isalpha(y))
    {
        //check if y is a punctuation
        if(y==')'||
                y==','||
                y=='.'||
                y==';'||
                y==':'||
                y=='?'||
                y=='\"'||
                y=='!')
        {
            //2nd check if y is a specific punctuation
            userWord.erase(userWord.length()-1,1);
            //deleting that specific punctuation in the word
        }
        else
        {
            //if y is not that specific punctuation
            if(x!='\'')
            {
                return true;
            }
        }
    }
    for(int i=0; i<userWord.length(); i++)
        //for loop to check the rest of the word to see if they contain a specifics
    {
        //if(ispunct(userWord.at(i)))
        if(!isalpha(userWord.at(i)))
        {
            //check if something in the word is punctuation
            if(userWord.at(i)=='\'')
            {
                //check if that specific punctuation is '
                return false;
            }
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
//Function that will check if userWord contain a number
bool checkNumber(string userWord)
{
    for(int i=0; i<userWord.length(); i++)
    {
        //loop that go through userWord
        if(isdigit(userWord.at(i)))
        {
            //Check if a specific a char in userWord is a digit
            return true;
        }

    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
//Function that check if the stack is empty
template <class Type>
bool myStack<Type>::isEmptyStack() const
{
    return(stackTop == 0);
}//end isEmptyStack
////////////////////////////////////////////////////////////////////////////////////////////
//Function that chek if the stack is full
template <class Type>
bool myStack<Type>::isFullStack() const
{
    return(stackTop == maxStackSize);
} //end isFullStack
////////////////////////////////////////////////////////////////////////////////////////////
//Function that add new element to the stack
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
////////////////////////////////////////////////////////////////////////////////////////////
//Function that return top element in the stack
template <class Type>
Type myStack<Type>::top() const
{
    assert(stackTop != 0); //if stack is empty, terminate the
//program
    return list[stackTop - 1]; //return the element of the stack
//indicated by stackTop - 1
}//end top
////////////////////////////////////////////////////////////////////////////////////////////
//Function that remove top element from the stack
template <class Type>
void myStack<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--; //decrement stackTop
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop
////////////////////////////////////////////////////////////////////////////////////////////
//Function that double the current stack size
template <class Type>
void myStack<Type>::doubleStackSize()
{
    maxStackSize*=2;
//double the current stack size
    list2=new Type[maxStackSize];
//initialize a new array with the updated stack size
    for(int i=0; i<stackTop; i++)
    {
//copy every element from the list array into list 2 array
        list2[i]=list[i];
    }
    delete []list;
//deleting the array that list is pointing to
    list=list2;
//point list to the array where list 2 is pointing to
}
////////////////////////////////////////////////////////////////////////////////////////////
//Constructor
//Initialize different variable in the stack such as
//a new dynamic array and the initial maxStackSize
template <class Type>
myStack<Type>::myStack(int stackSize)
{
    maxStackSize = stackSize; //set the stack size to
//the value specified by
//the parameter stackSize
    stackTop = 0; //set stackTop to 0
    list = new Type[maxStackSize]; //create the array to
//hold the stack elements
}//end constructor
////////////////////////////////////////////////////////////////////////////////////////////
//Destructor
//Remove all the elements from the stack.
template <class Type>
myStack<Type>::~myStack() //destructor
{
    delete [] list; //deallocate the memory occupied
//by the array
}//end destructor
