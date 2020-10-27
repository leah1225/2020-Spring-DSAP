#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

class TreeNode
{
private:
    int item;
    TreeNode* leftChildPtr;
    TreeNode* rightChildPtr;
public:
    TreeNode();
    TreeNode(const int& anItem);
    TreeNode(const int& anItem, TreeNode* leftPtr, TreeNode* rightPtr);

    void setItem(const int& anItem);
    int getItem() const;

    bool isLeaf() const;
    
    TreeNode* getLeftChildPtr() const;
    TreeNode* getRightChildPtr() const;
    
    void setLeftChildPtr(TreeNode* leftPtr);
    void setRightChildPtr(TreeNode* rightPtr);
};

TreeNode::TreeNode(){}
TreeNode::TreeNode(const int& anItem):item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr){}
TreeNode::TreeNode(const int& anItem, TreeNode* leftPtr, TreeNode* rightPtr):item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr){}

void TreeNode::setItem(const int& anItem)
{
    this->item = anItem;
}
int TreeNode::getItem() const
{
    return item;
}

bool TreeNode::isLeaf() const
{
    if(this->leftChildPtr == nullptr && this->rightChildPtr == nullptr)
        return true;
    else
        return false;
}

TreeNode* TreeNode::getLeftChildPtr() const
{
    return this->leftChildPtr;
}
TreeNode* TreeNode::getRightChildPtr() const
{
    return this->rightChildPtr;
}

void TreeNode::setLeftChildPtr(TreeNode* leftPtr)
{
    this->leftChildPtr = leftPtr;
}
void TreeNode::setRightChildPtr(TreeNode* rightPtr)
{
    this->rightChildPtr = rightPtr;
}



class BinarySearchTree
{
private:
    TreeNode* rootPtr;
    int nodeNums;
protected:
    int getHeightHelper(TreeNode* subTreePtr) const;
    TreeNode* insertInorder(TreeNode* subTreePtr, TreeNode* newNode);
    int leafCount(TreeNode* current);
    void preorder(TreeNode* current, vector <int>& r);
    void inorder(TreeNode* current, vector <int>& r);
    void postorder(TreeNode* current, vector <int>& r);
public:
    BinarySearchTree();
    BinarySearchTree(const int& rootItem);
    virtual ~BinarySearchTree();

    bool isEmpty() const;
    int getHeight() const;
    int getNodesNumber() const;
    int getLeafNumber();

    void setRootData(const int& newData);
    void add(const int& newData);

    void preorderTraverse();
    void inorderTraverse();
    void postorderTraverse();
};

int BinarySearchTree::getHeightHelper(TreeNode* subTreePtr) const
{
    if (subTreePtr == nullptr)
      return 0;
    else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

TreeNode* BinarySearchTree::insertInorder(TreeNode* subTreePtr, TreeNode* newNode)
{
    TreeNode* tempPtr = nullptr;

    if(subTreePtr == nullptr)
        return newNode;
    else if(subTreePtr->getItem() > newNode->getItem())
    {
        tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

int BinarySearchTree::leafCount(TreeNode* current)
{
    if(current == nullptr)
        return 0;
    if(current->getLeftChildPtr() == nullptr && current->getRightChildPtr() == nullptr)
        return 1;
    else
        return leafCount(current->getLeftChildPtr())+leafCount(current->getRightChildPtr());
}

void BinarySearchTree::preorder(TreeNode* current, vector <int>& r)
{
    if(current != nullptr)
    {
        r.push_back(current->getItem());
        preorder(current->getLeftChildPtr(), r);
        preorder(current->getRightChildPtr(), r);
    }
}

void BinarySearchTree::inorder(TreeNode* current, vector <int>& r)
{
    if(current != nullptr)
    {
        inorder(current->getLeftChildPtr(),r);
        r.push_back(current->getItem());
        inorder(current->getRightChildPtr(), r);
    }
}

void BinarySearchTree::postorder(TreeNode* current, vector <int>& r)
{
    if(current != nullptr)
    {
        postorder(current->getLeftChildPtr(), r);
        postorder(current->getRightChildPtr(), r);
        r.push_back(current->getItem());
    }
}

BinarySearchTree::BinarySearchTree():rootPtr(nullptr), nodeNums(0){}

BinarySearchTree::BinarySearchTree(const int& rootItem)
{
    rootPtr = new TreeNode(rootItem, nullptr, nullptr);
    nodeNums = 0;
}

BinarySearchTree::~BinarySearchTree(){}

bool BinarySearchTree::isEmpty() const
{
    if(rootPtr == nullptr)
        return true;
    else
        return false;
}

int BinarySearchTree::getHeight() const
{
    return getHeightHelper(rootPtr);
}

int BinarySearchTree::getNodesNumber() const
{
    return nodeNums;
}

int BinarySearchTree::getLeafNumber()
{
    int counter = leafCount(rootPtr);
    return counter;
}

void BinarySearchTree::setRootData(const int& newData)
{
    rootPtr->setItem(newData);
}

void BinarySearchTree::add(const int& newData)
{
    TreeNode* newNodePtr = new TreeNode(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    nodeNums++;
}

void BinarySearchTree::preorderTraverse()
{
    vector <int> result;
    preorder(rootPtr, result);
    for(int i = 0; i < result.size(); i++)
    {
        if(i != result.size()-1)
            cout << result[i] << " ";
        else
            cout << result[i] << endl;
    }
}

void BinarySearchTree::inorderTraverse()
{
    vector <int> result;
    inorder(rootPtr, result);
    for(int i = 0; i < result.size(); i++)
    {
        if(i != result.size()-1)
            cout << result[i] << " ";
        else
            cout << result[i] << endl;
    }
}

void BinarySearchTree::postorderTraverse()
{
    vector <int> result;
    postorder(rootPtr, result);
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
    BinarySearchTree BST1;
    BinarySearchTree BST2;
    
    int number = 0;
    vector <int> nodeItems;
    
    while(cin >> number)
    {
        nodeItems.push_back(number);
    }
    
    for(int i = 0; i < nodeItems.size(); i++)
    {
        BST1.add(nodeItems[i]);
    }
    
    cout << "Preorder: ";
    BST1.preorderTraverse();
    cout << "Inorder: "; 
    BST1.inorderTraverse();
    cout << "Postorder: ";
    BST1.postorderTraverse();
    cout << "Number of nodes: " << BST1.getNodesNumber() << endl;
    cout << "Number of leaf nodes: " << BST1.getLeafNumber() << endl;
    cout << "Height: " << BST1.getHeight() << endl;
    
    cout << "** after removing " << BST1.getNodesNumber()/2 << " nodes **" << endl;
    
    for(int i = nodeItems.size()/2 ; i < nodeItems.size(); i++)
    {
        BST2.add(nodeItems[i]);
    }
    
    cout << "Preorder: ";
    BST2.preorderTraverse();
    cout << "Inorder: "; 
    BST2.inorderTraverse();
    cout << "Postorder: ";
    BST2.postorderTraverse();
    cout << "Number of nodes: " << BST2.getNodesNumber() << endl;
    cout << "Number of leaf nodes: " << BST2.getLeafNumber() << endl;
    cout << "Height: " << BST2.getHeight() << endl;
    
    
    return 0;
}