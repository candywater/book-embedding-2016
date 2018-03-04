#include "h_head.h"
#include <queue>
#include <assert.h>

void init();
void readGraph();
void printGraph();
long long int crossingCount();
//debug
void printPos();
void debug();

void init(){
  n = 0;
  m = 0; 
  k = 1;
  v.clear();
  pos.clear();
  edges.clear();
  all_edges.clear();
  index_of_edges.clear();
}

void countOpenAndCloseEdges(const int& ix, const int& iy, queue<long long int>& stack, BIT& tree){
  long long int i = index_of_edges[ pos[ix] ][iy];
  Edge* tmp = &all_edges[i];
  int iu = v[tmp->x];
  int iv = v[tmp->y];
  int ip = iu < iv ? iu : iv;
  if( tmp->isOpen() ){
    //assert (ip != ix);
    tree.add(ip, -1);
    stack.push(i);
  }
  else{
    //assert (ip == ix);
    tree.add(ip, 1);
  }
  tmp->reverseOpen();
  //tree.printTree();
}

void countSingleEdge(long long int& count, const BIT& tree, const queue<long long int>& stack){
  Edge* tmp = &all_edges[ stack.front() ];
  if( tmp->isOpen() )
    return;
  int iu = v[tmp->x];
  int iv = v[tmp->y];
  //二つの点の間に一つ以上の点が存在する場合
  if(iv - iu > 1) 
    count += tree.sum(iu + 1, iv - 1);
  else if (iu - iv > 1)
    count += tree.sum(iv + 1, iu - 1);
}

long long int crossingCount(){
  long long int count = 0;
  BIT tree = BIT(n);

  //cout << "counting now.";
  //bug防止
  for(int i = 0; i < m; ++i){
    all_edges[i].setIfOpen(false);
  }
  //ix is position
  for(int ix = 0; ix < n; ix++){
    queue<long long int> stack;
    //iy is label
    for(int iy = 0; iy < (int)edges[ pos[ix] ].size(); ++iy){
      countOpenAndCloseEdges(ix, iy, stack, tree);
    }
    //該当場所のすべての辺を閉じてから交差数を数えるべし
    for(; !stack.empty(); stack.pop()){
      countSingleEdge(count, tree, stack);
    }
    //cout << ".";// << count ;
  }
  //cout << "over" << endl;
  return count;
}

//follow the format from readme.md
void readGraph(){
  cin >> n >> m;
  cin >> k;
  edges.resize(n, vector<int>() );
  index_of_edges.resize(n, vector<long long int>());
  for(int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp; 
    v.push_back(tmp - 1); 
    pos.push_back(tmp - 1);
  }
  int iv, iu;
  //from 1 index to 0 index
  while(cin >> iv >> iu){
    if( iv == iu ) continue;
    iv -= 1;
    iu -= 1;
    edges[iv].push_back(iu);
    edges[iu].push_back(iv);
    index_of_edges[iv].push_back((long long int)all_edges.size());
    index_of_edges[iu].push_back((long long int)all_edges.size());
    all_edges.push_back(Edge(iv, iu));
  }
  //position will be decided by greed-append
}

void printGraph(){
  cout << n << " " << m << endl;
  cout << k << endl;
  for(int i = 0; i < n; ++i){
    cout << (pos[i] + 1) << endl;
  }
  for(int i = 0; i < (int)edges.size(); ++i){
    for(auto ix = edges[i].begin(); ix != edges[i].end(); ++ix){
      if((*ix) < i) 
        cout << (i + 1) << " " << ((*ix) + 1) << " [0]" << endl;
    }
  }
}

//debug
void printPos(){
  cout << "label:     |" ;
  for(int i = 0; i < (int)pos.size(); ++i)
    printf("%4d|", i);

  cout << endl;

  cout << "pos list:  |" ;
  for(auto i = pos.begin(); i != pos.end(); ++i)
    printf("%4d|", *i);

  cout << endl;

}

//debug
void printEdges(){
  for(int i = 0; i < n; ++i){
    printf("[%d]:", i);
    for(int ix = 0; ix < (int)edges[i].size(); ++ix){
      cout << edges[i][ix] << " ";
    }
    cout << endl;
  }
}
//debug
void debug(){
  printEdges();
}

