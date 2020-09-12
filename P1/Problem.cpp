#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);

int supply[4];//ˮ����ʳ���������ӵ����������ѵ�Ǯ��
Resource dpmap[MAX_STEP + 2][MAX_SPOT + 2];
int Path[MAX_STEP + 2][MAX_SPOT + 2];
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
void PROBLEM::init() {
	Resource initres(0, MAXCOST, MAXCOST);
	for (int i = 0; i <= MAX_STEP; i++) {
		for (int j = 0; j <= MAX_SPOT; j++) {
			dpmap[i][j] = initres;
			Path[i][j] = 0;
			if (i == 0 && j == 1)
				dpmap[0][1].food = 0; dpmap[0][1].water = 0; dpmap[0][1].money = 0;
		}
		}
		
	}
	

/*
	���ػ����ٵģ��ѿ���׬��Ǯ
*/
bool mincmp(Resource a, Resource b) {
	int money1 = a.water * waterpri + a.food *foodpri - a.money;
	int money2 = b.water * waterpri + b.food *foodpri - b.money;
	if (money1 <= money2) {
		return true;
	}
	return false;
}

/*
	��һ�⣬��̬�滮(�Ż�������֦
*/

int PROBLEM::set1_dp(int weather[], int dest) {

	init();

	memset(supply, 0, sizeof(supply));
	bool haschange = true;
	while (haschange) {
		haschange = false;
		for (int i = 1; i <= MAX_STEP; i++) {//��i��
			for (int j = 1; j < dest; j++) {//ĳ����


				if (dpmap[i - 1][j].food < MAXCOST) {//�ж��Ƿ��ǵ���j��
					for (auto neibor : map[j].neibors) {//�ߵ���һ���ھӽڵ�
						//TODO:����i-30���м���ɳ����
						//if (i + map[neibor].dis > MAX_STEP)//��֦���ڵ�ǰ�ڵ����Ԥ���㹻��ʱ�䵽�յ�
						//	break;
						if (j != dest && weather[i] != SAND) {//���յ���Ϸ����
							Resource newres1 = dpmap[i - 1][j] + resource[weather[i]] * 2;
							if (((newres1.water*watersz + newres1.food*foodsz) < (MAXPAC + check_vil(i, neibor) * supply[2]))
								&& ((newres1.water*waterpri + newres1.food*foodpri) < (MYMONEY + check_vil(i, neibor) * supply[3]))) {//��֤����װ����,ǮҲ���ܳ���
								if (mincmp(dpmap[i][neibor], newres1) == false) {
									dpmap[i][neibor] = newres1;
									haschange = true;
									Path[i][neibor] = j;
									/*if (neibor == 27)
										cout << "��"<< i<<" ��"<<  "i reach dest from" << j << endl;*/
										//����߹�����һ����ׯ������װ������
									if (map[neibor].state == VIL) {
										int newpri = 2 * (waterpri * dpmap[i][neibor].water + foodpri * dpmap[i][neibor].food);
										supply[0] = dpmap[i][neibor].water; supply[1] = dpmap[i][neibor].food;
										supply[2] = supply[0] * watersz + supply[1] * foodsz;
										supply[3] = dpmap[i][neibor].money;

									}
								}
							}
							

						}
					}

					//����״̬ת��
					//ԭ��ͣ����������Ϊ
					if (j != dest && j != MINE ) {//��ȥ��ɽ��û�б�Ҫ����ͣ��,����ֻҪ����ɳ�����޷��߶�
						Resource newres2 = dpmap[i - 1][j] + resource[weather[i]];
						int newsize = newres2.water*watersz + newres2.food*foodsz;
						int newpri = newres2.water*waterpri + newres2.food*foodpri;
						int pass_vli = check_vil(i, j);
							if (    ( newsize < (MAXPAC +  pass_vli* supply[2]) )
								&& ( newpri < (MYMONEY + pass_vli * supply[3]) )     ) {//��֤����װ����,ǮҲ���ܳ���
								if (mincmp(dpmap[i][j], newres2) == false) {
									dpmap[i][j] = newres2;
									haschange = true;
									Path[i][j] = j;
									if (map[j].state == VIL) {
										supply[0] = dpmap[i][j].water; supply[1] = dpmap[i][j].food;
													supply[2] = supply[0] * watersz + supply[1] * foodsz;
												supply[3] = dpmap[i][j].money;
									}
								}
							}
						
					}

					//������ڿ�ɽ�ж��Ƿ��ڿ�
					if (map[j].state == MINE && dpmap[i - 1][j].food < MAXCOST) {
						Resource newres1 = dpmap[i - 1][j] + resource[weather[i]] * 3 + digmine;
						if (((newres1.water*watersz + newres1.food*foodsz) < (MAXPAC + supply[2] * check_vil(i, j)))
							&& ((newres1.water*waterpri + newres1.food*foodpri)) < (MYMONEY + check_vil(i, j) * supply[3])) {//��֤����װ����,ǮҲ���ܳ���
							if (mincmp(dpmap[i][j], newres1) == false) {
								dpmap[i][j] = newres1;
								cout << "��ɽ���" << j << "��һ�����ѵ�ʳ��" << dpmap[i - 1][j].food << " ";
								cout << i << "I have dig mine" << endl;
								haschange = true;
								Path[i][j] = j;
							}
						}
					}


					//cout <<"i="<< i << endl;
				}



			
			}
		}
	}



	///////
	cout << "supply" << supply[0] << "   " << supply[1] << "   " << supply[2] << "   " << supply[3] << endl;
	//����������

	//for (int i = 1; i <= MAX_STEP; i++) {//��i��
	//	for (int j = 1; j < map.size(); j++) {//ĳ����
	//	
	//		cout << i << "  " << dpmap[i][j].food << "  " << dpmap[i][j].water << "  " << dpmap[i][j].money << endl;
	//	}
	//}
	return getres_set1();
	////////
}


