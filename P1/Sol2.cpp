#include "Problem.h"

Resource sunny(0, 3, 4);
Resource hype(0, 9, 9);
Resource sandstorm(0, 10, 10);
Resource digmine(1000, 0, 0);
Resource walk_val;
Resource stay_val;
Resource stay_mine;

int basic_score[] = { -minscore,	-2000, 2 ,3,-2000,5, 6,-2000,4, 4, //minscore is an impl
								    -2000,1,2,2000,4,5,2000 ,3,3,
									-2000,1 ,2,2000,4,5 ,2000,3,3 };
int R[30][30][30];

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
		for (int j = 1; j <= 27; j++) {
			if (j <= 9)
				p2 = psunny;
			else if (j <= 18)
				p2 = phype;
			else
				p2 = psand;
			for (int k = 1; k <= 27; k++) {
				if (k <= 9)
					p3 = psunny;
				else if (k <= 18)
					p3 = phype;
				else
					p3 = psand;
				R[i][j][k] = basic_score[i] + p2 * basic_score[j] + p2 * p3 *basic_score[k];
			}
		}
	}



	//图中节点1,2,3,5,6,7,11,21属于同一类节点，三个深度均为普通节点
	/*int temp[] = { 1,2,3,5,6,7,11,21 };
	Resource ord3_val = walk_val;*/


	
}


