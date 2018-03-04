#include "h_head.h"
#include <time.h>
#include <fstream>
#include <string>
#include <limits.h>

//n = |V|
int n;
//m = |E|
long long int m;
//num of page
int k;
//num of round(circular sifting)
int circular_sifting_round = 1;
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
  if(argc >= 2)
    circular_sifting_round = std::stoi(argv[1]);
  //cout << "hello, world." << endl;
  //circular_sifting_round = 3;


  init();

  readGraph();
  cout << "read, ok" << endl;
  long long int beforeCount = crossingCount();
  //cout << "before count, ok" << endl;
  //debug();

  clock_t time = clock();
  greedyAppend();
  clock_t greedy_time = clock() - time;
  cout << "greedAppend, ok" << endl;
  long long int afterGreedy = crossingCount();
  //printGraph();

  //debug
  //printPos();

  time = clock();
  circularSifting();
  clock_t sifting_time = clock() - time;
  cout << "circularSifting, ok" << endl;
  long long int afterSifting = crossingCount();

  //debug
  //printPos();
  time = clock();
  backtrack();
  clock_t backtrack_time = clock() - time;
  cout << "backtrack, ok" << endl;
  
  time = greedy_time + sifting_time + backtrack_time;
  printGraph();
  cout << "print, ok" << endl;

  cout << "num of crossing" << endl;
  cout << "before       :" << beforeCount << endl;
  cout << "after greedy :" << afterGreedy << endl;
  cout << "after sifting:" << afterSifting << endl;
  cout << "best sol:" << crossingCount() << endl;

  cout << "greedy time :\t" << fixed << static_cast<double>(greedy_time)/(CLOCKS_PER_SEC)*1000 << " [ms] \t(" 
    << fixed << static_cast<double>(greedy_time)/(CLOCKS_PER_SEC) << " [s])" << endl;
  cout << "sifting time:\t" << fixed <<  static_cast<double>(sifting_time)/(CLOCKS_PER_SEC)*1000 << " [ms]\t(" 
    << fixed << static_cast<double>(sifting_time)/(CLOCKS_PER_SEC) << " [s])" << endl;
  cout << "backtrack time:\t" << fixed <<  static_cast<double>(sifting_time)/(CLOCKS_PER_SEC)*1000 << " [ms]\t(" 
    << fixed << static_cast<double>(sifting_time)/(CLOCKS_PER_SEC) << " [s])" << endl;
  cout << "sum time:\t" << fixed << static_cast<double>(time)/(CLOCKS_PER_SEC)*1000 << " [ms]\t(" 
    << fixed << static_cast<double>(time)/(CLOCKS_PER_SEC) << " [s])" << endl;


  ofstream fs("./test_data_dir/20170127_kitani/excel", ios::app | ios::out);
  fs << n << "," << m << "," << beforeCount << "," << afterSifting << "," << static_cast<double>(time)/(CLOCKS_PER_SEC) << "," << circular_local_round_num << ", " << crossingCount() <<   endl;
  fs.close();
  return 0;
}
