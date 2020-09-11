#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);


/*
	从文件中读入并建图
	attention; 不含dis
*/
void PROBLEM::construct_table() {
	resource.push_back(sunny);
	resource.push_back(hype);
	resource.push_back(sandstorm);

	graph blank;
	map.push_back(blank);//地点从1开始标记,所以先push一个空的0

	ifstream infile1(filename);
	string line;//数据格式： 点编号  点状态	邻居节点
	//按行读取
	while (getline(infile1, line)) {
		istringstream in(line);
		graph temp;

		int from = 0, state = 0, to = 0;
		in >> from >> state ;
		temp.state = state;

		while (in >> to) {
			temp.neibors.push_back(to);
		}
		map.push_back(temp);

	}
	infile1.close();

}

/*
	计算每个点到终点的最短距离
*/
void PROBLEM::bfs_getDis() {
	int size = map.size();
	bool *visited = new bool[size];
	for (int i = 0; i < size; i++)
		visited[i] = false;
	visited[0] = true;
	queue<int> que;
	int destnum = size - 1;
	que.push(destnum);//check:size-1是终点编号吗
	map[destnum].dis = 0;
	while (!que.empty())
	{
		int from = que.front();
		visited[from] = true;
		que.pop();
		for (int i = 0; i < map[from].neibors.size(); i++) {
			int neibor = map[from].neibors[i];
			if (visited[neibor] == false) {
				map[neibor].dis = map[from].dis + 1;
				que.push(neibor);
				visited[neibor] = true;
			}

		}
	}
	delete []visited;

}

/*
	考虑最小消耗量,初始化为极大
*/
void PROBLEM::init(Resource dpmap[MAX_STEP+2][MAX_SPOT+2]) {
	Resource initres(0, MAXCOST, MAXCOST);
	for (int i = 0; i <= MAX_STEP; i++) {
		for (int j = 0; j <= MAX_SPOT; j++) {
			dpmap[i][j] = initres;
		}
	}
}

/* 
	返回花销少的，已考虑赚的钱
*/
Resource mincmp(Resource a, Resource b) {
	int money1 = a.water * waterpri + a.food *foodpri - a.money;
	int money2 = b.water * waterpri + b.food *foodpri - b.money;
	if (money1 < money2)
		return a;
	return b;
}

/*
	第一题，动态规划(优化：带剪枝
*/

void PROBLEM::set1_dp(int weather[],int dest) {
	Resource dpmap[MAX_STEP+2][MAX_SPOT+2];
	init(dpmap);
	for (int i = 1; i <= MAX_STEP; i++) {//第i步
		for (int j = 0; j < map.size(); j++) {//某个点

			for (auto neibor : map[i].neibors) {//它的邻居节点
				if (i + map[j].dis > MAX_STEP)//剪枝，在当前节点必须预留足够的时间到终点
					break;
				if (neibor != dest) {//到终点游戏结束，考虑特例，起点....---终点-矿山
					//行走，从邻居节点走过来
					if (weather[i] != SAND) {
						Resource newres1 = dpmap[i - 1][neibor] + resource[weather[i]] * 2;
						dpmap[i][j] = mincmp(dpmap[i][j], newres1);
					}

					//村庄补给

					//停留,分为停留下来挖矿，主动停留（在普通地点，或者在矿山但是不挖矿），以及沙尘暴被动停留,后面的可以合并
					if (map[j].state == MINE) {
						Resource newres1 = dpmap[i - 1][j] + resource[weather[i]] * 3 + digmine;//停留此地挖矿
						dpmap[i][j] = mincmp(dpmap[i][j], newres1);
					}
					Resource newres2 = dpmap[i - 1][j] + resource[weather[i]];//无挖矿的停留
					dpmap[i][j] = mincmp(dpmap[i][j], newres2);
				}
			}
		}
	}

}


