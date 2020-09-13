#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/* 
	+------------基本参数设置--------------+

*/

const int MAX_STEP = 30;//限制日期数
const int MAX_SPOT = 65; //地图上最多的地点数
const int MAXCOST = 2000;
const int waterpri = 5;
const int foodpri = 10;
const int watersz = 3;
const int foodsz = 2;
const int MAXPAC = 1200;
const int MYMONEY = 10000;

enum {
	//地区类型
	ORD = 0,//普通地点
	SRC = 1,//起点
	MINE = 2,//矿山
	VIL=3,//村庄
	DST = 4,//终点
	//天气类型
	SUNNY=0,HYPE=1,SAND=2,
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
	bool operator == (Resource tmp) {
		if (money == tmp.money && water == tmp.water && food == tmp.food)
			return true;
		return false;
	}
	bool operator < (Resource tmp) {
		if ( water < tmp.water && food < tmp.food)
			return true;
		return false;
	}
	
	
};





class PROBLEM
{
protected:

	vector<graph> map;
	Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2];
	Resource package;
	string filename;
	
public:
	PROBLEM() {}
	PROBLEM(string setname): filename(setname) {}
	~PROBLEM(){
		vector<graph>().swap(map);//释放vector内存空间
	}
	friend class TEST;
	friend class Sol2;
    vector <Resource> resource;
	void construct_table();
	void bfs_getDis();//计算其他点到终点的最短距离
	int set1_dp(int weather[],int dest);
	void init();
	int getres_set1();
	void check_path(int day,int dest);
	int check_vil(int reachday, int dest);

};

class Sol2 {
	
private:
	//int R[30];//记录每个点的分值
	int psunny = 0.45;
	int phype = 0.45;
	int psand = 0.1;
	
protected:

public:
	void init();
	void get_R();
	void get_Q(int weather[],PROBLEM set4);
	void judge_state(int weather,PROBLEM set4);
};