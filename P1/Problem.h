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
	//地区类型
	ORD = 0,//普通地点
	SRC = 1,//起点
	MINE = 2,//矿山
	VIL=3,//村庄
	DST = 4,//终点
	//天气类型
	sun=0,hypet=1,sand=2,
};


struct graph {
	int state = 0;//标记本身
	int dis = 0;//该点距离终点的最短路径长度->方便后续剪枝
	vector<int> neibors;//邻居地点

};

struct Resource;

struct Resource {
	int money = 0;
	int water = 0;
	int food = 0;
	Resource() {}
	Resource(int x, int y, int z) : money(x), water(y), food(z) {}
	Resource(const Resource &tmp) : money(tmp.money), water(tmp.water), food(tmp.food) {}
	//重载操作符
	Resource operator + (Resource tmp) {
		Resource res;
		res.money = money + tmp.money;
		res.water=water  + tmp.water;
		res.food = food+ tmp.food;
		return res;
	}
	Resource operator - (Resource tmp) {
		Resource res;
		res.money = money - tmp.money;
		res.water = water - tmp.water;
		res.food = food - tmp.food;
		return res;
	}
	Resource operator * (int num) {
		Resource res;
		res.money = money * num ;
		res.water = water * num ;
		res.food = food * num ;
		return res;
	}

	
	void operator = (Resource tmp) {
		money = tmp.money;
		water = tmp.water;
		food = tmp.food;
	}
	

};



const int MAX_STEP = 30;//限制日期数
const int MAX_SPOT = 50; //地图上最多的地点数
const int MAXCOST = 2147483647;
const int waterpri = 5;
const int foodpri = 10;


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
	static  vector <Resource> resource;
	void construct_table();
	void bfs_getDis();//计算其他点到终点的最短距离
	void set1_dp(int weather[],int dest);
	void init(Resource dpmap[MAX_STEP+2][MAX_SPOT+2]);


};

