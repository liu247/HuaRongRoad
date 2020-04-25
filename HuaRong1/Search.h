#pragma once

#include<cstdio>
#include<cstring>
#include<windows.h>
#include<time.h>

const int maxState = 100010;   //最大搜索队列范围，可作选择为bfs输入参数
const int hashSize = 128 * 1024;   //hash数组大小
const int maxheight = 200;  //最大搜索层数，可选择作为bfs输入参数
typedef char State[20];
#define hs17(h1,h) h=(h1&0x0001FFFF)^(h1>>17) //17位哈希值计算(折叠式计算)
#define hs15(h1,h) h=(h1&0x00007FFF)^(h1>>19) //15位哈希值计算(折叠式计算)
const int dx[] = { -1,0,1,0,-1,0,1,0 }; //上左下右上左下右
const int dy[] = { 0,-1,0,1,0,-1,0,1 };

const char U1[] = "ABBBBSSSSHC"; //棋子类型表
const char U2[] = "ABBBBHHSSSC"; //棋子类型表
const char U3[] = "ABBBBHHHHHC"; //棋子类型表

const char chess1[20] = {
	6,6,10,10,
	7,7,10,10,
	8, 8, 5, 5,
	1, 0, 3, 9,
	2, 0, 4, 9
};

const char chess2[20] = {
	7,10,10,3,
	7,10,10,4,
	8, 6, 6, 9,
	8, 5, 5, 9,
	1, 0, 0, 2
};

const char chess3[20] = {
	10,10,3,4,
	10,10,1,2,
	5, 5, 6, 6,
	7, 7, 8, 8,
	0, 9, 9, 0
};

const char chess4[20] = {
	3,10,10,9,
	4,10,10,9,
	7, 7, 8, 8,
	5, 5, 6, 6,
	1, 0, 0, 2
};
class Search
{
public:
	Search();
	~Search();
public:
	//unsigned int hsb[hashSize], hsb1[hashSize], hsb2[hashSize / 4]; //哈希表
	//State st[maxState];   //所有的状态数组，全部保存在此
	//State answer[maxheight];  //存储结果数组
	//int cur[maxState];  //父亲结点
	//int dist[maxState];   //距离数组
	unsigned int *hsb, *hsb1, *hsb2; //哈希表
	State *st;   //所有的状态数组，全部保存在此
	State *answer;  //存储结果数组
	int *cur;  //父亲结点
	int *dist;   //距离数组
	int front = 1;//队头
	int rear = 2; //队尾
	int count = 0;
	int mark;
	void init_lookup_table();
	int try_to_insert(char* s);
	void insert_queue(char* newchess);
	void check2(char* q);
	void walk_1(char* chess, int BS_1);
	void walk1_1(char* chess, int BS_1);
	void walk2_1(char* chess, int BS_1);
	void walk3_1(char* chess, int BS_1);
	void walk_2(char* chess, int BS_1, int BS_2);
	int bfs();
	void move(char* chess);
	void Run();
	void Run1(char chess[5][4]);
};

