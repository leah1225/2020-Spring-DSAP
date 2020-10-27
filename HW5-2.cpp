#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>
using namespace std;

void selectionSort(string array[], int size) //將字串陣列以字典順序重新排列
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

class Node
{
private:
    string itemName;
    int itemType;
    Node* next;
public:
    Node();
    Node(const string& name, const int& type);
    Node(const string& name, const int& type, Node* nextNodePtr);
    ~Node();
    void setItem(const string& name, const int& type);
    void setNext(Node* nextNodePtr);
    int getItemType() const;
    string getItemName() const;
    Node* getNext() const;
};

Node::Node():itemName(""), itemType(0), next(nullptr){}

Node::Node(const string& name, const int& type):itemName(name), itemType(type), next(nullptr){}

Node::Node(const string& name, const int& type, Node* nextNodePtr)
{
    itemName = name;
    itemType = type;
    next = nextNodePtr;
}

Node::~Node(){}

void Node::setItem(const string& name, const int& type)
{
    itemName = name;
    itemType = type;
}

void Node::setNext(Node* nextNodePtr)
{
    next = nextNodePtr;
}

int Node::getItemType() const
{
    return itemType;
}

string Node::getItemName() const
{
    return itemName;
}

Node* Node::getNext() const
{
    return next;
}




class ItemBag
{
private:
    Node* headPtr;
    int itemCnt;
    int maxItemCnt;
    Node* getPointerTo(const string& target) const;
public:
    ItemBag(const int& capacity);
    virtual ~ItemBag();
    int getCurrentSize() const;
    bool isEmpty()const;
    bool hasItem(const string& target) const;
    void addItem(const string& name, const int& type) throw(overflow_error);
    void getItemList() const;
    void getItemSummary() const;
    void remove(const string& target) throw(invalid_argument);
    int getType(const string& target) const;
};

ItemBag::ItemBag(const int& capacity):headPtr(nullptr), itemCnt(0), maxItemCnt(capacity){}

ItemBag::~ItemBag()
{
}

Node* ItemBag::getPointerTo(const string& target) const
{
    bool found = false;
    Node* curPtr = headPtr;
    
    while (!found && (curPtr != nullptr))
    {
        if (target == curPtr->getItemName())
            found = true;
        else
            curPtr = curPtr->getNext();
    } 
    
    return curPtr;
}

int ItemBag::getCurrentSize() const
{
    return itemCnt;
}

bool ItemBag::isEmpty() const
{
    return itemCnt == 0;
}

bool ItemBag::hasItem(const string& target) const
{
    return (getPointerTo(target) != nullptr);
}

void ItemBag::addItem(const string& name, const int& type) throw(overflow_error)
{
    if (itemCnt < maxItemCnt)
    {
        Node* newNodePtr = new Node();
        newNodePtr->setItem(name, type);
        newNodePtr->setNext(headPtr);  // New node指向nullptr

        headPtr = newNodePtr;          // 讓headPtr指向New node
        itemCnt++;
    }
    else
        throw overflow_error("no more capacity");
}

void ItemBag::getItemList() const
{
    if(isEmpty() == true)
        cout << "empty" << endl;
    else
    {
        string* itemArray;
        itemArray = new string[itemCnt];
        Node* curPtr = headPtr;

        for(int i = 0; i < itemCnt; i++) //將items寫入一個新的array
        {
            itemArray[i] = curPtr->getItemName();
            curPtr = curPtr->getNext();
        }

        selectionSort(itemArray, itemCnt);
        
        for(int i = 0; i < itemCnt; i++)
        {
            if(i == itemCnt - 1)
                cout << itemArray[i] << endl;
            else
                cout << itemArray[i] << ",";
        }
        delete [] itemArray;
    }
}

