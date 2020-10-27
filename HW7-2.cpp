#include <iostream>
#include <cmath>
#include <string>
#include<stdexcept>
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
  if(this->top < MAX_STACK - 1)
  {
    top++;
    this->items[top] = newEntry;
  } 
} 
  
template<typename ItemType>
void ArrayStack<ItemType>::pop()
{
  if(!this->isEmpty())
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
  
  
/* 符號優先順序：次方 > 乘號 = 除號 > 加號 = 減號
必須嚴格大於前一個符號才能直接放到stack中*/
  
int main()
{
    ArrayStack <int> intStack;
    ArrayStack <char> operatorStack;
    string sentence;
  
    int num1 = 0, num2 = 0, result = 0; char temp;
  
    while(getline(cin, sentence))
    {
        for (int i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != '+' && sentence[i] != '-' && sentence[i] !='*' && sentence[i] != '/' && sentence[i] != '^' && sentence[i] != ' ') //如果是整數的話直接放進去
                intStack.push(sentence[i] - '0');
            else if (sentence[i] == '+' || sentence[i] == '-') //如果要加入的符號是加或減
            {
                if(operatorStack.isEmpty())
                    operatorStack.push(sentence[i]);
                else
                {
                    while(!operatorStack.isEmpty())
                    {
                        num1 = intStack.peek();
                        intStack.pop();
                        num2 = intStack.peek();
                        intStack.pop();
                        temp = operatorStack.peek();
                        operatorStack.pop();
  
                        if(temp == '+')
                            result = num2 + num1;
                        else if(temp == '-')
                            result = num2 - num1;
                        else if(temp == '*')
                            result = num2 * num1;
                        else if(temp == '/')
                            result = num2 / num1;
                        else if(temp == '^')
                            result = pow(num2, num1);
                          
                        intStack.push(result);
                    }
                    operatorStack.push(sentence[i]);
                }
            }
            else if (sentence[i] == '*' || sentence[i] == '/')
            {
                if(operatorStack.isEmpty())
                    operatorStack.push(sentence[i]);
                else if(operatorStack.peek() == '+' || operatorStack.peek() == '-')
                    operatorStack.push(sentence[i]);
                else
                {
                    while(operatorStack.peek() != '+' && operatorStack.peek() != '-')
                    {
                        num1 = intStack.peek();
                        intStack.pop();
                        num2 = intStack.peek();
                        intStack.pop();
                        temp = operatorStack.peek();
                        operatorStack.pop();
  
                        if(temp == '*')
                            result = num2*num1;
                        else if(temp == '/')
                            result = num2 / num1;
                        else if(temp == '^')
                            result = pow(num2, num1);
  
                        intStack.push(result);
                        
                        if(operatorStack.isEmpty() == true) //如果這次計算完沒有運算子了
                            break;
                    }
                    operatorStack.push(sentence[i]);
                }  
            }
            else if (sentence[i] == '^')
            {
                operatorStack.push(sentence[i]);
            }
        }
        while(!operatorStack.isEmpty())
        {
            num1 = intStack.peek();
            intStack.pop();
            num2 = intStack.peek();
            intStack.pop();
            temp = operatorStack.peek();
            operatorStack.pop();
  
            if(temp == '+')
                result = num2 + num1;
            else if(temp == '-')
                result = num2 - num1;
            else if(temp == '*')
                result = num2 * num1;
            else if(temp == '/')
                result = num2 / num1;
            else if(temp == '^')
                result = pow(num2, num1);
                          
            intStack.push(result);
        }
        result = intStack.peek();
        intStack.pop();
        cout << result << endl;
    }  
    return 0;
}
