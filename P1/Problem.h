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
	ORD = 0,//��ͨ�ص�
	SRC = 1,//���
	MINE = 2,//��ɽ
	VIL=3,//��ׯ
	DST = 4,//�յ�
};


struct graph {
	int state = 0;//��Ǳ���
	int dis = 0;//�õ�����յ�����·������->���������֦
	vector<int> neibors;//�ھӵص�

};



struct Resource {
	int money = 0;
	int water = 0;
	int food = 0;
	Resource() {}
	Resource(int x, int y, int z) : money(x), water(y), food(z) {}
	//���ز�����
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



const int MAX_STEP = 30;//����������
const int MAX_SPOT = 50; //��ͼ�����ĵص���




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
	void construct_table();
	void bfs_getDis();//���������㵽�յ����̾���



};

