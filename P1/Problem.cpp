#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);

int supply[4];//水量，食物量，增加的容量，花费的钱币
Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2];
int Path[MAX_STEP+2][MAX_SPOT+2];
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
		in >> from >> state;
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
	delete[]visited;

}

/*
	考虑最小消耗量,初始化为极大
*/
void PROBLEM::init(Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2]) {
	Resource initres(0, MAXCOST, MAXCOST);
	for (int i = 0; i <= MAX_STEP; i++) {
		for (int j = 0; j <= MAX_SPOT; j++) {
			dpmap[i][j] = initres;
			Path[i][j] = 0;
		}
	}
	dpmap[0][1].food = 0; dpmap[0][1].water = 0; dpmap[0][1].money = 0;
}

/*
	返回花销少的，已考虑赚的钱
*/
bool mincmp(Resource a, Resource b,Resource & c) {
	int money1 = a.water * waterpri + a.food *foodpri - a.money;
	int money2 = b.water * waterpri + b.food *foodpri - b.money;
	if (money1 <= money2) {
		c = a;
		return true;
	}
	c = b;
	return false;
}

/*
	第一题，动态规划(优化：带剪枝
*/

int PROBLEM::set1_dp(int weather[], int dest) {

	init(dpmap);
	
	memset(supply, 0, sizeof(supply));
	bool haschange = true;
	while (haschange) {
		haschange = false;
		for (int i = 1; i <= MAX_STEP; i++) {//第i步
			for (int j = 2; j < map.size(); j++) {//某个点

				for (auto neibor : map[j].neibors) {//它的邻居节点
					//TODO:计算i-30天有几天沙尘暴
					if (i + map[j].dis > MAX_STEP)//剪枝，在当前节点必须预留足够的时间到终点
						break;
					if (neibor != dest) {//到终点游戏结束，考虑特例，起点....---终点-矿山
						//行走，从邻居节点走过来
						if (weather[i] != SAND) {
							Resource newres1 = dpmap[i - 1][neibor] + resource[weather[i]] * 2;
							if (newres1.water*watersz + newres1.food*foodsz < MAXPAC + supply[2]) {//保证背包装的下
								if (mincmp(dpmap[i][j], newres1, dpmap[i][j]) == false) {
									haschange = true;
									Path[i][j] = neibor;
								}
							}
						}
						//cout << 123 << endl;

						//停留,分为停留下来挖矿，主动停留（在普通地点，或者在矿山但是不挖矿），以及沙尘暴被动停留,后面的可以合并
						if (map[j].state == MINE && dpmap[i - 1][j].food < MAXCOST) {
							Resource newres1 = dpmap[i - 1][j] + resource[weather[i]] * 3 + digmine;//停留此地挖矿
							if (newres1.water*watersz + newres1.food*foodsz < MAXPAC + supply[2]) {//保证背包装的下
								if (mincmp(dpmap[i][j], newres1, dpmap[i][j]) == false) {
									haschange = true;
									Path[i][j] = j;
								}
							}
						}
						Resource newres2 = dpmap[i - 1][j] + resource[weather[i]];//无挖矿的停留
						if (newres2.water*watersz + newres2.food*foodsz < MAXPAC + supply[2]) {//保证背包装的下
							if (mincmp(dpmap[i][j], newres2, dpmap[i][j]) == false) {
								haschange = true;
								Path[i][j] = j;
							}
						}
						//cout << 134 << endl;
						//村庄补给
						if (map[j].state == VIL) {
							int newpri = 2 * (waterpri * supply[0] + foodpri * supply[1]);
							if (supply[0] == 0 || newpri < supply[3]) {//第一次经过村庄;否则挑选花费少的
								supply[0] = dpmap[i][j].water; supply[1] = dpmap[i][j].food;
								supply[2] = watersz * supply[0] + supply[1] * foodsz;
								supply[3] = newpri;
							}
						}
					}
				}

				/*cout << "j=" << j << endl;*/
			}
			//cout <<"i="<< i << endl;

		}

	}
	//运行完后计算
	return getres_set1(dpmap);
}


int PROBLEM::getres_set1(Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2]) {
	int dest = map.size() - 1;
	Resource mincost(0,MAXCOST, MAXCOST);
	int reachday = 0;
	for (int i = 1; i <= MAX_STEP; i++) {
		mincmp(mincost, dpmap[i][dest],mincost);
		if (mincost == dpmap[i][dest])
			reachday = i;
	}
	if (mincost.water*watersz + mincost.food*foodsz < MAXPAC + supply[2]) {//保证背包装的下
		check_path(reachday, map.size() - 1);
		cout << "花费水，食物，赚到的钱" << mincost.water << "   " << mincost.food << "  " << mincost.money << endl;
		if (mincost.water*watersz + mincost.food*foodsz < MAXPAC) {//不用村庄补给就能装下
			int cost = mincost.water*waterpri + mincost.food*foodpri - mincost.money;
			return MYMONEY - cost;
		}
		else {
			//优先在起点购买食物
			int foodnum = (MAXPAC > foodsz * mincost.food)? mincost.food : (MAXPAC / 2);//在起点能购买的食物的数目
			int waternum = (MAXPAC > (foodnum * 2) ? (MAXPAC - foodnum *2) : 0) / 3;//在起点能购买的水的数目
			int buycost = foodnum * foodpri + waternum * waterpri +
				(mincost.food > foodnum) ? ((mincost.food - foodnum) * 2 * foodpri) : 0	
				+ (mincost.water > waternum) ? ((mincost.water - waternum) * 2 * waterpri) : 0; //多出的部分在村庄按两倍价格购买；

			return MYMONEY - buycost + mincost.money;

		}
	
	}
	return -1;//表示不能到达
}

void PROBLEM::check_path(int reachday,int dest) {
	cout << "路径（倒序): " << dest << " ";
	while (reachday > 0) {
		cout << Path[reachday][dest] << " ";	
		dest = Path[reachday][dest];
		reachday--;
	}
	cout << endl;
}