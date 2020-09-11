#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);

int supply[4];//ˮ����ʳ���������ӵ����������ѵ�Ǯ��
Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2];
int Path[MAX_STEP+2][MAX_SPOT+2];
/*
	���ļ��ж��벢��ͼ
	attention; ����dis
*/
void PROBLEM::construct_table() {
	resource.push_back(sunny);
	resource.push_back(hype);
	resource.push_back(sandstorm);

	graph blank;
	map.push_back(blank);//�ص��1��ʼ���,������pushһ���յ�0

	ifstream infile1(filename);
	string line;//���ݸ�ʽ�� ����  ��״̬	�ھӽڵ�
	//���ж�ȡ
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
	����ÿ���㵽�յ����̾���
*/
void PROBLEM::bfs_getDis() {
	int size = map.size();
	bool *visited = new bool[size];
	for (int i = 0; i < size; i++)
		visited[i] = false;
	visited[0] = true;
	queue<int> que;
	int destnum = size - 1;
	que.push(destnum);//check:size-1���յ�����
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
	������С������,��ʼ��Ϊ����
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
	���ػ����ٵģ��ѿ���׬��Ǯ
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
	��һ�⣬��̬�滮(�Ż�������֦
*/

int PROBLEM::set1_dp(int weather[], int dest) {

	init(dpmap);
	
	memset(supply, 0, sizeof(supply));
	bool haschange = true;
	while (haschange) {
		haschange = false;
		for (int i = 1; i <= MAX_STEP; i++) {//��i��
			for (int j = 2; j < map.size(); j++) {//ĳ����

				for (auto neibor : map[j].neibors) {//�����ھӽڵ�
					//TODO:����i-30���м���ɳ����
					if (i + map[j].dis > MAX_STEP)//��֦���ڵ�ǰ�ڵ����Ԥ���㹻��ʱ�䵽�յ�
						break;
					if (neibor != dest) {//���յ���Ϸ�������������������....---�յ�-��ɽ
						//���ߣ����ھӽڵ��߹���
						if (weather[i] != SAND) {
							Resource newres1 = dpmap[i - 1][neibor] + resource[weather[i]] * 2;
							if (newres1.water*watersz + newres1.food*foodsz < MAXPAC + supply[2]) {//��֤����װ����
								if (mincmp(dpmap[i][j], newres1, dpmap[i][j]) == false) {
									haschange = true;
									Path[i][j] = neibor;
								}
							}
						}
						//cout << 123 << endl;

						//ͣ��,��Ϊͣ�������ڿ�����ͣ��������ͨ�ص㣬�����ڿ�ɽ���ǲ��ڿ󣩣��Լ�ɳ��������ͣ��,����Ŀ��Ժϲ�
						if (map[j].state == MINE && dpmap[i - 1][j].food < MAXCOST) {
							Resource newres1 = dpmap[i - 1][j] + resource[weather[i]] * 3 + digmine;//ͣ���˵��ڿ�
							if (newres1.water*watersz + newres1.food*foodsz < MAXPAC + supply[2]) {//��֤����װ����
								if (mincmp(dpmap[i][j], newres1, dpmap[i][j]) == false) {
									haschange = true;
									Path[i][j] = j;
								}
							}
						}
						Resource newres2 = dpmap[i - 1][j] + resource[weather[i]];//���ڿ��ͣ��
						if (newres2.water*watersz + newres2.food*foodsz < MAXPAC + supply[2]) {//��֤����װ����
							if (mincmp(dpmap[i][j], newres2, dpmap[i][j]) == false) {
								haschange = true;
								Path[i][j] = j;
							}
						}
						//cout << 134 << endl;
						//��ׯ����
						if (map[j].state == VIL) {
							int newpri = 2 * (waterpri * supply[0] + foodpri * supply[1]);
							if (supply[0] == 0 || newpri < supply[3]) {//��һ�ξ�����ׯ;������ѡ�����ٵ�
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
	//����������
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
	if (mincost.water*watersz + mincost.food*foodsz < MAXPAC + supply[2]) {//��֤����װ����
		check_path(reachday, map.size() - 1);
		cout << "����ˮ��ʳ�׬����Ǯ" << mincost.water << "   " << mincost.food << "  " << mincost.money << endl;
		if (mincost.water*watersz + mincost.food*foodsz < MAXPAC) {//���ô�ׯ��������װ��
			int cost = mincost.water*waterpri + mincost.food*foodpri - mincost.money;
			return MYMONEY - cost;
		}
		else {
			//��������㹺��ʳ��
			int foodnum = (MAXPAC > foodsz * mincost.food)? mincost.food : (MAXPAC / 2);//������ܹ����ʳ�����Ŀ
			int waternum = (MAXPAC > (foodnum * 2) ? (MAXPAC - foodnum *2) : 0) / 3;//������ܹ����ˮ����Ŀ
			int buycost = foodnum * foodpri + waternum * waterpri +
				(mincost.food > foodnum) ? ((mincost.food - foodnum) * 2 * foodpri) : 0	
				+ (mincost.water > waternum) ? ((mincost.water - waternum) * 2 * waterpri) : 0; //����Ĳ����ڴ�ׯ�������۸���

			return MYMONEY - buycost + mincost.money;

		}
	
	}
	return -1;//��ʾ���ܵ���
}

void PROBLEM::check_path(int reachday,int dest) {
	cout << "·��������): " << dest << " ";
	while (reachday > 0) {
		cout << Path[reachday][dest] << " ";	
		dest = Path[reachday][dest];
		reachday--;
	}
	cout << endl;
}