void ItemBag::getItemSummary() const
{
    if(isEmpty() == true)
        cout << "empty" << endl;
    else
    {
        string* itemArray;
        itemArray = new string[itemCnt];
        Node* curPtr = headPtr;

        for(int i = 0; i < itemCnt; i++) //將items寫入一個新的array
        {
            itemArray[i] = curPtr->getItemName();
            curPtr = curPtr->getNext();
        }

        selectionSort(itemArray, itemCnt);

        int cnt = 0; 
        for(int i = 0; i < itemCnt; i++)
        {
            if(i != itemCnt-1)
            {
                if(itemArray[i] == itemArray[i+1])
                    cnt++;
                else if(itemArray[i] != itemArray[i+1])
                {
                    cnt++;
                    cout << itemArray[i] << "," << cnt << ";";
                    cnt = 0; //歸零重新計算
                } 
            }
            else //如果是最後一個
            {
                cnt++;
                cout << itemArray[i] << "," << cnt << endl;
            }        
        }
        delete [] itemArray;
    }
}

void ItemBag::remove(const string& target) throw(invalid_argument)
{
    Node* targetNodePtr = getPointerTo(target);
    bool canRemoveItem = !isEmpty() && (targetNodePtr != nullptr);
    if (canRemoveItem)
    {
        //將要移除的node的name跟type改成第一個node的name跟type
        targetNodePtr->setItem(headPtr->getItemName(), headPtr->getItemType());
        
        //把第一個node刪掉
        Node* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        
        itemCnt--;
    } 
    else
        throw invalid_argument("does the character own it?");
}

int ItemBag::getType(const string& target) const
{
    Node* targetNodePtr;
    int type = 0;
    if(hasItem(target) == true)
    {
        targetNodePtr = getPointerTo(target);
        type = targetNodePtr->getItemType();
    }
    return type;
}

class Character
{
private:
  string name;
  int level;
public:
  ItemBag Bag;
  Character(string name, int lv, int capacity);
  ~Character();
  string getName();
  void addItem(const string& target, const int& type);
  bool hasItem(const string& target) const;
  virtual void useItem(const string& target);
  void getItemList() const;
  void getItemSummary() const;
  void remove(const string& target);
};

Character::Character(string name, int lv, int capacity) : name(name), level(lv), Bag(capacity) {}

Character::~Character() {}

string Character::getName()
{
  return name;
}

void Character::addItem(const string& target, const int& type)
{
  Bag.addItem(target, type);
}

bool Character::hasItem(const string& target) const
{
  if(Bag.hasItem(target) == true)
    return true;
  else
    return false;
}

void Character::useItem(const string& target)
{
  if(Bag.hasItem(target) == false) //沒有這個道具
    cout << "does the character own it?" << endl;
  else
    Bag.remove(target);
}

void Character::getItemList() const
{
  Bag.getItemList();
}

void Character::getItemSummary() const
{
  Bag.getItemSummary();
}

void Character::remove(const string& target)
{
  Bag.remove(target);
}


class Warrior : public Character
{
private:
public:
  Warrior(string name, int lv, int capacity);
  ~Warrior();
  void useItem(const string& target);
};

Warrior::Warrior(string name, int lv, int capacity) : Character(name, lv, capacity) {}

Warrior::~Warrior() {}

void Warrior::useItem(const string& target)
{
  if(Bag.hasItem(target) == false) //沒有這個道具
    cout << "does the character own it?" << endl;
  else
  {
    //戰士不能使用type = 3的道具
    if (Bag.getType(target) == 3)
      cout << "cannot use it" << endl;
    else
      Bag.remove(target);
  }
}



class Wizard : public Character
{
private:
public:
  Wizard(string name, int lv, int capacity);
  ~Wizard();
  void useItem(const string& target);
};

Wizard::Wizard(string name, int lv, int capacity) : Character(name, lv, capacity) {}

Wizard::~Wizard() {}

void Wizard::useItem(const string& target)
{
  if(Bag.hasItem(target) == false) //沒有這個道具
    cout << "does the character own it?" << endl;
  else
  {
    //巫師不能使用type = 2的道具
    if (Bag.getType(target) == 2)
      cout << "cannot use it" << endl;
    else
      Bag.remove(target);
  }
}




