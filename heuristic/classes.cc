#include "h_head.h"

Edge::Edge(int x, int y){
  if(x > y) mySwap(int, x, y);
  this->x = x;
  this->y = y;
  open = false;
}
Edge::Edge(int x, int y,int page){
  if(x > y) mySwap(int, x, y);
  this->x = x;
  this->y = y;
  this->page = page;
  open = false;
}
bool Edge::isOpen() const{
  return this->open;
}
void Edge::setIfOpen(bool open){
  this->open = open;
}
void Edge::reverseOpen(){
  open = !open;
}

//constructor
BIT::BIT(){
}
//destructor
BIT::~BIT(){
  tree.clear();
}
// 1 index
BIT::BIT(int length){
  tree.clear();
	//tree.resize(numOfNodes(length+1), 0);
	tree.resize(length + 1, 0);
}

//[1, i+1]の範囲内での合計値
long long int BIT::sum(const int& j)const{
  int i = j;
	if(i <= -1) return 0;
	i++;
	long long int s = 0;
	while(i > 0){
    if(static_cast<unsigned long int>(i) < tree.size())
      s += tree[i];
		i -= (i & -i);
	}
	return s;
}
//[i+1, j+1]の範囲内での合計値
long long int BIT::sum(const int& i, const int& j)const {
	//if(i > j) mySwap(int, i, j);
  if(i < j)
    return sum(j) - sum(i-1);
  else
    return sum(i) - sum(j-1);
}

long long int BIT::value(const int& i){
	return sum(i, i);
}
//add x at i+1
void BIT::add(const int& j, const long long int& x){
	int i = j + 1;
	while(static_cast<unsigned long int>(i) < tree.size() ){
    tree[i] += x;
    i += (i & -i);
  }
}

//add x at i+1
void BIT::add(const int& j, const long int& y){
  int i = j + 1;
  long long int x = static_cast<long long int>(y);
  while(static_cast<unsigned long int>(i) < tree.size() ){
    tree[i] += x;
    i += (i & -i);
  }
}

//add x at i+1
void BIT::add(const int& j, const int& y){
  int i = j + 1;
  long long int x = static_cast<long long int>(y);
  while(static_cast<unsigned long int>(i) < tree.size() ){
    tree[i] += x;
    i += (i & -i);
  }
}

//add x at i+1
void BIT::add(const int& j, const unsigned int& y){
  int i = j + 1;
  long long int x = static_cast<long long int>(y);
  while(static_cast<unsigned long int>(i) < tree.size() ){
    tree[i] += x;
    i += (i & -i);
  }
}

//add x at i+1
void BIT::add(const int& j, const unsigned long int& y){
  int i = j + 1;
  long long int x = static_cast<long long int>(y);
  while(static_cast<unsigned long int>(i) < tree.size() ){
    tree[i] += x;
    i += (i & -i);
  }
}

void BIT::printTree() {
  printf("|node|");
  int i = 1;
  while(static_cast<unsigned long int>(i) != tree.size())
    printf("%4d|", (i++)-1);
  cout << endl;
  cout << "|leaf|";
  i = 1;
  while(static_cast<unsigned long int>(i) != tree.size())
    printf("%4lld|", value((i++) - 1));
  cout << endl;
  cout << "|real|";
  i = 1;
  while(static_cast<unsigned long int>(i) != tree.size())
    printf("%4lld|", tree[i++]);
  cout << endl;
  cout << endl;
}


