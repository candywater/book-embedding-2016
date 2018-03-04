#include "h_head.h"
#include "class_head.h"
#include <limits.h>
#include <assert.h>
#include <algorithm>

void circularSifting();

int circular_local_round_num = 1;

//one_round_sifting returns the best pos to insert
namespace{
void oneRoundSifting();
//sifting for one vertex
//the best pos is between i and i+1
void siftingFor(const int&);
long long int tryToChangeWith(const int&, const int&);
void makeListForChanging(vector<int>&, vector<int>&, const int&, const int&);
//(i, j) insert i between j and j+1
void changeVertices(const int&, const int&);
bool judgePos(const int&, const int&, const int&);

long long int circular_count;
}

void circularSifting(){

  circular_count = crossingCount();

  for(int i = 0; i < circular_sifting_round; ++i){
    //printf("circular_round = %d", circular_sifting_round);
    printf("round[%3d] now, ", i+1);
    oneRoundSifting();
    
    long long int t_count = crossingCount();
    if(t_count == circular_count) {
      circular_local_round_num = i + 1;
      return;
    }
    else circular_count = t_count;
    printf("count_now: %lld ", circular_count);
    printf("over\n");
  }
}

namespace{
void oneRoundSifting(){
  //position 
  for(int vertex_chosen = 0;vertex_chosen < n; ++vertex_chosen){
    //(pos, ipos)
    siftingFor(vertex_chosen);
    //printf(".");
  }
}

//１頂点グラフでも通用するかも
//一つの頂点に対して一周回す
//(pos, ipos)
void siftingFor(const int& vertex_chosen){

  long long int crossing_num = 0;
  int local_best_pos = (vertex_chosen - 1 + n) % n;
  //record position

  long long int tmp = 0;
  //一周回す
  for(int vertex_change = (vertex_chosen + 1) % n; 
      vertex_change != vertex_chosen; 
      vertex_change = (++vertex_change) % n){

    tmp += tryToChangeWith(vertex_chosen, vertex_change);

    if(tmp < crossing_num){
      crossing_num = tmp;
      local_best_pos = vertex_change;
    }
  }
  changeVertices(vertex_chosen, local_best_pos);
}

//(label list, label list, label, label)
void makeListForChanging(vector<int>& x, vector<int>& y, 
    const int& lx, const int& ly){

  for(int i = 0; i < (int)edges[lx].size(); ++i){
    if(edges[lx][i] != ly)
      x.push_back(edges[lx][i]);

  }
  for(int i = 0; i < (int)edges[ly].size(); ++i){
    if(edges[ly][i] != lx)
      y.push_back(edges[ly][i]);
  }

  //pos compare
  //WARNING:ここの比べ方にご注意！
  auto comp = [&ly](const int& a, const int& b) 
    -> bool {
      return (v[a] - v[ly] + n) % n < (v[b] - v[ly] + n) % n;
    };
  sort(x.begin(), x.end(), comp);
  sort(y.begin(), y.end(), comp);

}

//TODO:
//(pos, pos)
long long int tryToChangeWith(const int& vertex_chosen, const int& vertex_change){
  //label of vertex x
  int lx = pos[vertex_chosen];
  //label of vertex y
  int ly = pos[vertex_change];

  vector<int> x;
  vector<int> y;
  makeListForChanging(x, y, lx, ly);
  int i = 0; 
  int j = 0;
  long long int c = 0;
  while(i < (int)x.size() && j < (int)y.size()){
    if(judgePos(x[i], y[j], vertex_change)){
      c -= ((int)y.size() - j);
      //printf("(1:)x[%d]:%d, y[%d]:%d, v:%d, c:%lld\n", i, x[i], j, y[j], pos[vertex_change], c);
      ++i;
    }
    else if(judgePos(y[j], x[i], vertex_change)){
      c += ((int)x.size() - i);
      ++j;
    }
    //x[i] = y[j]
    else{
      c = c + ((int)x.size() - i) - ((int)y.size() - j);
      ++i;
      ++j;
    }
  }
  return c;
}
//debug
/*cout << "x: ";
  for(auto i = x.begin(); i != x.end(); i++)
  printf("%4d|", *i);
  cout << endl << "y: ";
  for(auto i = y.begin(); i != y.end(); i++)
  printf("%4d|", *i);
  cout << endl;
 */




//TODO(label, label, label)
bool judgePos(const int& x, const int& y, const int&z){
  //assert ( ((v[x] - z + n) % n < (v[y] - z + n) % n) == ((v[x] < v[y] && v[y] < z) || (v[y] < z && z < v[x]) || (z < v[x] && v[x] < v[y])) );
  return  (v[x] - z + n) % n < (v[y] - z + n) % n;
}

/*
   ここで、
   listで頂点の入れ替えの時間はO(1)だが、iteratorを追跡する時間がO(n) である。
   vectorを用いてO(n)時間で頂点の入れ替えをしてもいい。
   だが、
   iteratorを追跡するとは、現在の暫定解と比べるたびに追跡するわけであって、
   vectorを利用すると、余分な時間を使ってしまうではないかと、考えている。
   （しかも時計回りでずらすか、反時計回りでずらすかは考慮せざるえない）
   しかしlistを利用することで、実装が難しくなってしまった。
   バグを埋めないように頑張る。
   2016-12-6
   でもlistにすると、random accessができなくなる途端、
   位置の前後関係の判定は、計算時間を食らってしまう。(毎回判定するのにO(n)時間がかかりそう）
   かえって効率悪くなる予想がする。(判定はm回やるので、O(nm)時間かかるのに対して、vectorによる頂点の入れ替えは、全部でn回やって、O(n^2)時間かかる。
   そのため、めんどいだが、ここの構造をやはりvectorにする
 */
//move vertex to position between (position) and (position + 1)
//(position, position)
void changeVertices(const int& vertex_chosen, const int& local_best_pos){
  assert (vertex_chosen != local_best_pos);
  //時計回り、反時計まわりなんて、とりあえず書かないことにした。
  int tmp = pos[vertex_chosen];
  pos.erase(pos.begin() + vertex_chosen);
  if(vertex_chosen < local_best_pos){
    pos.insert(pos.begin() + local_best_pos, tmp);
  }
  else if(vertex_chosen > local_best_pos){
    pos.insert(pos.begin() + local_best_pos + 1, tmp);
  }
  for(int i = 0; i < n; ++i){
    v[ pos[i] ] = i;
  }
}
}
