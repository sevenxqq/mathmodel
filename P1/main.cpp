#include "Problem.h"




class TEST
{
public:
	TEST();
	~TEST();
	void test_consgraph_getdis(PROBLEM set) {
		int size = set.map.size();
		for (int i = 1; i < size; i++) {
			/*cout << endl << "点编号: " << i << "    点类型: " << set.map[i].state << "	邻居节点: ";
			for (auto j : set.map[i].neibors)
				cout << j << " ";*/
			cout << i << "距离终点:" << set.map[i].dis << endl;
		}
	}
	/*void test_dpmap(PROBLEM set) {
		for (int i = 1; i < MAX_STEP; i++) {
			for (int j = 1; j < MAX_SPOT; j++) {
				cout << dpmap[i][j] << "  ";
			}
			cout << endl;
		}
	}*/
private:

};

TEST::TEST()
{
}

TEST::~TEST()
{
}

int main() {

	 //第一题的main////////////////////////////////////////////
	PROBLEM set1("SET2.txt");
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


	int set_ans = set1.set1_dp(set1_weather, 64);
	/*cout << "i begin to test path 29 " << endl;
	set1.check_path(29, 27);*/
	cout << set_ans << endl;
	 ////////////////////////////////////////////////////////////

	//第二题的main/////////////////////////////////////////////
	PROBLEM set4("SET4_6.txt");
	Sol2 sol4;
	int set4_weather[35];
	sol4.get_R();
	sol4.get_Q(set4_weather, set4);

	// */ ////////////////////////////
	system("pause");
	return 0;

	


}

