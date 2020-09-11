#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/* 
	+------------基本参数设置--------------+

*/

enum {
	ORD = 0,//普通地点
	SRC = 1,//起点
	MINE = 2,//矿山
	VIL=3,//村庄
	DST = 4,//终点
};


struct graph {
	int state = 0;//标记本身
	int dis = 0;//该点距离终点的最短路径长度->方便后续剪枝
	vector<int> neibors;//邻居地点

};



struct Resource {
	int money = 0;
	int water = 0;
	int food = 0;
	Resource() {}
	Resource(int x, int y, int z) : money(x), water(y), food(z) {}
	//重载操作符
	void operator + (Resource tmp) {
		money += tmp.money;
		water += tmp.water;
		food += tmp.food;
	}
	void operator - (Resource tmp) {
		money -= tmp.money;
		water -= tmp.water;
		food -= tmp.food;
	}
};



const int MAX_STEP = 30;//限制日期数
const int MAX_SPOT = 50; //地图上最多的地点数




class PROBLEM
{
protected:

	vector<graph> map;
	Resource package;
	string filename;

public:
	PROBLEM() {}
	PROBLEM(string setname): filename(setname) {}
	~PROBLEM(){
		vector<graph>().swap(map);//释放vector内存空间
	}
	friend class TEST;
	void construct_table();
	void bfs_getDis();//计算其他点到终点的最短距离



};

