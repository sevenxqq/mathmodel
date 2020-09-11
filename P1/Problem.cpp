#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);



void PROBLEM::construct_table() {
	resource.push_back(sunny);
	resource.push_back(hype);
	resource.push_back(sandstorm);
	resource.push_back(digmine);

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

void PROBLEM::bfs_getDis() {
	int size = map.size();
	bool *visited = new bool(size);
	memset(visited, false, sizeof(visited));//检查这里对不对
	visited[0] = true;
	queue<int> que;
	que.push(size - 1);//check:size-1是终点编号吗
	int curdis = -1;
	while (!que.empty())
	{
		int from = que.front();
		visited[from] = true;
		que.pop();
		curdis++;
		map[from].dis = curdis;
		for (int i = 0; i < map[from].neibors.size(); i++) {
			int neibor = map[from].neibors[i];
			if (visited[neibor] == false) {
				que.push(neibor);
				visited[neibor] = true;
			}

		}
	}


}


void PROBLEM::init(Resource dpmap[MAX_STEP+2][MAX_SPOT+3]) {
	Resource initres(0, MAXCOST, MAXCOST);
	for (int i = 0; i <= MAX_STEP; i++) {
		for (int j = 0; j <= MAX_SPOT; j++) {
			dpmap[i][j] = initres;
		}
	}
}



void PROBLEM::set1_dp(int weather[]) {
	Resource dpmap[MAX_STEP][MAX_SPOT];//考虑最小消耗量,初始化为极大

	for (int i = 1; i <= MAX_STEP; i++) {//第i步
		for (int j = 0; j < map.size(); j++) {

			for (auto neibor : map[i].neibors) {
				//从邻居节点走过来
				if (weather[i]!=sand)
					Resource newres1 = dpmap[i - 1][neibor] + 2 * resource[weather[i]];
				//挖矿

				//村庄

				//停留
				Resource newres1 = dpmap[i - 1][j] + resource[weather[i]];//这里是拷贝？？？
				
			}
		}
	}

}


