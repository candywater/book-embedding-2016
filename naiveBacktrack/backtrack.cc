#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <climits>
#include <stdlib.h>
#include <ncurses.h>
#include <fstream>
#include <time.h>
#define false 0
#define true 1

using namespace std;
/*
seikai y.
201602

こんな大掛かりなプログラムなんてはじめてだよーーーーーーーーTAT
*/
/*
 the defination of book embedding
 book with k pages consists of k half-spaces, the pages, that share a single line, the spine of the book. A k-page book embedding of a graph is an embedding of a graph into a book with k pages such that all the vertices lie at distinct positions of the spine and every edge is drawn in one of the pages such that only its endpoints touch the spine.
  edges may only cross if they are assigned to the same page.
 */

/*
◇バックトラックですべての解となるものを探す
問題は http://www.csun.edu/gd2015/challenge.htm
  Graph Drawing Challenge 2015
  Crossing minimization in book embeddings:Automatic
  -can use any their own tools.
  -to solve the challenge automatically
  -can do manual fine-tuning

purpose:
  minimizing the number of crossings in a book embedding with k pages.
  INPUT:arbitrary undirected graph,k pages
  OUTPUT:a)an ordering of the vertices along the spaine
         b)an assignment of the edges to the pages
  制限時間：1 hour
 */
/*
 book embedding
 -独自なプログラムorツールで解く
 -自動的にプログラムを動かせる
 -パラメーターに応じて調整可能

INPUT:無向グラフ、ページ数ｋ
OUTPUT: 1)本の背表紙での頂点の順番
        2)エッジがどのページに割り当てているのか
目的:各ページの交差点の和が最小になるように
制限時間（無視）:一時間
制限フォーマット:ACSII
 */
/*
 6  #num of nodes, num of vextices (N)
 2  #num of pages (K)
 0  #node of the spine
 1
 2
 3
 4
 5  #end of node of the spine
 0 1 [1]                 # Edge between Node 0 and Node 1 on page 1
 0 3 [0]                 # Edge between Node 0 and Node 3 on page 0
 0 5 [0]                 # Edge between Node 0 and Node 5 on page 0
 1 2 [1]                 # Edge between Node 1 and Node 2 on page 1
 1 4 [0]                 # Edge between Node 1 and Node 4 on page 0
 2 4 [1]                 # Edge between Node 2 and Node 4 on page 1
 2 5 [0]                 # Edge between Node 2 and Node 5 on page 0
 4 5 [1]
 */
/*
 main->INPUT mesort->process mesort->output mesort->end



 */

void input();
void reset();
void controller();
extern void vexticesCombinatorics(int n);
extern void edgesCombinatorics();
void edgesCom(map<pair<int,int>,int>::iterator ix);
int sumOfCrossings();
int sumOfPerPage(std::vector<pair<int,int> > *v);
int judgeCrossings(int x1,int x2,int y1,int y2);
void insertBestCom(int);
void BestComOutput();
void outputScreen(int);
//=================
//TEST
extern void test();
extern void testInput();
extern void testJudgeCrossing();
extern void testJudgeCrossing1(int i);
extern void testVexticesCombinatorics();
extern void testVexticesCombinatorics1();
extern void testSumOfCrossings(int);
extern void testSumOfPerPage(int);
//=================
//global parameters
int numOfNodes=0;
int numOfPages=0;
int numOfEdges=0;
map<int,int> vexticesMap;//front int is the label, beyond int is the position
map<int,int> bestVexticesMap;
map<pair<int,int>,int> edges;//beyond int is page
map<pair<int,int>,int> bestEdges;
clock_t t_start=clock();
//暫定解を格納する変数
int bestNumOfCross=INT_MAX;
//=================
extern int countTest;
extern int countTestVextex;
extern int countSumOfCrossings;
//=================


int main(void){
  //INPUT value
  //test();//also comment cout in sumOfCrossings
  controller();
  endwin();
  return 0;
}


/*入力は
 頂点1　頂点2　何ページ
 頂点1が頂点2より小さいように自動変換する<-これ重要
 */