class Team
{
private:
  int memberCount;
  Character* member[10];
public:
  Team();
  ~Team();
  void addWarrior(string name, int lv, int capacity);
  void addWizard(string name, int lv, int capacity);
  bool NameExist(const string& name) const;
  void addItem(const string& name, const string& target, const int& type);
  void hasItem(const string& name, const string& target) const;
  void useItem(const string& name, const string& target);
  void getItemList(const string& name) const;
  void getItemSummary(const string& name) const;
  void remove(const string& name, const string& target);
};

Team::Team()
{
  this->memberCount = 0;
  for(int i = 0; i < 10; i++)
    member[i] = nullptr;
}

Team::~Team()
{
  for(int i = 0; i < this->memberCount; i++)
    delete this->member[i];
}

void Team::addWarrior(string name, int lv, int capacity) 
{
  if(memberCount < 10)
  {
    member[memberCount] = new Warrior(name, lv, capacity);
    memberCount++;
  }
}

void Team::addWizard(string name, int lv, int capacity)
{
  if(memberCount < 10)
  {
    member[memberCount] = new Wizard(name, lv, capacity);
    memberCount++;
  }
}

bool Team::NameExist(const string& name) const
{
  bool found = false;
  for (int i = 0; i < memberCount; i++)
  {
    if(member[i]->getName() == name)
    {
      found = true;
      break;
    }
  }
  return found;
}

void Team::addItem(const string& name, const string& target, const int& type)
{
  if(NameExist(name) == true) //存在這個角色
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->addItem(target, type);
      }
    }
  }
  else
    cout << "no such a character" << endl;
}

void Team::hasItem(const string& name, const string& target) const
{
  if(NameExist(name) == true)
  {
    for (int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        if(member[i]->hasItem(target) == true)
          cout << "yes" << endl;
        else
          cout << "no" << endl;
      }
    }
  }
  else
    cout << "no such a character" << endl;
}

void Team::useItem(const string& name, const string& target)
{
  if(NameExist(name) == true)
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->useItem(target);
      }
    }
  }
  else
  {
    cout << "no such a character" << endl;
  }
}

void Team::getItemList(const string& name) const
{
  if(NameExist(name) == true)
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->getItemList();
      }
    }
  }
  else
    cout << "no such a character" << endl;
}

void Team::getItemSummary(const string& name) const
{
  if(NameExist(name) == true)
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->getItemSummary();
      }
    }
  }
  else
    cout << "no such a character" << endl;
}

void Team::remove(const string& name, const string& target)
{
  if(NameExist(name) == true)
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->remove(target);
      }
    }
  }
  else
    cout << "no such a character" << endl;
}

int main()
{
    char instruction;
  string name;
  int level = 0;
  int bagCapacity = 0;
  
  string item;
  int itemType = 0;

  Team T;

  while (cin >> instruction)
  {
    if (instruction == 'R') 
    {
      cin >> name >> level >> bagCapacity;
      if (T.NameExist(name) == false) //沒有新增過這個角色
      {
        T.addWarrior(name, level, bagCapacity);
      }
      else
        cout << "the character exists" << endl;
    }

    if(instruction == 'D')
    {
      cin >> name >> level >> bagCapacity;
      if (T.NameExist(name) == false) //沒有新增過這個角色
      {
        T.addWizard(name, level, bagCapacity);
      }
      else
        cout << "the character exists" << endl;
    }

    if(instruction == 'A') //新增道具
    {
      cin >> name >> item >> itemType;
      try
      {
        T.addItem(name, item, itemType);
      }
      catch(overflow_error e)
      {
        cout << e.what() << endl;
      }
    }

    if(instruction == 'H')
    {
      cin >> name >> item;
      T.hasItem(name, item);
    }

    if(instruction == 'U')
    {
      cin >> name >> item;
      try
      {
        T.useItem(name, item);
      }
      catch(invalid_argument e)
      {
        cout << e.what() << '\n';
      }
    }

    if(instruction == 'L')
    {
      cin >> name;
      T.getItemList(name);
    }

    if(instruction == 'S')
    {
      cin >> name;
      T.getItemSummary(name);
    }

    if(instruction == 'V')
    {
      cin >> name >> item;
      try
      {
        T.remove(name, item);
      }
      catch(invalid_argument e)
      {
        cout << e.what() << '\n';
      }
    }
  }

  return 0;
}