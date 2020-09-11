#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/* 
	+------------������������--------------+

*/

enum {
	//��������
	ORD = 0,//��ͨ�ص�
	SRC = 1,//���
	MINE = 2,//��ɽ
	VIL=3,//��ׯ
	DST = 4,//�յ�
	//��������
	sun=0,hypet=1,sand=2,
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
	

};



const int MAX_STEP = 30;//����������
const int MAX_SPOT = 50; //��ͼ�����ĵص���
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
		vector<graph>().swap(map);//�ͷ�vector�ڴ�ռ�
	}
	friend class TEST;
	static  vector <Resource> resource;
	void construct_table();
	void bfs_getDis();//���������㵽�յ����̾���
	void set1_dp(int weather[],int dest);
	void init(Resource dpmap[MAX_STEP+2][MAX_SPOT+2]);


};