void input(){
  cin>>numOfNodes;
  cin>>numOfPages;
  int tmp1,tmp2,tmp3;
  for(int i=0;i<numOfNodes;i++){
    cin>>tmp1;
    //vexticesMap.insert(make_pair(i,-1));
  }
  //while(scanf("%d %d [%d]",&tmp1,&tmp2,&tmp3)!=EOF){
  while(cin>>tmp1>>tmp2){
    cin.ignore(256,'\n');
    tmp3 = 0;
    edges.insert(
      make_pair(make_pair(tmp1,tmp2),tmp3)
    );
  }
  numOfEdges=edges.size();
  bestVexticesMap=vexticesMap;
  bestEdges=edges;
  //testInput();
  return;
}
void controller(){
/*20160206*/
  reset();
  input();
  initscr();
  vexticesCombinatorics(0);

  getch();
  BestComOutput();
}

int sumOfCrossings(){
  //which edge in perpage,pages[int],int is the page
  vector<vector<pair<int,int> > > pages;
  pages.resize(numOfPages, vector<pair<int,int> >());
  //vector<pair<int,int> > pages[numOfPages];
  int sumAllCount=0;
  for(map<pair<int,int>,int>::iterator ix=edges.begin();
  ix!=edges.end();ix++){
    pair<int,int> tmp =
      make_pair((ix->first.first),(ix->first.second));
    pages[(ix->second)].push_back(tmp);
  }

  for(int ix=0;ix<numOfPages;ix++){
    if((pages[ix]).size() == 0)
      continue;
    //cout<<"page("<<ix<<") ";//あとでコメントアウト
    sumAllCount+=sumOfPerPage(&pages[ix]);
    if(sumAllCount>=bestNumOfCross){
      outputScreen(sumAllCount);
      return sumAllCount;
    }
  }

  //testSumOfCrossings(sumAllCount);
  if(sumAllCount==0){
    insertBestCom(sumAllCount);
    BestComOutput();
    exit(1);
  }
  if(sumAllCount < bestNumOfCross){
    //cout<<"$$$$$$$$inserted%%%%%%%%%%\n";
    outputScreen(sumAllCount);
    insertBestCom(sumAllCount);}
  return sumAllCount;
}

int sumOfPerPage(vector<pair<int,int> > *pages){
  int x1,x2,y1,y2;
  int sumCount=0;
  for(vector<pair<int,int> >::iterator ix=pages->begin();
      ix!=pages->end()-1;ix++)
    for(vector<pair<int,int> >::iterator iy=ix+1;
        iy!=pages->end();iy++){
      x1=ix->first;x1=vexticesMap[x1];
      x2=ix->second;x2=vexticesMap[x2];
      y1=iy->first;y1=vexticesMap[y1];
      y2=iy->second;y2=vexticesMap[y2];
      sumCount+=judgeCrossings(x1,x2,y1,y2);
    }

  //testSumOfPerPage(sumCount);
  return sumCount;

}

void insertBestCom(int sum){
  bestNumOfCross=sum;
  bestVexticesMap=vexticesMap;
  bestEdges=edges;
  BestComOutput();
}


int judgeCrossings(int x1, int x2, int y1, int y2){
  //x1,x2;y1,y2 順序チェック
  if(x2<x1) swap(x1,x2);
  if(y2<y1) swap(y1,y2);
  if(x1==x2) puts("(error1_0)\n");
  if(y2==y1) puts("(error1_1)\n");
  if((x1==y1)&&(x2==y2)) puts("(error1_2)\n");
  //x1<x2,y1<y2は保証される
  /*
  //離れるまたは隣接する  case1&case2
  if(x1<y1 && x2<y2)
  if(x2<=y1) return false;
  if(x1>y1 && x2>y2)
  if(x1>=y2) return false;
  //包含するまたは包含するかつ頂点が重ねる   case3&case4
  if(x1<=y1 && x2>=y2)
  return false;
  if(x1>=y1 && x2<=y2)
  return false;
   */
  //交差する  case5&case6
  if(x1<y1 && x2<y2){
    if(x2>y1) return 1;
  }
  else if(x1>y1 && x2>y2){
    if(x1<y2) return 1;
  }
  return 0;
  /*puts("(error1_3)");
  return -1;*/
}
void reset(){
  numOfNodes=-1;
  numOfPages=-1;
  numOfEdges=-1;
  countTest=0;
  countTestVextex=0;
  bestNumOfCross=INT_MAX;
  vexticesMap.clear();
  bestVexticesMap.clear();
  edges.clear();
  bestEdges.clear();
}

