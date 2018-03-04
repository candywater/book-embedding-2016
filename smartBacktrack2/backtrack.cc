#include "h_head.h"
#include <limits.h>
#include <deque>
#include <set>
#include <assert.h>


void backtrack();

namespace{
class connect_comp{
  private:
  public:
    bool operator() (const int&, const int&) const;
};

set<int, connect_comp> connect_queue;


BIT bit_tree;
vector<int> pos_temp;
vector<int> v_temp;
long long int times_count = 0;
//num of inward connectivity(すでに配置された頂点)
vector<int> num_of_connect;

void backTrack(int, long long int, const set<int, connect_comp>&);
int backtrackInit(set<int, connect_comp>&);
void openAndCloseEdges(const set<int, connect_comp>::const_iterator&, set<int, connect_comp>&);
void returnOpenAndCloseEdges(const set<int, connect_comp>::const_iterator&);
long long int countCrossingNum(const set<int, connect_comp>::const_iterator&);
//debug
void p(const int&);
void printQueue(const set<int, connect_comp>&);
void printPosTemp();
}

bool connect_comp::operator() (const int& a, const int& b)const{
  if(edges[a].size() - num_of_connect[a] ==  
      edges[b].size() - num_of_connect[b]
      && num_of_connect[a] == num_of_connect[b])
    return a < b; 
  else if(num_of_connect[a] == num_of_connect[b])
    return edges[a].size() - num_of_connect[a] < 
      edges[b].size() - num_of_connect[b];
  else 
    return num_of_connect[a] > num_of_connect[b];
}

void backtrack(){
  set<int, connect_comp> connect_queue;
  bit_tree = BIT(n);
  //円形のため、最初のポジションにとりあえず一つの頂点を入れる
  int start_vertex = backtrackInit(connect_queue);

  for(int ix = 0; ix < static_cast<int>(edges[start_vertex].size()); ++ix){
    Edge& tmp = all_edges[ index_of_edges[start_vertex][ix] ];
    tmp.reverseOpen();
    if( tmp.isOpen() )
      bit_tree.add(v_temp[start_vertex], 1);
    else
      bit_tree.add(v_temp[start_vertex], -1);
    int ty = tmp.x == start_vertex ? tmp.y : tmp.x;
    connect_queue.erase(ty);
    num_of_connect[ty] += 1;
    connect_queue.insert(ty);
  }
  //debug
  printQueue(connect_queue);

  printf("backtrack time num:\r%lld", times_count);
  backTrack(1, 0, connect_queue);
  cout << endl;
}

namespace{
int backtrackInit(set<int, connect_comp>& connect_queue){
  pos_temp.resize(n, 0);
  v_temp.resize(n, INT_MAX);

  for(long long int i = 0; i < m; ++i)
    all_edges[i].setIfOpen(false); 

  for(int i = 0; i < n; i++)
    //num of N(v) that already inserted
    num_of_connect.push_back(0);
  for(int i = 0; i < n; i++)
    connect_queue.insert(i);

  int start_vertex = *connect_queue.begin();
  connect_queue.erase(connect_queue.begin());
  pos_temp[0] = start_vertex;
  v_temp[start_vertex] = 0;

  return start_vertex;
}

//debug
void printQueue(const set<int, connect_comp>& ttt){
  cout << "queue: ";
  auto i = ttt.begin();
  while(i != ttt.end())
    cout << *i++ << " " ;
  cout << endl;
}
void printCon(){
  auto i = num_of_connect.begin();
  while(i != num_of_connect.end())
    cout << *i++ << " ";
  cout << endl;
  for(int ix = 0; ix < n; ++ix)
    cout << edges[ix].size() << " ";
  cout <<endl;
}
//debug
void printPosTemp(){
  cout << "pos temp:";
  for(auto i = pos_temp.begin(); i != pos_temp.end(); ++i)
    cout << *i << " ";
  cout << endl;
}
//debug
void p(const int& i){
  cout << "check point " << i << endl;
}

void openAndCloseEdges(const set<int, connect_comp>::const_iterator& iv, set<int, connect_comp>& connect_queue){
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
    //update priority queue
    pt = tmp.x == *iv ? tmp.y : tmp.x;
    if(connect_queue.erase(pt)){
      num_of_connect[pt] += 1;
      connect_queue.insert(pt);
    }
    else
      num_of_connect[pt] += 1;
  }
}

void returnOpenAndCloseEdges(const set<int, connect_comp>::const_iterator& iv){
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
    //need not to update priority queue
    pt = tmp.x == *iv ? tmp.y : tmp.x;
    num_of_connect[pt] -= 1;
  }
}

long long int countCrossingNum(const set<int, connect_comp>::const_iterator& iv){

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

void backTrack(int i, long long int count_now, const set<int, connect_comp>& connect_queue){

  //assertionは良くない
  assert(count_now >= 0);
  //printf("\rbacktrack time num:%lld", ++times_count);
  ++times_count;
  if( count_now >= best_crossing_num ) return;
  if(i == n){
    if( best_crossing_num > count_now){
      best_crossing_num = count_now;
      pos = pos_temp;
      v = v_temp;
    }
    return;
  }
  if(best_crossing_num == 0) return;

  //label
  //順序に試していく
  for(auto iv = connect_queue.begin(); iv != connect_queue.end(); ++iv){
    pos_temp[i] = *iv;
    v_temp[*iv] = i;

    //open edges and close edges
    //label
    set<int, connect_comp> tmpq = connect_queue;
    tmpq.erase(*iv);
    openAndCloseEdges(iv, tmpq);

    //count crossing num
    long long int c = 0;
    c += countCrossingNum(iv);

    backTrack( i + 1, count_now + c, tmpq);

    //after backtrack, return them to their original states
    returnOpenAndCloseEdges(iv);
    v_temp[*iv] = INT_MAX;

  }
}
}
