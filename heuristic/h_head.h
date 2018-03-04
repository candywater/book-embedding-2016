#ifndef _H_HEAD_H_
#define _H_HEAD_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "class_head.h"

//n = |V|
extern int n;
//m = |E|
extern long long int m;
//num of page
extern int k;
//num of round(circular sifting)
extern int circular_sifting_round;
//vertices index from 1
extern vector<int> v;
//position index from 0
extern vector<int> pos;
//edges list
extern vector< vector<int> > edges;
//all edges
extern vector< Edge > all_edges;
//index of edge of two vertices
extern vector< vector<long long int> > index_of_edges;

//debug
extern int circular_local_round_num;

extern void init();
extern void readGraph();
extern void printGraph();
extern long long int crossingCount();
extern void greedyAppend();
extern void circularSifting();
//debug
extern void printPos();
extern void debug();

#endif
