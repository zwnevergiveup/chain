#include<iostream>
#include<memory>
#include<sstream>
#include<iterator>
#include <algorithm>
template<typename T>
class iterator;
template<typename T>
struct chainNode//该结构体为链表中储存的单个元素的结构;
{
    T Element;
    chainNode<T> *Next;
    chainNode(){}
    chainNode(const T &element){this->Element=element;
                                Next=NULL;}
    chainNode(const T &element,chainNode<T> *next){
        this->Element=element;
        this->Next=next;
    }
};
template<typename T>
class linerList
{
public:
    virtual ~linerList(){}
    virtual bool empty()const =0;
    virtual int    size()   const =0;
    virtual T&   get(int theIndex) const=0;
    virtual int indexOf(const T& theElement)const =0;
    virtual void erase(int theIndex)=0;
    virtual void insert(int theIndex,const T& theElement)=0;
    virtual void output(std::ostream &out)const =0;
};
template<typename T>
class chain:public linerList<T>
{
    friend class iterator<T>;
public:
    chain(int initialCapacity=10);
    chain(const chain<T>&);
    ~chain();
    bool empty() const{return ListSize==0;}
    int size() const{return ListSize;}
    T& get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex,const T& theElement);
    void output(std::ostream &out)const;
protected:
    void checkIndex(int theIndex)const;
    chainNode<T> *FirstNode;
    int ListSize;
};
template<typename T>
 chain<T>::chain(int initialCapacity)
 {
  if(initialCapacity<1)
  {
      std::cout<<"Initial capacity must > 1"<<std::endl;
     return;
  }
  FirstNode=NULL;
  ListSize=0;
 }
 template<typename T>
 chain<T>::chain(const chain<T> &theList){
     this->ListSize=theList.ListSize;
     if(ListSize=0)
     {
         this->FirstNode=NULL;
         return;
     }
     chainNode<T>* sourceNode=theList.FirstNode;
     FirstNode=new chainNode<T>(sourceNode->Element);
     sourceNode=sourceNode->Next;
     chainNode<T> *targetNode=FirstNode;
     while(sourceNode!=NULL)
     {
     targetNode->Next=new chainNode<T>(sourceNode->Element);
     targetNode=targetNode->Next;
     sourceNode=sourceNode->Next;
     }
     targetNode->Next=NULL;
 }
 template<typename T>
 chain<T>::~chain()
 {
     while(FirstNode!=NULL)
     {
         chainNode<T> *nextNode=FirstNode->Next;
         delete FirstNode;
         FirstNode=nextNode;
     }
 }
template<typename T>
T& chain<T>::get(int theIndex) const
{
     //checkIndex(theIndex);
     chainNode<T>* sourceNode=FirstNode;
   for(int i=0;i<theIndex;i++)
   {
    sourceNode=sourceNode->Next;
   }
    return sourceNode->Element;
}
template<typename T>
int chain<T>::indexOf(const T &theElement)const
{
    if(empty())
    {
        std::cout<<"empty!"<<std::endl;
    }
    else
    {     int index=0;
        chainNode<T> *sourceNode=FirstNode;
        while(sourceNode!=NULL&&sourceNode->Element!=theElement)
        {
            sourceNode=sourceNode->Next;
            ++index;
        }
        if(sourceNode==NULL)
            return -1;
        else
            return index;
    }
}
template<typename T>
void chain<T>::erase(int theIndex)
{
   // checkIndex(theIndex);
    chainNode<T> *ergodicNode=FirstNode;
    if(theIndex==0)
    {
        FirstNode=FirstNode->Next;
        delete ergodicNode;
    }
    else
    {
        for(int i=0;i<theIndex-1;i++)
            ergodicNode=ergodicNode->Next;

        chainNode<T> *LSGNode=ergodicNode->Next;
        ergodicNode->Next=ergodicNode->Next->Next;
        delete LSGNode;
        --ListSize;
    }
}
template<typename T>
void chain<T>::insert(int theIndex,const T  &theElement)
{
    if(theIndex<0||theIndex>ListSize)
    {
      std::cout<<"invalid Index";
                 return;
    }
    if(theIndex==0)
    FirstNode=new chainNode<T>(theElement,FirstNode);
    else
    {
        chainNode<T> *ergodicNode=FirstNode;
        for(int i=0;i<theIndex-1;i++)
            ergodicNode=ergodicNode->Next;
        ergodicNode->Next=new chainNode<T>(theElement,ergodicNode->Next);
    }
    ++ListSize;
}
template<typename T>
void chain<T>::output(std::ostream &out)const
{
    for(chainNode<T> *ergodicNode=FirstNode;
        ergodicNode!=NULL;
        ergodicNode=ergodicNode->Next)
        out<<ergodicNode->Element<<" ";
}
template<typename T>
std::ostream& operator<<(std::ostream &out,const chain<T> &x)
{
    x.output(out);
    return out;
}
template<typename T>
class iterator
{
public:
    iterator(chainNode<T> *theNode=NULL):Node(theNode){}
    T& operator* ()const{return Node->Element;}
    T* operator->()const{return &Node->Element;}
    iterator& operator++ ()
    {
        Node=Node->Next;
        return *this;
    }
    iterator operator++(int)
    {
        iterator old=*this;
        Node=Node->Next;
        return old;
    }
    bool operator !=(const iterator right)const
    {return Node!=right.Node;}
    bool operator ==(const iterator right)const
    {return Node==right.Node;}
protected:
    chainNode<T> *Node;
};
int main(){
    chain<int> *link=new chain<int>(20);
    for(int i=20;i>0;--i)
    link->insert(0,i);
    link->erase(3);
    link->insert(3,520);
    std::cout<<*link<<std::endl;
 return 0;
}


















