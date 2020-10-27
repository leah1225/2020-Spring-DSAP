#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class ArrayMinHeap
{
private:
    static const int ROOT_INDEX = 0;
    static const int DEFAULT_CAPACITY = 30000;
    int* items;
    int itemCount;
    int maxItems;

    int getLeftChildIndex(const int nodeIndex) const;
    int getRightChildIndex(int nodeIndex) const;
    int getParentIndex(int nodeIndex) const;

    bool isLeaf(int nodeIndex) const;
    void heapRebuild(int subTreeRootIndex);

protected:
    int leafCount(int currentIndex);
    void preorder(int currentIndex, vector <int>& r);
    void inorder(int currentIndex, vector <int>& r);
    void postorder(int currentIndex, vector <int>& r);

public:
    ArrayMinHeap();
    virtual ~ArrayMinHeap();

    bool isEmpty() const;
    int getNumberOfNodes() const;
    int getHeight() const;
    int getLeafNumber();
    int peekTop();
    void add(const int& newData);
    void remove();
    

    void preorderTraverse();
    void inorderTraverse();
    void postorderTraverse();
};

int ArrayMinHeap::getLeftChildIndex(const int nodeIndex) const
{
    return (nodeIndex*2 + 1);
}

int ArrayMinHeap::getRightChildIndex(const int nodeIndex) const
{
    return (nodeIndex*2 + 2);
}

int ArrayMinHeap::getParentIndex(int nodeIndex) const
{
    return (nodeIndex-1)/2;
}

ArrayMinHeap::ArrayMinHeap()
{
    items = new int[DEFAULT_CAPACITY];
    itemCount = 0;
    maxItems = DEFAULT_CAPACITY;

    for(int i = 0; i < 30000; i++)
    {
        items[i] = 30000; //都先預設為1000
    }
}
ArrayMinHeap::~ArrayMinHeap(){}

bool ArrayMinHeap::isLeaf(int nodeIndex) const
{
    int LeftChildIndex = nodeIndex*2+1;
    int RightChildIndex = nodeIndex*2+2;
    
    if(items[LeftChildIndex] == 30000 && items[RightChildIndex] == 30000)
        return true;
    else
        return false;
}

void ArrayMinHeap::heapRebuild(int subTreeRootIndex)
{
    if(!isLeaf(subTreeRootIndex))
    {
        int smallerChildIndex = 2*subTreeRootIndex + 1;

        if(items[2*subTreeRootIndex + 2] != 30000) //如果有右邊的孩子
        {
            int rightChildIndex = smallerChildIndex + 1;

            if(items[rightChildIndex] < items[smallerChildIndex])
                smallerChildIndex = rightChildIndex;
        }
        if(items[subTreeRootIndex] > items[smallerChildIndex])
        {
            swap(items[subTreeRootIndex], items[smallerChildIndex]);
            heapRebuild(smallerChildIndex);
        }
    }
}

int ArrayMinHeap::leafCount(int currentIndex)
{
    if(items[currentIndex] == 30000)
        return 0;
    if(items[getLeftChildIndex(currentIndex)] == 30000 && items[getRightChildIndex(currentIndex)] == 30000)
        return 1;
    else
        return leafCount(getLeftChildIndex(currentIndex))+leafCount(getRightChildIndex(currentIndex));
}

void ArrayMinHeap::preorder(int currentIndex, vector <int>& r)
{
    if(items[currentIndex] != 30000)
    {
        r.push_back(items[currentIndex]);
        preorder(getLeftChildIndex(currentIndex), r);
        preorder(getRightChildIndex(currentIndex), r);
    }
}

void ArrayMinHeap::inorder(int currentIndex, vector <int>& r)
{
    if(items[currentIndex] != 30000)
    {
        inorder(getLeftChildIndex(currentIndex), r);
        r.push_back(items[currentIndex]);
        inorder(getRightChildIndex(currentIndex), r);
    }
}

