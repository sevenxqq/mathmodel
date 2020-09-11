#include "Problem.h"






class TEST
{
public:
	TEST();
	~TEST();
	void test_consgraph(PROBLEM set) {
		int size = set.map.size();
		for (int i = 1; i < size; i++) {
			cout << endl << "点编号: " << i << "    点类型: " << set.map[i].state << "	邻居节点: ";
			for (auto j : set.map[i].neibors)
				cout << j << " ";
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

	PROBLEM set1("SET1.txt");
	set1.construct_table();
	TEST smalltest;
	smalltest.test_consgraph(set1);
	system("pause");
	return 0;
}