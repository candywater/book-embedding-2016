//multiページ,順序のすでに決まっている頂点の交差数を数える、BITによる実装した計算機。
//テスト済み
//seikai y. 2016.09.27
//一ページで、出ていく辺で、交差数を数える。
//すべての頂点の順序はすでに決まっている
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <assert.h>
#define swap(type,a,b){type t = a; a = b; b = t;}

using namespace std;

class edge{
	private:
		bool open = false;
	public:
		int x,y;
		int page;
		edge(int, int);
		edge(int, int, int);
		bool isopen();
		bool isopen(bool);
};
edge::edge(int x, int y){
	if(x > y) swap(int, x, y);
	this->x = x;
	this->y = y;
}
edge::edge(int x, int y,int page){
	if(x > y) swap(int, x, y);
	this->x = x;
	this->y = y;
	this->page = page;
}
bool edge::isopen(){
	return this->open;
}
bool edge::isopen(bool open){
	this->open = open;
	return this->open;
}

//binary indexed tree
//indexes of BIT start from 1
class bit{
	private:
		vector<long long int> tree;
	public:
		bit(int);
		long long int sum(int);
		long long int sum(int, int);
		long long int value(int);
		void add(int, long long int);
		void printTree();
};
//constructor
bit::bit(int length){
	tree.clear();
	tree.resize(length+1, 0);
}
//[1, i]の範囲内での合計値
long long int bit::sum(int i){
	if(i <= -1) return 0;
	i++;
	long long int s = 0;
	while(i > 0){
		s += tree[i];
		i -= (i & -i);
	}
	return s;
}
//[i, j]の範囲内での合計値
long long int bit::sum(int i, int j){
	if(i > j) swap(int, i, j);
	return sum(j) - sum(i-1);
}
long long int bit::value(int i){
	return sum(i, i);
}
void bit::add(int i, long long int x){
	i += 1;
	while(i <= tree.size()){
		tree[i] += x;
		i += (i & -i);
	}
}
void bit::printTree(){
	printf("|node|");
	int i = 1;
	while(i != tree.size())
		printf("%4d|", (i++)-1);
	cout << endl;
	cout << "|leaf|";
	i = 1;
	while(i != tree.size())
		printf("%4lld|", value((i++) - 1));
	cout << endl;
	cout << "|real|";
	i = 1;
	while(i != tree.size())
		printf("%4lld|", tree[i++]);
	cout << endl;
	cout << endl;
}

static int n,m,k;
static vector<edge> edges;
//すべての辺がどの頂点にあるのか
static vector<queue<int> > all;
static vector<int> nodes;//nodes[pos] = label
//bestNodes[pos] = label
static vector<int> bestNodes;
//bestPos[label] = pos
static vector<int> bestPos;
static vector<bit> trees;
long long int crossingSum = 0;

int main(void){
	//INPUT
	cin >> n >> k ;
	nodes.resize(n, 0);
	all.resize(n, queue<int>());
	for(int i = 0;i < n;i++){
		int t;
		cin >> t;
		nodes[i] = t;
	}

	int a,b,c;
	while(scanf("%d %d [%d]",&a, &b, &c) != EOF){
		int itmp = edges.size();
		all[a].push(itmp);
		all[b].push(itmp);
		edge tmp = edge(a,b,c);
		edges.push_back(tmp);
		//cout << "edges.size:" << itmp<< endl;
	}

	//cout << "input process over\n";

	//ここは暫定的にこういう処理をする。つまり、入力のデータの交差数を数える。
	//bestNodes[pos] = label
	bestNodes = nodes;
	//bestPos[label] = pos
	bestPos.resize(n, 0);
	for(int i = 0; i < n; i++){
		bestPos[bestNodes[i]] = i;
	}
	
	//k page の場合
	trees.resize(k, bit(n));
	//cout << "created BIT\n";
	//tree.printTree();

	for(int i = 0; i < n; i++){
		queue<int> stack;
		for(int ia = all[i].front(); all[i].empty() != true; all[i].pop(), ia = all[i].front()){
			if(!edges[ia].isopen()){
				edges[ia].isopen(true);
				int p = edges[ia].page;
				trees[p].add(i, 1);
			}
			else{
				edges[ia].isopen(false);
				int p = edges[ia].page;
				int ix = edges[ia].x;
				int iy = edges[ia].y;
				ix = bestPos[ix];
				iy = bestPos[iy];
				if(ix > iy) swap(int, ix, iy);
				trees[p].add(ix, -1);
				stack.push(ia);
				//tree.printTree();
			}
		}
		//該当場所のすべての辺を閉じてから交差数を数えるべし
		if(stack.empty() != true)
			for(int ia = stack.front(); stack.empty() != true; stack.pop(), ia = stack.front()){
				int p = edges[ia].page;
				int ix = edges[ia].x;
				int iy = edges[ia].y;
				ix = bestPos[ix];
				iy = bestPos[iy];
				if(ix > iy) swap(int, ix, iy);
				//二つの点の間に一つ以上の点が存在する場合
				if(iy - ix > 1) 
					crossingSum += trees[p].sum(ix + 1, iy - 1);
				//printf("ix:%d  iy:%d\n", ix, iy);
				//cout << "sum-ia:" << ia<< "(" << edges[ia].x<<","<<edges[ia].y<<")" ;
				//cout << "crossing: "<<crossingSum<<endl;
			}
	}

	cout << "crossing:" << crossingSum << endl;

	return 0;
}
