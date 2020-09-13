#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/* 
	+------------������������--------------+

*/

const int MAX_STEP = 30;//����������
const int MAX_SPOT = 65; //��ͼ�����ĵص���
const int MAXCOST = 2000;
const int waterpri = 5;
const int foodpri = 10;
const int watersz = 3;
const int foodsz = 2;
const int MAXPAC = 1200;
const int MYMONEY = 10000;

enum {
	//��������
	ORD = 0,//��ͨ�ص�
	SRC = 1,//���
	MINE = 2,//��ɽ
	VIL=3,//��ׯ
	DST = 4,//�յ�
	//��������
	SUNNY=0,HYPE=1,SAND=2,
};


struct graph {
	int state = 0;//��Ǳ���
	int dis = 0;//�õ�����յ�����·������->���������֦
	vector<int> neibors;//�ھӵص�

};

struct Resource;

struct Resource {
	int money = 0;
	int water = 0;
	int food = 0;
	Resource() {}
	Resource(int x, int y, int z) : money(x), water(y), food(z) {}
	Resource(const Resource &tmp) : money(tmp.money), water(tmp.water), food(tmp.food) {}
	//���ز�����
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
		vector<graph>().swap(map);//�ͷ�vector�ڴ�ռ�
	}
	friend class TEST;
	friend class Sol2;
    vector <Resource> resource;
	void construct_table();
	void bfs_getDis();//���������㵽�յ����̾���
	int set1_dp(int weather[],int dest);
	void init();
	int getres_set1();
	void check_path(int day,int dest);
	int check_vil(int reachday, int dest);

};

class Sol2 {
	
private:
	//int R[30];//��¼ÿ����ķ�ֵ
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