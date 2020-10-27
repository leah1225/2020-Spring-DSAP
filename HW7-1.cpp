#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>
using namespace std;

const int MAX_STACK = 999;

template<class ItemType>
class ArrayStack
{
private:
  ItemType items[MAX_STACK]; 
  int top;
public:
  ArrayStack(); // Default constructor
  bool isEmpty() const;
  void push(const ItemType& newEntry);
  void pop();
  ItemType peek() const;
}; 

template<typename ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
} 

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
  return top < 0;
} 

template<typename ItemType>
void ArrayStack<ItemType>::push(const ItemType& newEntry)
{
  if(this->top < MAX_STACK - 1) // 判斷是否有空間塞入下一個物件
  {
    top++;
    this->items[top] = newEntry;
  } 
} 

template<typename ItemType>
void ArrayStack<ItemType>::pop()
{
  if(!this->isEmpty()) //直接將top-1,下一次push的時候直接複寫掉
  {
    top--;
  }
} 

template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
  if(!this->isEmpty()) // check precondition
    return items[top];
  else
    throw logic_error("...");
} 

int main()
{
    ArrayStack <char> strStack;
    ArrayStack <char> result;
    string sentence;

    while(getline(cin, sentence))
    {

        for(int i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] == '<' && !strStack.isEmpty())
                strStack.pop();
            else if(sentence[i] != '<')
                strStack.push(sentence[i]);
        }

        while (!strStack.isEmpty())
        {
            char newChar = strStack.peek();
            result.push(newChar);
            strStack.pop();
        }
        
        while (!result.isEmpty())
        {
            char newChar = result.peek();
            cout << newChar;
            result.pop();
        }
        cout << "\n";
    }
    return 0;
}