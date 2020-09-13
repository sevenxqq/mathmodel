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

	vector<graph> map;//游戏地图
	Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2];//动态规划的记录
	Resource package;//背包
	string filename;//输入文件名来建立相应游戏地图
	
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
	int set1_dp(int weather[],int dest);//动态规划寻找路径
	void init();//一些初始化操作
	int getres_set1();//动态规划之后计算结果
	void check_path(int day,int dest);//打印路径
	int check_vil(int reachday, int dest);//判断路径上是否经过村庄

};

class Sol2 {
	
private:
	//天气概率参数，可以更改以获得其他情况
	int psunny = 0.45;//晴天概率
	int phype = 0.45;//高温概率
	int psand = 0.1;//沙尘暴概率
	
protected:

public:
	void init();
	void get_R();//计算基础奖励
	void get_Q(int weather[],PROBLEM set4);//学习：综合局部收益和经验值
	int judge_state(int weather,PROBLEM set4,int i,int j);//用于决策树搜索，计算后续决策的收益
};