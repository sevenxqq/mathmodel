#include "Problem.h"






class TEST
{
public:
	TEST();
	~TEST();
	void test_consgraph_getdis(PROBLEM set) {
		int size = set.map.size();
		for (int i = 1; i < size; i++) {
			/*cout << endl << "����: " << i << "    ������: " << set.map[i].state << "	�ھӽڵ�: ";
			for (auto j : set.map[i].neibors)
				cout << j << " ";*/
			cout << i << "�����յ�:" << set.map[i].dis << endl;
		}
	}
private:

};

TEST::TEST()
{
}

TEST::~TEST()
{
}

int main() {

	//��һ���main

	PROBLEM set1("SET1.txt");
	set1.construct_table();
	set1.bfs_getDis();
	/*TEST smalltest;
	smalltest.test_consgraph_getdis(set1);*/
	int set1_weather[35] = { 0,	HYPE,HYPE,SUNNY, SAND,SUNNY,HYPE, //0 is a blank impl
								SAND,SUNNY,HYPE, HYPE,SAND,HYPE,
								SUNNY,HYPE,HYPE,HYPE,SAND,SAND,
								HYPE,HYPE,SUNNY,SUNNY,HYPE,SUNNY,
								SAND,HYPE,SUNNY,SUNNY,HYPE,HYPE
	};
	
	
	int set_ans = set1.set1_dp(set1_weather, 27);
	cout << set_ans << endl;


	// */

	system("pause");
	return 0;
}