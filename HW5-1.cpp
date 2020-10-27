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


class Item
{
private:
    string name; //道具的名稱（不同的道具其名稱必不同）
    int type; // 1:所有角色都可以使用  2:戰士才能用  3:巫師才用
public:
    Item(string name, int type);
    ~Item();
    void setItem(string name, int type);
    string getItemName();
    int getItemType();
};

Item::Item(string name, int type):name(name), type(type) {}

Item::~Item() {}

void Item::setItem(string name, int type)
{
    this->name = name;
    this->type = type;
}

string Item::getItemName()
{
    return name;
}

int Item::getItemType()
{
    return type;
}




class ItemBag
{
private:
    static const int DEFAULT_CAPACITY = 10; //Bag的容量上限為10
    Item** items;
    int itemCnt;
    int maxItemCnt;
    int getIndexOf(const string& target) const; //回傳target在Bag中的index
public:
    ItemBag(int capacity);
    ~ItemBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool contains(const string& target) const;
    void addItem(const string& target, const int& type) throw(overflow_error);//超過容量時丟出例外
    bool hasItem(const string& target) const;
    void getItemList();
    void getItemSummary(); //列出包包內道具的個數
    void removeItem(const string& target) throw(invalid_argument); //如果包包內沒有這個item，丟出exception
    int getType(const string& target); //檢查是否可以使用這個item時用
};

ItemBag::ItemBag(int capacity)
{
    itemCnt = 0;
    maxItemCnt = capacity;
    items = new Item*[DEFAULT_CAPACITY];
}

ItemBag::~ItemBag()
{
    for(int i = 0; i < itemCnt; i++)
        delete this->items[i];
    delete [] this->items;
}

int ItemBag::getIndexOf(const string& target) const //回傳找到的第一個index
{
    bool found = false;
    int curIndex = 0;
    int result = -1;
    while(found == false && curIndex < itemCnt)
    {
        if(items[curIndex]->getItemName() == target)
        {
            found = true;
            result = curIndex;
        }
        else
            curIndex++;
    }
    return result;
}

int ItemBag::getCurrentSize() const
{
    return itemCnt;
}

bool ItemBag::isEmpty() const
{
    if(itemCnt == 0)
        return true;
    else
        return false;
}

bool ItemBag::contains(const string& target) const
{
    if(getIndexOf(target) == -1)
      return false;
    else
      return true;
}

void ItemBag::addItem(const string& target, const int& type) throw(overflow_error)
{
    if(this->itemCnt < this->maxItemCnt)
    {
        this->items[itemCnt] = new Item(target, type);
        this->itemCnt++;
    }
    else
        throw overflow_error("no more capacity");
}

bool ItemBag::hasItem(const string& target) const
{
    if(contains(target) == true)
        return true;
    else
        return false;
}

void ItemBag::getItemList()
{
    if(isEmpty() == true)
        cout << "empty" << endl;
    else
    {
        string* itemArray;
        itemArray = new string[itemCnt];
        for(int i = 0; i < itemCnt; i++)
        {
          itemArray[i] = this->items[i]->getItemName(); //將items寫入一個新的array
        }
        
        selectionSort(itemArray, itemCnt); //將array按照字典順序排列
        
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

void ItemBag::getItemSummary()
{
    if(isEmpty() == true)
        cout << "empty" << endl;
    else
    {
        string* itemArray;
        itemArray = new string[itemCnt];
        for(int i = 0; i < itemCnt; i++)
        {
          itemArray[i] = this->items[i]->getItemName(); //將items寫入一個新的array
        }
        
        selectionSort(itemArray, itemCnt); //將array按照字典順序排列

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

void ItemBag::removeItem(const string& target) throw(invalid_argument)//如果包包內沒有這個item，丟出exception
{
    int locatedIndex = getIndexOf(target);
    bool canRemoveItem = (locatedIndex > -1);
    if(canRemoveItem)
    {
        itemCnt--;
        items[locatedIndex]->setItem(items[itemCnt]->getItemName(), items[itemCnt]->getItemType());
        //減少一個item數量，再把要移除的item改成最後一個item
    }
    else
      throw invalid_argument("does the character own it?");
}

int ItemBag::getType(const string& target)
{
  int itemIndex = 0;
  int type = 0;
  if(hasItem(target) == true)
  {
    itemIndex = getIndexOf(target);
    type = items[itemIndex]->getItemType();
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
  void getItemList();
  void getItemSummary();
  void removeItem(const string& target);
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
    Bag.removeItem(target);
}

void Character::getItemList()
{
  Bag.getItemList();
}

void Character::getItemSummary()
{
  Bag.getItemSummary();
}

void Character::removeItem(const string& target)
{
  Bag.removeItem(target);
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
      Bag.removeItem(target);
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
      Bag.removeItem(target);
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
  void hasItem(const string& name, const string& target);
  void useItem(const string& name, const string& target);
  void getItemList(const string& name);
  void getItemSummary(const string& name);
  void removeItem(const string& name, const string& target);
  
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

void Team::hasItem(const string& name, const string& target)
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

void Team::getItemList(const string& name)
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

void Team::getItemSummary(const string& name)
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

void Team::removeItem(const string& name, const string& target)
{
  if(NameExist(name) == true)
  {
    for(int i = 0; i < memberCount; i++)
    {
      if(member[i]->getName() == name)
      {
        member[i]->removeItem(target);
      }
    }
  }
  else
    cout << "no such a character" << endl;
}


// ===========================================================================
// End of Character, Warrior, Wizard, and Team 
// ===========================================================================

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