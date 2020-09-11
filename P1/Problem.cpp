#include "Problem.h"
#include <queue>

Resource sunny(0, 5, 7);
Resource hype(0, 8, 6);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);

void PROBLEM::construct_table() {
	graph blank;
	map.push_back(blank);//�ص��1��ʼ���,������pushһ���յ�0

	ifstream infile1(filename);
	string line;//���ݸ�ʽ�� ����  ��״̬	�ھӽڵ�
	//���ж�ȡ
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
	memset(visited, false, sizeof(visited));//�������Բ���
	visited[0] = true;
	queue<int> que;
	que.push(size - 1);//check:size-1���յ�����
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


