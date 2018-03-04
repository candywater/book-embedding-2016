#include <set>
#include <iostream>
#include <list>
#include <deque>


using namespace std;

void print(const list<int>& a){
  for(auto i : a)
    cout << i << " ";
  cout << endl;
}
void p(const deque<int>::iterator& i){
  cout << *i << endl;
}

int main(){

  
  list<int> a = {1, 2, 3, 4};
  deque<int> b = {1, 2, 3, 4};
  p(b.begin());
  printf("\r\r");
  p(b.begin());
  p(b.begin());
  p(b.begin());

  return 0;
}
