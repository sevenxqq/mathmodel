#include "Problem.h"
#include <stdlib.h>
#include <time.h> 



Resource sunny(0, 3, 4);
Resource hype(0, 9, 9);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);
Resource walk_val;
Resource stay_val;
Resource stay_mine;
const double PGREEDY = 0.6;
const double QLEARN = 0.4;

int basic_score[] = { 0,	-2000, 2 ,3,-2000,5, 6,-2000,4, 4, //0 is an impl
								    -2000,1,2,2000,4,5,2000 ,3,3,
									-2000,1 ,2,2000,4,5 ,2000,3,3 };
int R[30][30][30];//对于set4,实际是27^3=19683种状态
double Q[MAX_STEP+2][MAX_SPOT+2];//记录第i天j地的分值

int dpscore[MAX_STEP + 2][MAX_SPOT + 2];
int Path[MAX_STEP + 2][MAX_SPOT + 2];
const int minscore = -10000;
const int ori3_psum = 1;


void Sol2::init() {
	Resource walk_val = sunny * 2 * psunny + hype * 2 * phype;
	Resource stay_val = sandstorm * psand;
	Resource stay_mine = sunny * 3 * psunny + hype * 3 * phype + sandstorm * 3 * psand + digmine;

}

void Sol2::get_R() {
	// 单层有27种状态，深度为3总的为27^3；
	int p1 = 0, p2 = 0, p3 = 0;
	for (int i = 1; i <= 27; i++) {
		if (i <= 9)
			p1 = psunny;
		else if (i <= 18)
			p1 = phype;
		else
			p1 = psand;
		//在随机生成weather数组后，可以确定天气，p1=1;
		p1 = 1;
		for (int j = 0; j <= 27; j++) {
			if (j <= 9)
				p2 = psunny;
			else if (j <= 18)
				p2 = phype;
			else
				p2 = psand;
			for (int k = 0; k <= 27; k++) {
				if (k <= 9)
					p3 = psunny;
				else if (k <= 18)
					p3 = phype;
				else
					p3 = psand;
				R[i][j][k] = p1 * basic_score[i] + p1 * p2 * basic_score[j] + p1 * p2 * p3 *basic_score[k];
			}
		}
	}



	//图中节点1,2,3,5,6,7,11,21属于同一类节点，三个深度均为普通节点
	/*int temp[] = { 1,2,3,5,6,7,11,21 };
	Resource ord3_val = walk_val;*/


	
}

int Sol2::judge_state(int weather,PROBLEM set4,int i,int j) {
	if (i > MAX_STEP)//没有这步
		return 0;
	if (weather == SUNNY) {
		//2：判断地点类型
		if (set4.map[j].state == ORD) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 1
				return 1;
			}
			else if (rate < 2) {//line 2
				return 2;
			}
			else {//line 3
				return 3;
			}

		}
		else if (set4.map[j].state == VIL) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 4;
			}
			else if (rate < 2) {//line 
				return 5;
			}
			else {//line 
				return 6;
			}

		}
		else if (set4.map[j].state == MINE) {
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 7;
			}
			else if (rate < 2) {//line 
				return 8;
			}
			else {//line 
				return 9;
			}
		}

	}

	else if (weather == HYPE) {
		//2：判断地点类型
		if (set4.map[j].state == ORD) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 1
				return 10;
			}
			else if (rate < 2) {//line 2
				return 11;
			}
			else {//line 3
				return 12;
			}

		}
		else if (set4.map[j].state == VIL) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 13;
			}
			else if (rate < 2) {//line 
				return 14;
			}
			else {//line 
				return 15;
			}

		}
		else if (set4.map[j].state == MINE) {
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 16;
			}
			else if (rate < 2) {//line 
				return 17;
			}
			else {//line 
				return 18;
			}
		}
	}
	else if (weather == SAND) {
		//2：判断地点类型
		if (set4.map[j].state == ORD) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 1
				return 19;
			}
			else if (rate < 2) {//line 2
				return 20;
			}
			else {//line 3
				return 21;
			}

		}
		else if (set4.map[j].state == VIL) {
			//3:判断背包充裕程度
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 22;
			}
			else if (rate < 2) {//line 
				return 23;
			}
			else {//line 
				return 24;
			}

		}
		else if (set4.map[j].state == MINE) {
			double rate = (MAXPAC - set4.dpmap[i][j].food * foodsz - set4.dpmap[i][j].water *waterpri)
				/ (set4.map[j].dis *(sunny.food *foodsz + sunny.water*watersz));
			if (rate < 1) { //line 
				return 25;
			}
			else if (rate < 2) {//line 
				return 26;
			}
			else {//line 
				return 27;
			}
		}
	}
}

void Sol2::get_Q(int weather[],PROBLEM set4) {
	srand((unsigned)time(NULL));
	//	TODO 随机生成weather
	//attention:注意修改PROBLEM.cpp中地点，资源消耗等相关参数；
	//tip:在头文件定义中修改psunny等参数可以调整天气的概率
	int studycircle = 1;//调整学习的次数
	while (studycircle > 0) {
		for (int i = 0; i < 35; i++) {
			double randnum = rand() / double(RAND_MAX);
			int random = 0;
			if (randnum < psunny)
				random = 0;
			else if (randnum < psunny + phype)
				random = 1;
			else
				random = 2;
			//int random = rand() % 3;
			weather[i] = random;
		}

		set4.construct_table();
		bool has_change = true;
		while (has_change)//未收敛
		{
			for (int i = 1; i <= MAX_STEP; i++) {//第i天
				for (int j = 1; j <= MAX_SPOT; j++) {
					int state1 = judge_state(weather[i], set4, i, j);
					for (auto neibor1 : set4.map[j].neibors) {
						int state2 = 0;
						if (i + 1 <= MAX_STEP) {
							int state2 = judge_state(weather[i + 1], set4, i + 1, neibor1);
							for (auto neibor2 : set4.map[neibor1].neibors) {
								int state3 = 0;
								if (i + 2 <= MAX_STEP)
									int state3 = judge_state(weather[i + 2], set4, i + 2, neibor2);
								Q[i][j] = (1 - PGREEDY)* Q[i][j] + PGREEDY * (R[1][1][1] + QLEARN * Q[i][j]);

							}
						}
					}
				}
			}
		}

		studycircle--;
	}

}