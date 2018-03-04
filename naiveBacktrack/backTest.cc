#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <ncurses.h>
#include <time.h>
#define false 0
#define true 1

using namespace std;
/*
seikai y.
201602

こんな大掛かりなプログラムなんてはじめてだよーーーーーーーーTAT
*/

void test();
void testInput();
void testJudgeCrossing();
void testJudgeCrossing1(int i);
void testVexticesCombinatorics();
void testVexticesCombinatorics1();
void testEdgesCombinatorics();
void testSumOfCrossings(int);
void testSumOfPerPage(int);

extern void input();
extern void reset();
extern void controller();
extern void vexticesCombinatorics(
  int n
  );
extern void edgesCombinatorics();
extern void edgesCom(
  map<pair<int,int>,int>::iterator ix
  );
extern int sumOfCrossings();
extern int sumOfPerPage();
extern int judgeCrossings(int x1,int x2,int y1,int y2);
extern void insertBestCom(int);
extern void BestComOutput();
//=================
extern int numOfNodes;
extern int numOfPages;
extern int numOfEdges;
extern map<int,int> vexticesMap;
extern map<int,int> bestVexticesMap;
extern map<pair<int,int>,int> edges;
extern map<pair<int,int>,int> bestEdges;
extern clock_t t_start;
//暫定解を格納する変数
extern int bestNumOfCross;
//=================
int countTest=0;
int countTestVextex=0;
unsigned long long int countSumOfCrossings=0;
//=================


void test(){
  //testJudgeCrossing();
  testVexticesCombinatorics();
  BestComOutput();
  return;
}
void testVexticesCombinatorics(){
  //20160206テスト済み
  //テストするのに、仮想のデータが必要ということで、できるだけ簡単なデータを用意する
  numOfNodes=4;
  numOfPages=2;
  //int vextices[4]={0,1,2,3};
  /*上のvextices[4]は要らないが、
  もし頂点のラベルが0-3の順番でなければ、
  必要になってくる
  現在は必要としない
  */
  edges.insert(make_pair(make_pair(0,1),-1));
  edges.insert(make_pair(make_pair(0,3),-1));
  edges.insert(make_pair(make_pair(1,2),-1));
  edges.insert(make_pair(make_pair(1,3),-1));
  edges.insert(make_pair(make_pair(2,3),-1));
  numOfEdges=edges.size();
  bestEdges=edges;
  vexticesCombinatorics(
    0
    );
}
void testVexticesCombinatorics1(){
  //表示しているのが頂点のラベルである label in order
  cout<<"=="<<++countTestVextex<<":\t";
  cout<<"{";
  for(map<int,int>::iterator ix=vexticesMap.begin();
      ix!=vexticesMap.end();ix++)
    cout<<ix->second<<" ";
  cout<<"\b}==\n";
}
void testEdgesCombinatorics(){
  //label and line, not position
  cout<<"\t"<<++countTest<<":";
  cout<<"{";
  for(map<pair<int,int>,int>::iterator ix=edges.begin();
    ix!=edges.end();ix++){
    cout<<"("<<(ix->first).first<<",";
    cout<<(ix->first).second<<")";
    cout<<"["<<ix->second<<"], ";
  }
  cout<<"\b\b}"<<endl;
}



void testJudgeCrossing(){
  //20160206テスト済み
  cout << "--case1--" << endl;
  testJudgeCrossing1(judgeCrossings(0,1,2,3));
  testJudgeCrossing1(judgeCrossings(1,2,2,3));
  cout << "--case2--" <<endl;
  testJudgeCrossing1(judgeCrossings(9,10,4,7));
  testJudgeCrossing1(judgeCrossings(9,11,5,9));
  cout << "--case3--" <<endl;
  testJudgeCrossing1(judgeCrossings(0,10,2,6));
  testJudgeCrossing1(judgeCrossings(11,13,11,12));
  testJudgeCrossing1(judgeCrossings(15,17,16,17));
  cout << "--case4--" <<endl;
  testJudgeCrossing1(judgeCrossings(9,10,7,11));
  testJudgeCrossing1(judgeCrossings(5,6,6,9));
  testJudgeCrossing1(judgeCrossings(7,20,3,20));
  cout << "--case5--" <<endl;
  testJudgeCrossing1(judgeCrossings(10,15,12,17));
  cout << "--case6--" <<endl;
  testJudgeCrossing1(judgeCrossings(20,25,17,23));
}
void testJudgeCrossing1(int i){
  if(i==0) cout<<"  false"<<endl;
  else if(i==1) cout<<"  **true**"<<endl;
  else puts("(error-1_0)\n");
}


void testSumOfCrossings(int sum){
  //cout<<countTestVextex<<"-"<<countTest<<" ";

  /*cout<<++countSumOfCrossings<<"\n";
  cout<<"sumOfCrossings:"<<sum<<" \n";
  cout<<"bestNumOfCross:"<<bestNumOfCross<<"\n";*/

  mvprintw(2,0,"time now:%lf",(double)clock()-t_start);
  mvprintw(3,0,"num of calculations:%lld",++countSumOfCrossings);
  mvprintw(4,0,"sumOfCrossings:%d",sum);
  mvprintw(5,0,"bestNumOfCross:%d",bestNumOfCross);
  getch();

}

void testSumOfPerPage(int sum){
  //printw("sumOfPerPage:%d\n",sum);
  cout<<"sumOfPerPage:"<<sum<<endl;
}

void testInput(){
  map<int,int>::iterator ix=vexticesMap.begin();
  cout<<"1111\n";
  for(;ix!=vexticesMap.end();ix++){
    cout<<ix->first<<" "
    <<ix->second<<"\n";
  }
  cout<<"2222\n";
  map<pair<int,int>,int>::iterator iy=edges.begin();
  for(;iy!=edges.end();iy++){
    cout<<iy->first.first<<" "
    <<iy->first.second<<" "
    <<iy->second<<"\n";
  }
}