void ArrayMinHeap::postorder(int currentIndex, vector <int>& r)
{
    if(items[currentIndex] != 30000)
    {
        postorder(getLeftChildIndex(currentIndex), r);
        postorder(getRightChildIndex(currentIndex), r);
        r.push_back(items[currentIndex]);
    }
}

bool ArrayMinHeap::isEmpty() const
{
    if(itemCount == 0)
        return true;
    else
        return false;
}

int ArrayMinHeap::getNumberOfNodes() const
{
    return itemCount;
}

int ArrayMinHeap::getHeight() const
{
    return ceil(log2(itemCount+1));
}

int ArrayMinHeap::getLeafNumber()
{
    int counter = leafCount(ROOT_INDEX);
    return counter;
}

int ArrayMinHeap::peekTop()
{
    return items[0];
}

void ArrayMinHeap::add(const int& newData)
{
    items[itemCount] = newData;

    int newDataIndex = itemCount;
    bool inPlace = false;

    while(newDataIndex > 0 && !inPlace)
    {
        int parentIndex = (newDataIndex-1)/2;
        if(items[newDataIndex] >= items[parentIndex])
            inPlace = true;
        else
        {
            swap(items[newDataIndex], items[parentIndex]);
            newDataIndex = parentIndex;
        } 
    }
    itemCount++;
}

void ArrayMinHeap::remove()
{
    items[0] = items[itemCount-1];
    items[itemCount-1] = 30000;
    itemCount--;
    heapRebuild(0);
}

void ArrayMinHeap::preorderTraverse()
{
    vector <int> result;
    preorder(ROOT_INDEX, result);
    for(int i = 0; i < result.size(); i++)
    {
        if(i != result.size()-1)
            cout << result[i] << " ";
        else
            cout << result[i] << endl;
    }
}

void ArrayMinHeap::inorderTraverse()
{
    vector <int> result;
    inorder(ROOT_INDEX, result);
    for(int i = 0; i < result.size(); i++)
    {
        if(i != result.size()-1)
            cout << result[i] << " ";
        else
            cout << result[i] << endl;
    }
}

void ArrayMinHeap::postorderTraverse()
{
    vector <int> result;
    postorder(ROOT_INDEX, result);
    for(int i = 0; i < result.size(); i++)
    {
        if(i != result.size()-1)
            cout << result[i] << " ";
        else
            cout << result[i] << endl;
    }
}

int main()
{
    ArrayMinHeap Heap1;
    
    int number = 0;
    vector <int> nodeItems;
    
    while(cin >> number)
    {
        nodeItems.push_back(number);
    }
    
    for(int i = 0; i < nodeItems.size(); i++)
    {
        Heap1.add(nodeItems[i]);
    }
    
    cout << "Preorder: ";
    Heap1.preorderTraverse();
    cout << "Inorder: "; 
    Heap1.inorderTraverse();
    cout << "Postorder: ";
    Heap1.postorderTraverse();
    cout << "Number of nodes: " << Heap1.getNumberOfNodes() << endl;
    cout << "Number of leaf nodes: " << Heap1.getLeafNumber() << endl;
    cout << "Height: " << Heap1.getHeight() << endl;
    
    int removeNodeNum = Heap1.getNumberOfNodes()/2;
    
    for(int i = 0 ; i < removeNodeNum; i++)
    {
        Heap1.remove();
    }
    
    cout << "** after removing " << removeNodeNum << " nodes **" << endl;

    cout << "Preorder: ";
    Heap1.preorderTraverse();
    cout << "Inorder: "; 
    Heap1.inorderTraverse();
    cout << "Postorder: ";
    Heap1.postorderTraverse();
    cout << "Number of nodes: " << Heap1.getNumberOfNodes() << endl;
    cout << "Number of leaf nodes: " << Heap1.getLeafNumber() << endl;
    cout << "Height: " << Heap1.getHeight() << endl;
    
    
    return 0;
}