void BestComOutput(){
  erase();

  mvprintw(7,0,"================time of best solution:%lfs",((double)clock()-t_start)/CLOCKS_PER_SEC);
  int a[numOfNodes];
  for(auto i:a) i=0;
  mvprintw(8,0,"# Number of Nodes:%d",numOfNodes);
  mvprintw(9,0,"# Number of Pages:%d",numOfPages);
  mvprintw(10,0,"# Nodes on spine\n");
  for(map<int,int>::iterator ix=bestVexticesMap.begin();
      ix!=bestVexticesMap.end();ix++)
    a[ix->second]=ix->first;
  for(int i=0;i<numOfNodes;i++)
    printw("%5d",a[i]);

  mvprintw(14,0,"# Edges\n");
  int iz=0;
  for(map<pair<int,int>,int>::iterator ix=bestEdges.begin();
      ix!=bestEdges.end();ix++,iz++)
    printw("%d-%d[%d] ",ix->first.first,
        ix->first.second,ix->second);

  mvprintw(20,0,"#smallest num of crossings:%d     ",
      bestNumOfCross);


  ofstream ofs("./output.txt",ios::app);
  ofs<<"================"<<((double)clock()-t_start)/CLOCKS_PER_SEC<<"s ======"<<endl;
  ofs<<"# Number of Nodes:"<<numOfNodes<<endl;
  ofs<<"# Number of Pages:"<<numOfPages<<endl;
  ofs<<"# Nodes on spine"<<endl;
  for(int i=0;i<numOfNodes;i++){
    ofs<<a[i]<<" ";
  }
  ofs<<endl;
  ofs<<"# Edges"<<endl;
  for(auto ix=bestEdges.begin();
      ix!=bestEdges.end();ix++)
    ofs<<ix->first.first<<"-"<<ix->first.second<<"["<<ix->second<<"] ";
  ofs<<endl;
  ofs<<endl;
  ofs<<"#smallest nm of crossings:"<<bestNumOfCross<<endl;

  getch();

  /*
     cout<<"===================================\n";
     int a[numOfNodes]={0};
     cout<<"# Number of Nodes\n";
     cout<<numOfNodes<<endl;
     cout<<"# Number of Pages\n";
     cout<<numOfPages<<endl;
     cout<<"# Nodes on spine\n";
     for(map<int,int>::iterator ix=bestVexticesMap.begin();
     ix!=bestVexticesMap.end();ix++)
     a[ix->second]=ix->first;
     for(int i=0;i<numOfNodes;i++)
     cout<<a[i]<<endl;

     cout<<"# Edges\n";
     for(map<pair<int,int>,int>::iterator ix=bestEdges.begin();
     ix!=bestEdges.end();ix++)
     cout<<ix->first.first<<" "
     <<ix->first.second<<" "
     <<"["<<ix->second<<"]"<<endl;

     cout<<"#smallest num of crossings:"
     <<bestNumOfCross<<endl;
     cout<<"===================================\n\n";
   */

}

void outputScreen(int sum){

  mvprintw(2,0,"time now:%lfs",((double)clock()-t_start)/CLOCKS_PER_SEC);
  mvprintw(3,0,"num of calculations:%lld",++countSumOfCrossings);
  mvprintw(4,0,"sumOfCrossings:%d",sum);
  mvprintw(5,0,"bestNumOfCross:%d",bestNumOfCross);
  getch();
}

