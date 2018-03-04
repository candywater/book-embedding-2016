#include "h_head.h"
#include <limits.h>
#include <deque>
#include <assert.h>


void backtrack();

namespace{
  BIT bit_tree;
  vector<int> pos_temp;
  vector<int> v_temp;
  long long int times_count = 0;

  void backTrack(int, long long int, const deque<int>&);
  void openAndCloseEdgse(const deque<int>::const_iterator&);
  long long int countCrossingNum(const deque<int>::const_iterator&);
}

void backtrack(){
  deque<int> vertices;
  for(int i = 1; i < n; ++i)
    vertices.push_back(n - i);
  pos_temp.resize(n, 0);
  v_temp.resize(n, INT_MAX);
  
  for(long long int i = 0; i < m; ++i)
    all_edges[i].setIfOpen(false); 

  bit_tree = BIT(n);
  //円形のため、最初のポジション0にラベル０の点を固定で入れる。
  pos_temp[0] = 0;
  v_temp[0] = 0;
  for(int ix = 0; ix < static_cast<int>(edges[0].size()); ++ix){
    Edge& tmp = all_edges[ index_of_edges[0][ix] ];
    tmp.reverseOpen();
    if( tmp.isOpen() )
      bit_tree.add(v_temp[tmp.x], 1);
    else
      bit_tree.add(v_temp[tmp.x], -1);
  }
  //debug
  //bit_tree.printTree();
  //printf("\r%lld", times_count);
  backTrack(1, 0, vertices);
  printf("times_count:%lld best_sol:%lld", times_count, best_crossing_num);
  cout << endl;
}

namespace{

//debug
void printQueue(const deque<int>& ttt){
  cout << "deque: ";
  auto i = ttt.begin();
  while(i != ttt.end())
    cout << *i++ << " " ;
  cout << endl;
}
//debug
void printPosTemp(){
  cout << "pos temp:";
  for(auto i = pos_temp.begin(); i != pos_temp.end(); ++i)
    cout << *i << " ";
  cout << endl;
}

void openAndCloseEdges(const deque<int>::const_iterator& iv){
  for(int ix = 0; ix < static_cast<int>(edges[*iv].size()); ++ix){
    Edge& tmp = all_edges[ index_of_edges[*iv][ix] ];
    int px = v_temp[*iv];
    int py = v_temp[ edges[*iv][ix] ];
    int pt = px < py ? px : py;
    tmp.reverseOpen();
    if( tmp.isOpen() )
      bit_tree.add(pt, 1);
    else
      bit_tree.add(pt, -1);
  }
}

long long int countCrossingNum(const deque<int>::const_iterator& iv){

  long long int c = 0;
  for(int ix = 0; ix < static_cast<int>(edges[*iv].size()); ++ix){
    Edge& tmp = all_edges[ index_of_edges[*iv][ix] ];
    if( tmp.isOpen() )
      continue;
    int px = v_temp[*iv];
    int py = v_temp[ edges[*iv][ix] ];
    if( px < py - 1 )
      c += bit_tree.sum(px + 1, py - 1);
    else if( py < px -1 )
      c += bit_tree.sum(py + 1, px - 1);
  }
  return c;
}

void backTrack(int i, long long int count_now, const deque<int>& vertices){
  //assertionは良くない
  assert(count_now >= 0);
  //counter
  ++times_count;
  //printf("\r%lld %lld", ++times_count, best_crossing_num);
  if(i == n){
    if( best_crossing_num > count_now){
      best_crossing_num = count_now;
      pos = pos_temp;
      v = v_temp;
    }
    return;
  }
  if(best_crossing_num == 0) return;
  if( count_now >= best_crossing_num ) return;

  //label
  for(auto iv = vertices.begin(); iv != vertices.end(); ++iv){

    pos_temp[i] = *iv;
    v_temp[*iv] = i;

    //open edges and close edges
    //label
    openAndCloseEdges(iv);

    //count crossing num
    long long int c = 0;
    c += countCrossingNum(iv);

    deque<int> tmpv(vertices.begin(), iv);
    tmpv.insert(tmpv.end(), iv + 1, vertices.end());
    backTrack( i + 1, count_now + c, tmpv);

    //after backtrack, return them to their original states
    openAndCloseEdges(iv);
    v_temp[*iv] = INT_MAX;
  }
}
}
