#include "h_head.h"
#include <time.h>
#include <limits.h>

//n = |V|
int n;
//m = |E|
long long int m;
//num of page
int k;
//vertices index from 0  
//v[i] = position of vertex, which label is i
vector<int> v;
//position index from 0 
//pos[i] = vertex label, which in positon i
vector<int> pos;
//edges list
//edges[label_i][出現する順番] = label in N(label_i)
vector< vector<int> > edges;
//all edges
vector< Edge > all_edges;
//index of edge of two vertices
//index_of_edges[label][出現する順番] = index of all_edges
vector< vector<long long int> > index_of_edges;
//best solution
long long int best_crossing_num = LLONG_MAX;


int main(int argc, char *argv[]){
  cout << "hello, world." << endl;
  init();
  readGraph();
  cout << "read, ok" << endl;
  long long int before_count = crossingCount();
  best_crossing_num = before_count;

  clock_t time = clock();
  backtrack();
  cout << "backtrack, ok" << endl;
  time = clock() - time;

  printGraph();
  cout << "print, ok" << endl;

  cout << "before_num:" << before_count << endl;
  cout << "best ans:  " << crossingCount() << endl;
  printf("time: %f [ms]\t (%f [s])\n",
      (double)(time/CLOCKS_PER_SEC*1000), 
      (double)(time/CLOCKS_PER_SEC));
  return 0;
}
