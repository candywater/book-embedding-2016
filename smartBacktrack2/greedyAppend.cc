#include "h_head.h"
#include <set>
#include <random>
#include <assert.h>

void greedyAppend();

namespace{

class connect_comp{
  private:
  public:
    bool operator() (const int&, const int&) const;
};


void connectivity();
void crossingAppend();
void crossingAppendStart();
void crossingAppendSequence(int&, int&);
void crossingAppendEnd(const int&, const int&);
long long int ifLeft(const int&, const int&, const int&);
long long int ifRight(const int&, const int&, const int&);
void closeOrOpenEdges(const int&, const int&);

//debug
void printQueue();
void printPosition();
void greedyDebug();

//num of inward connectivity(すでに配置された頂点)
vector<int> num_of_connect;
set<int, connect_comp> connect_queue;
//BIT is 1 index, not 0 index; 
//but call BIT should use 0 index
//it need not to consider about the index of bit
BIT b_i_tree;
}


//num_of_connectの大きい方を優先
//(inward connectivity)
//次にedges[i].size() - num_of_connect[i]の小さい方を優先
//(outward connectivity)
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

void greedyAppend(){
  connectivity();
  //cout << "connectivity, ok" << endl;
  crossingAppend();
  //cout << "crossing, ok" << endl;
}

namespace{
void connectivity(){
  for(int i = 0; i < n; i++)
    //num of N(v) that already inserted
    num_of_connect.push_back(0);
  for(int i = 0; i < n; i++)
    connect_queue.insert(i);
}

void crossingAppendStart(){
  random_device rd;

  //process of start_ver(tex)
  int start_ver = static_cast<int>(rd());
  start_ver = start_ver >= 0 ? start_ver % n : (-start_ver) % n;
  cout << "start_vertex: " << start_ver << endl;
  //ここでよくエグメントエラー出るのかな？
  assert (start_ver >= 0);

  connect_queue.erase(start_ver);
  for(int i = 0; i < (int)edges[start_ver].size(); ++i){
    //update the priority queue
    int itmp = edges[start_ver][i];
    connect_queue.erase(itmp);
    num_of_connect[itmp] += 1;
    connect_queue.insert(itmp);
    //make edges open
    all_edges[index_of_edges[start_ver][i]].reverseOpen();
  }

  //set start postion as 0 
  //(1 index in BIT, 
  //so 0 will be transformed automatelly to 1)
  b_i_tree.add(0, (int)edges[start_ver].size());
  v[start_ver] = 0;
  pos[0] = start_ver;
}

long long int ifLeft(const int& vertex_chosen, const int& left, const int& right){
  long long int crossing_count = 0;
  for(int i = 0; i < (int)edges[vertex_chosen].size(); ++i){
    int ilabel = edges[vertex_chosen][i];
    int i_pos = pos[ilabel];
    //i_pos >= left && i_pos <= right は想定しない
    if(i_pos >= 0 && i_pos < left){
      crossing_count += b_i_tree.sum(i_pos + 1, left - 1);
    }
    else{
      crossing_count += b_i_tree.sum(i_pos + 1, n - 1);
      crossing_count += b_i_tree.sum(0, left - 1);
    }
  }
  return crossing_count;
}

long long int ifRight(const int& vertex_chosen, const int& left, const int& right){
  long long int crossing_count = 0;
  for(int i = 0; i < (int)edges[vertex_chosen].size(); ++i){
    int ilabel = edges[vertex_chosen][i];
    int i_pos = pos[ilabel];
    //i_pos >= left && i_pos <= right は想定しない
    if(i_pos >= 0 && i_pos <= left){
      crossing_count += b_i_tree.sum(0, i_pos - 1);
      crossing_count += b_i_tree.sum(n - 1, right - 1);
    }
    else{
      crossing_count += b_i_tree.sum(i_pos - 1, right - 1);
    }
  }
  return crossing_count;
}

/*debug*/
void printQueue(){
  for(auto i = connect_queue.begin(); i != connect_queue.end(); ++i)
    cout << *i << " "; 
  cout << endl;
}

void closeOrOpenEdges(const int& vertex_chosen, const int& position){
  //close or open edges
  for(int i = 0; i < (int)index_of_edges[vertex_chosen].size(); ++i){
    Edge *tmp = &all_edges[index_of_edges[vertex_chosen][i]];
    if(tmp->isOpen())
      b_i_tree.add(position, -1);
    else
      b_i_tree.add(position, 1);
    tmp->reverseOpen();
    //update the priority queue
    int itmp = edges[vertex_chosen][i];
    bool flag = connect_queue.count(itmp) >= 1;
    connect_queue.erase(itmp);
    //必ず決めてからkey valueを変えること
    //そうしなければ、うまく削除できない
    num_of_connect[itmp] += 1;
    if(flag)
      connect_queue.insert(itmp);
  }
}

/*debug*/
void printPosition(){
  for(int i = 0; i < n; ++i){
    cout << pos[i] << " ";
  }
  cout << endl;
}

//debug
void greedyDebug(){
  printPosition();
  printQueue();
}


void crossingAppendSequence(int& left, int& right){
  //in fact, (left != right) is enough
  while(left != right && (connect_queue.size() > 1) ){
    int vertex_chosen = *connect_queue.begin();
    //delete it from the queue
    connect_queue.erase(vertex_chosen);

    //it is 0 index here, 
    //so it need not to consider about bit position
    int position = 0;
    //left is not real left, but the "left" side
    //the same as right
    //**be care of the edge which is going to be closed**
    if( ifLeft(vertex_chosen, left, right) < ifRight(vertex_chosen, left, right) )
      position = left++;
    else
      position = right--;

    v[vertex_chosen] = position;
    pos[position] = vertex_chosen;

    //close or open edges (and update the perm of queue)
    closeOrOpenEdges(vertex_chosen, position);
    //cout << "crossing sequence, left(" << left << "), right(" << right << "), size of queue:" << connect_queue.size() << endl;
    //cout << ".";
  }
}

void crossingAppendEnd(const int& left, const int& right){
  int vertex_last = *connect_queue.begin();
  v[vertex_last] = left;
  pos[left] = vertex_last;
  //後処理(処理しなくてもいいが、交差数を数えるために処理する)
  connect_queue.clear();
  /*for(int i = 0; i < (int)index_of_edges[vertex_last].size(); ++i){
    Edge* tmp = &all_edges[index_of_edges[vertex_last][i]];
    tmp->reverseOpen();
    }*/
}

//crossing perm
void crossingAppend(){
  //pos of first vertex is 0
  //because bit is 1 index
  //so 0 will be tranformed automate to 1
  b_i_tree = BIT(n);

  //position will be set vertex from left side
  int left = 1;
  //position will be set vertex from right side
  int right = n - 1;

  //cout << "greedy-Appending now";
  //choose the first vertex
  crossingAppendStart();
  //inserting perm (except the last one)
  crossingAppendSequence(left, right);
  //last vertex to insert
  crossingAppendEnd(left, right);
  //cout << "over" << endl;
}
}