int PROBLEM::getres_set1() {
	int dest = map.size() - 1;
	Resource mincost(0, MAXCOST, MAXCOST);
	int reachday = 0;
	for (int i = 1; i <= MAX_STEP; i++) {
		if (mincmp(mincost, dpmap[i][dest]) == false) {
			reachday = i;
			mincost = dpmap[i][dest];
		}
		cout << i<< "  " << dpmap[i][dest].food <<"  "<<  dpmap[i][dest].water <<"  "<<  dpmap[i][dest].money << endl;
		
	}
	if (mincost.water*watersz + mincost.food*foodsz < MAXPAC + check_vil(reachday,dest) * supply[2]) {//��֤����װ����
		check_path(reachday, map.size() - 1);
		cout << "����ˮ��ʳ�׬����Ǯ" << mincost.water << "   " << mincost.food << "  " << mincost.money << endl;
		if (mincost.water*watersz + mincost.food*foodsz < MAXPAC) {//���ô�ׯ��������װ��
			int cost = mincost.water*waterpri + mincost.food*foodpri - mincost.money;
			cout << "cost" << cost << endl;
			return MYMONEY - cost;
		}
		else {
			//��������㹺��ʳ��
			int foodnum = (MAXPAC > foodsz * mincost.food) ? mincost.food : (MAXPAC / 2);//������ܹ����ʳ�����Ŀ
			cout << "foodnum=" << foodnum << endl;
			int waternum = (MAXPAC > (foodnum * 2) ? (MAXPAC - foodnum * 2) : 0) / 3;//������ܹ����ˮ����Ŀ
			cout << "waternum=" << waternum << endl;
			int buycost = foodnum * foodpri + waternum * waterpri +
				((mincost.food > foodnum) ? ((mincost.food - foodnum) * 2 * foodpri) : 0)
				+ ((mincost.water > waternum) ? ((mincost.water - waternum) * 2 * waterpri) : 0); //����Ĳ����ڴ�ׯ�������۸���
			cout << "buycost" << buycost << endl;
			return MYMONEY - buycost + mincost.money;

		}

	}
	return -1;//��ʾ���ܵ���
}

void PROBLEM::check_path(int reachday, int dest) {
	cout << "·��������): " << dest << " "<<endl;
	while (reachday > 0) {
		cout << Path[reachday][dest] << " :";
		cout << dpmap[reachday][dest].food << "  " << endl;
		dest = Path[reachday][dest];
		reachday--;
	}
	cout << endl;
}

int PROBLEM::check_vil(int reachday, int dest) {//dest�ǵ���

	while (reachday > 0) {
		if (map[dest].state == VIL)
			return 1;
		dest = Path[reachday][dest];
		reachday--;
	}
	return 0;
}