#ifndef _CLASS_HEAD_H_
#define _CLASS_HEAD_H_

#define mySwap(type,a,b){type t = a; a = b; b = t;}


class Edge{
  private:
    bool open;
  public:
    int x,y;
    int page = 0;
    Edge(int, int);
    Edge(int, int, int page);
    bool isOpen() const;
    void setIfOpen(bool);
    void reverseOpen();
};

//binary indexed tree
//indexes of BIT start from 1
class BIT{
  private:
    vector<long long int> tree;
  public:
    BIT();
    BIT(int);
    ~BIT();
    //return sum of range[1, i+1]
    long long int sum (const int&)const;
    //return sum of range[i+1, j+1]
    long long int sum (const int&, const int&)const;
    //return value i+1
    long long int value(const int&) ;
    //update(add) value x at position i+1
    void add(const int&, const long long int&);
    void add(const int&, const long int&);
    void add(const int&, const int&);
    void add(const int&, const unsigned int&);
    void add(const int&, const unsigned long int&);
    void printTree() ;
};

#endif
