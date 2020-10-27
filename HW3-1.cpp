#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;
 
void selectionSort(string array[], int size) //幫要印出來的商家進行字典順序排列
{
   int start; 
   string temp;
   for(int i = size -1; i > 0; --i)
   {
      start = 0;
      for(int j = 1; j <= i; ++j)
      {
        if(array[j] >array[start])
        {
            start = j;
        }
         temp = array[start];
        array[start] = array[i];
        array[i] = temp;
      }
   }
}
 
class Entity //customer和mall的雛形
{
protected:
    string account;
public:
    Entity(string id);
    ~Entity();
    string getAccount();
};
Entity::Entity(string id):account(id){}
Entity::~Entity(){}
string Entity::getAccount()
{
    return account;
}
 
class Customer:public Entity
{
private:
public:
    Customer(string id);
};
Customer::Customer(string id):Entity(id){}
 
class CustomerArray
{
private:
    int capacity;
    int cnt;
    Customer** customerPtr;
public:
    CustomerArray();
    ~CustomerArray();
    void add(string account);
};
 
CustomerArray::CustomerArray()
{
    this->cnt = 0;
    this->capacity = 200;
    this->customerPtr = new Customer*[this->capacity];
}
 
CustomerArray::~CustomerArray()
{
    for(int i = 0; i < this->cnt; i++)
        delete this->customerPtr[i];
    delete [] this->customerPtr;
}
 
void CustomerArray::add(string account)
{
    if(cnt < capacity)
    {
        customerPtr[cnt] = new Customer(account);
        cnt++;
    }
}
 
 
class Mall:public Entity
{
private:
public:
    Mall(string id);
};
Mall::Mall(string id):Entity(id){}
 
class MallArray
{
private:
    int capacity;
    int cnt;
    Mall** mallPtr;
public:
    MallArray();
    ~MallArray();
    void add(string account);
};
 
MallArray::MallArray()
{
    this->capacity = 200;
    this->cnt = 0;
    this->mallPtr = new Mall*[this->capacity];
}
 
MallArray::~MallArray()
{
    for(int i = 0; i < this->cnt; i++)
        delete this->mallPtr[i];
    delete [] this->mallPtr;
}
 
void MallArray::add(string account)
{
    if(cnt < capacity)
    {
        mallPtr[cnt] = new Mall(account);
        cnt++;
    }
}
 
 
class Transaction //紀錄所有交易資訊
{
private:
    string buyer[200];
    string seller[200];
    string product[200];
    int tradeCnt;
    int buyerScore[200];
    int sellerScore[200];
public:
    Transaction();
    ~Transaction();
    void purchase(string id1, string id2, string p, int s1, int s2);
    void search(string buyer, string product);
};
 
Transaction::Transaction():tradeCnt(0){} //將交易次數歸零
 
Transaction::~Transaction(){}
 
void Transaction::purchase(string id1, string id2, string p, int s1, int s2)
{
    buyer[tradeCnt] = id1;
    seller[tradeCnt] = id2;
    product[tradeCnt] = p;
    buyerScore[tradeCnt] = s1;
    sellerScore[tradeCnt] = s2;
    tradeCnt++; //每出現一次交易就將交易次數加一
}
 
void Transaction::search(string buyer, string product)
{   
    int maxScore = 0; //最高評價
    int maxCnt = 0; //最高評價出現的次數
    for(int i = 0; i < tradeCnt; i++) //找到某買家購買某商品的最高評價跟最高評價出現次數
    {
        if(this->buyer[i] == buyer && this->product[i] == product && this->buyerScore[i] > maxScore)
        {
            maxScore = buyerScore[i];
            maxCnt = 1;
        }
        else if(this->buyer[i] == buyer && this->product[i] == product && this->buyerScore[i] == maxScore)
        {
            maxCnt++;
        }
    }
 
    if (maxScore == 0) //根本沒有買過這個商品
        cout << "\n";
    else if(maxScore != 0 && maxCnt == 1) //只跟一個賣家買過
    {
        for(int i = 0; i < tradeCnt; i++)
        {
            if(this->buyer[i] == buyer && this->product[i] == product && this->buyerScore[i] == maxScore)
                cout << seller[i] << endl;
        }
    }
    else if(maxScore != 0 && maxCnt != 1) //跟不同賣家購買過
    {
        string* object = new string [maxCnt];
        int cnt = 0;
        for(int i = 0; i < tradeCnt; i++)
        {
            if(this->buyer[i] == buyer && this->product[i] == product && this->buyerScore[i] == maxScore)
            {
                object[cnt] = seller[i];
                cnt++;
            }
        }
        selectionSort(object, maxCnt);
        if(maxCnt > 5) //如過交易過的賣家多於五個，只印出前五家
        {
            for(int i = 0; i < 5; i++)
            {
                if(i != 4)
                    cout << object[i] << " ";
                else
                    cout << object[i] << endl;
            }
        }
        else
        {
            for(int i = 0; i < maxCnt; i++)
            {
                if(i != maxCnt-1)
                    cout << object[i] << " ";
                else
                    cout << object[i] << endl;
            }
        }
        delete [] object;
        object = nullptr;
    }    
}
 
int main()
{
    CustomerArray c;
    MallArray m;
    Transaction t;
 
    char instruction;
    string cust, mall, p;
    int s1 = 0, s2 = 0;
 
    while (cin >> instruction)
    {
        if(instruction == 'C')
        {
            cin >> cust;
            c.add(cust);
        }
        else if (instruction == 'M')
        {
            cin >> mall;
            m.add(mall);
        }
        else if(instruction == 'T')
        {
            cin >> cust >> mall >> p >> s1 >> s2;
            t.purchase(cust, mall, p, s1, s2);
        }
        else if(instruction == 'S')
        {
            cin >> cust >> p;
            t.search(cust, p);
        }
    }
    return 0;