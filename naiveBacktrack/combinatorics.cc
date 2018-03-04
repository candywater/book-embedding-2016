#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#define false 0
#define true 1

using namespace std;
/*
seikai y.
201602

こんな大掛かりなプログラムなんてはじめてだよーーーーーーーーTAT
*/


void vexticesCombinatorics(int n);
void edgesCombinatorics();
void edgesCom(map<pair<int,int>,int>::iterator ix);
//=================
extern void input();
extern void reset();
extern void controller();
extern int sumOfCrossings();
extern int sumOfPerPage();
extern int judgeCrossings(int x1,int x2,int y1,int y2);
extern void insertBestCom(int);
extern void BestComOutput();
//=================
//TEST
extern void test();
extern void testJudgeCrossing();
extern void testJudgeCrossing1(int i);
extern void testVexticesCombinatorics();
extern void testVexticesCombinatorics1();
extern void testEdgesCombinatorics();
extern void testSumOfCrossings(int);
extern void testSumOfPerPage(int);
//=================
extern int numOfNodes;
extern int numOfPages;
extern int numOfEdges;
extern map<int,int> vexticesMap;
extern map<int,int> bestVexticesMap;
extern map<pair<int,int>,int> edges;
extern map<pair<int,int>,int> bestEdges;
//暫定解を格納する変数
extern int bestNumOfCross;
//=================
extern int countTest;
extern int countTestVextex;
//=================

//背表紙のすべての頂点の組み合わせ
//backtrack
//vexticesCombinatorics(0,numOfNodes,vextices,...略)
void vexticesCombinatorics(int n){
//nは背表紙の現在のlabel,numOfNodesは頂点の数,*vexticesは背表紙の現在の頂点の割り当て状態
//map<int,int> vexticesMap;
//前のintはlabel、後ろのintは頂点のposition
//現在、int \*vexticesは要らない
  if(n==numOfNodes){
    //testVexticesCombinatorics1();
    edgesCombinatorics();//パラメーターは後で
    return;
  }
  for(int i=0;i<numOfNodes;i++){
    if(vexticesMap.count(i)!=0){
      continue;
    }
    vexticesMap.insert(make_pair(i,n));
    vexticesCombinatorics(n+1);
    vexticesMap.erase(i);
  }
  return;
}

void edgesCombinatorics(){
  countTest=0;
  map<pair<int,int>,int>::iterator ix=edges.begin();
  edgesCom(ix);
  return;
}

void edgesCom(
  map<pair<int,int>,int>::iterator ix
  ){
    //cout<<(ix->first).first<<" "<<(ix->first).second<<" "<<ix->second<<endl;
    if(ix==edges.end()){
      //testEdgesCombinatorics();
      sumOfCrossings();
      return;
    }
    for(int iy=0;iy<numOfPages;iy++){
      ix->second=iy;
      ix++;
      edgesCom(
        ix
        );
      ix--;
      ix->second=-1;
    }
  }
