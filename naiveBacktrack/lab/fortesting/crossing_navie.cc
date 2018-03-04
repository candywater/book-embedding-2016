//検証用navie な数え方(１ページバージョン)
#include <stdio.h>
#include <iostream>
#include <vector>
#define swap(type, a, b){type t = a; a = b; b = t;}

using namespace std;

class edge{
	private:
		bool open = false;
	public:
		int x,y;
		int page;
		edge(int x, int y);
		edge(int x, int y, int page);
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

static vector<int> nodes;
static vector<int> pos;

bool ifcrossing(edge x, edge y){
	int x1 = pos[x.x];
	int x2 = pos[x.y];
	int y1 = pos[y.x];
	int y2 = pos[y.y];
	if(x1 > x2) swap(int, x1, x2);
	if(y1 > y2) swap(int, y1, y2);
	if(x1 < y1 && y1 < x2 && x2 < y2)
			return true;
	if(y1 < x1 && x1 < y2 && y2 < x2)
			return true;
	return false;
}

int main(){

	int n,m,k;
	cin >> n >> k;
	nodes.resize(n, 0);
	pos.resize(n, 0);
	for(int i = 0;i < n;i++){
		int tmp;
		cin >> tmp;
		nodes[i] = tmp;
		pos[i] = nodes[i];
	}

	vector<edge> edges;
	int a,b,c;
	while(scanf("%d %d [%d]",&a, &b, &c) != EOF){
		edges.push_back(edge(a,b,c));
	}

	long long int crossingNum = 0;

	printf("m:%lu\n", edges.size());

	for(int i = 0; i < edges.size() - 1; i++){
		//printf("(%d, %d)\n", edges[i].x, edges[i].y);
		for(int ix = i+1; ix < edges.size(); ix++){
			//printf("(%d, %d)-(%d, %d)\n", edges[i].x, edges[i].y, edges[ix].x, edges[ix].y);
			crossingNum += ifcrossing(edges[i], edges[ix]);
			//cout << "crossing:" << crossingNum << endl;
		}
	}

	cout << "crossing:" << crossingNum << endl;

	return 0;

}
