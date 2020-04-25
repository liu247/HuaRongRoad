#include "pch.h"
#include "Search.h"

Search::Search() {
	/*利用malloc在堆内存中开辟内存空间,它的大小是元素的个数乘以该数据类型的长度*/ 
	/*hsb = (unsigned int*)malloc(hashSize * sizeof(unsigned int));
	hsb1 = (unsigned int*)malloc(hashSize * sizeof(unsigned int));
	hsb2 = (unsigned int*)malloc((hashSize / 4) * sizeof(unsigned int));
	st = (State*)malloc(maxState * sizeof(State));
	answer = (State*)malloc(maxheight * sizeof(State));
	cur = (int*)malloc(maxState * sizeof(int));
	dist = (int*)malloc(maxState * sizeof(int));*/

	hsb = new unsigned int[hashSize]();
	hsb1 = new unsigned int[hashSize]();
	hsb2 = new unsigned int[hashSize / 4]();
	st = new State [maxState]();
	answer = new State[maxheight]();
	cur = new int[maxState]();
	dist = new int[maxState]();
}

Search::~Search() {
	/*free(hsb);
	free(hsb1);
	free(hsb2);
	free(st);
	free(answer);
	free(cur);
	free(dist);*/
	delete[] hsb;
	delete[] hsb1;
	delete[] hsb2;
	delete[] st;
	delete[] answer;
	delete[] cur;
	delete[] dist;
}
void Search::init_lookup_table() {
	memset(hsb, 0, sizeof(hsb));
	memset(hsb1, 0, sizeof(hsb1));
	//memset(hsb2, 0, sizeof(hsb2));
}

int Search::try_to_insert(char* s) {
	int i;
	char q[20];
	switch (mark) {
	case 1:
		for (i = 0; i < 20; i++) {
			q[i] = U1[(s[i])];
		}
		break;
	case 2:
		for (i = 0; i < 20; i++) {
			q[i] = U2[(s[i])];
		}
		break;
	case 3:
		for (i = 0; i < 20; i++) {
			q[i] = U3[(s[i])];
		}
		break;
	case 4:
		for (i = 0; i < 20; i++) {
			q[i] = U1[(s[i])];
		}
		break;
	}
	unsigned n1, n2, m0, h, h1, h2, * p = (unsigned int*)q;
	n1 = (p[1] << 3) + (p[2] << 5) + p[0]; //每次折叠时都应充分发挥各子作用,增强散列
	n2 = (p[3] << 1) + (p[4] << 4);
	m0 = (n2 << 6) ^ (n1 << 3); //增强散列参数
	//第一哈希处理
	h1 = n1 + n2 + m0;
	h2 = n1 - n2 + m0;
	hs17(h1, h);//h1为散列和,h为第一哈希索引
	if (!hsb[h]) {
		hsb[h] = h1;  //h1为散列和,h为第一哈希索引
		return 1;
	}
	if (hsb[h] == h1) return 0;

	//第二哈希处理
	h1 = n1 - n2 + m0;
	hs15(h1, h);//h1为散列差,h为第二哈希
	if (!hsb1[h]) {
		hsb1[h] = h1;
		return 1;
	}
	if (hsb1[h] == h1) return 0;
}

void Search::insert_queue(char* newchess) {
	State& t = st[rear];
	memcpy(&t, newchess, sizeof(t));
	dist[rear] = dist[front] + 1;
	cur[rear] = front;
	if (try_to_insert(st[rear])) {
	//	check2(newchess);
		rear++;  //如果成功插入查找表，修改队尾指针
	}
}

void Search::check2(char* q) {
	int i;
	char q2[20];
	memcpy(q2, q, sizeof(q2));
	for (i = 0; i < 20; i += 4) q2[i] = q[i + 3], q2[i + 1] = q[i + 2], q2[i + 2] = q[i + 1], q2[i + 3] = q[i];
	try_to_insert(q2);
}

void Search::walk_1(char* chess, int BS_1) {
	char newChess[20];
	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;

	if (BS_1 - 4 >= 0 && BS_1 - 4 < 20 && chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 8) { //检查上方存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && ((chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 4) || chess[BS_1 - 1] == 9)) {//检查左方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && ((chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 4) || chess[BS_1 + 1] == 9)) { 		//检查右方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BS_1 + 4 >= 0 && BS_1 + 4 < 20 && chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 8) {		//检查下方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 8] = 0;
		}
		insert_queue(newChess);
	}
}

void Search::walk1_1(char* chess, int BS_1) {
	char newChess[20];
	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4) || chess[BS_1 - 4] == 9)) { //检查上方存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 8) {//检查左方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 8) { 		//检查右方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4) || chess[BS_1 + 4] == 9)) {		//检查下方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 8] = 0;
		}
		insert_queue(newChess);
	}
}

void Search::walk2_1(char* chess, int BS_1) {
	int i;
	char newChess[20];
	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4) || (chess[BS_1 - 4] >= 7 && chess[BS_1 - 4] <= 9))) { //检查上方存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 6) {//检查左方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 6) { 		//检查右方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4) || (chess[BS_1 + 4] >= 7 && chess[BS_1 + 4] <= 9))) {		//检查下方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //竖将移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 8] = 0;
		}
		insert_queue(newChess);
	}
}

void Search::walk3_1(char* chess, int BS_1) {
	int i;
	char newChess[20];
	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4))) { //检查上方存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 9) {//检查左方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 9) { 		//检查右方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //横将移动
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4))) {		//检查下方是否存在且是否可以移动
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //小兵移动
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		insert_queue(newChess);
	}
}
void Search::walk_2(char* chess, int BS_1, int BS_2) {
	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;
	int BSx_2 = BS_2 / 4;
	int BSy_2 = BS_2 % 4;  //获取空格的行列编号

	int newBSx_1, newBSy_1;
	int newBSx_2 = 0, newBSy_2 = 0;
	int  newBS_1, newBS_2;   //新空格位置

	char newChess[20];
	int i;

	/*
	将竖放的空格周围棋子移动，移动两格
	*/
	if (BS_2 - BS_1 == 4) { //竖放
		//第一个空格周围的小兵走两个格子，即第一个格子上，左，右
		for (i = 3; i < 6; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			/*
			i = 3 newBS_1=BS_1 右边的棋子
			i = 4 newBS_1=BS_1 上边的棋子
			i = 5 newBS_1=BS_1 左边的棋子
			*/
			newBS_2 = newBSx_2 * 4 + newBSy_2;//newBS_2 = 0
			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				/*小兵在前四行*/
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*BS_2是BS_1下方的点，newBS_1是小兵
				BS_1 周围的小兵棋子与BS_2互换
				*/
				insert_queue(newChess);
			}
		}
		//第二个空格周围的小兵走两个格子，即第二个格子下，左，右
		for (i = 5; i < 8; i++) {
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];
			newBS_2 = newBSx_2 * 4 + newBSy_2;
			/*
			i = 5 newBS_2=BS_2 左边的棋子
			i = 6 newBS_2=BS_2 下边的棋子
			i = 7 newBS_2=BS_2 右边的棋子
			*/
			if (newBSx_2 >= 0 && newBSx_2 < 5 && newBSy_2 >= 0 && newBSy_2 < 4 && chess[newBS_2] >= 1 && chess[newBS_2] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_1] = newChess[newBS_2];
				newChess[newBS_2] = 0;
				/*BS_2是BS_1下方的点，newBS_2是小兵
				BS_2 周围的小兵棋子与BS_1互换
				*/
				insert_queue(newChess);
			}
		}

		/*
		竖将纵向移动两个
		*/
		for (i = 0; i < 3; i += 2) {
			newBSx_1 = BSx_1 + 2 * dx[i];
			newBSy_1 = BSy_1 + 2 * dy[i];
			newBSx_2 = BSx_2 + 2 * dx[i];
			newBSy_2 = BSy_2 + 2 * dy[i];

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 0 newBS = BS上方两格的棋子
			i = 2 newBS = BS下方两格的棋子
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] == chess[newBS_2]) {
				/*newBSx_1和newBSx_2在同一列
				i = 0 BS_1和BS_2上方两格的棋子
				i = 2 BS_1和BS_2下方两格的棋子
				*/
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //竖将移动
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
					/*
					i = 0 BS_1和BS_2上方两格的棋子向下移动两格
					i = 2 BS_1和BS_2下方两格的棋子向上移动两格
					*/
					insert_queue(newChess);
				}
			}
		}

		/*
		竖将横向移动一格
		*/
		for (i = 1; i < 4; i += 2) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 1 newBS = BS左边的棋子
			i = 3 newBS = BS右边的棋子
			*/

			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] == chess[newBS_2]) {
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //竖将移动
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
					/*
					i = 1 BS左边的竖将棋子向右移动
					i = 3 BS右边的竖将向左边移动
					*/
				}
				else { //曹操移动
					newBSx_1 = newBSx_1 + dx[i];
					newBSy_1 = newBSy_1 + dy[i];
					newBSx_2 = newBSx_2 + dx[i];
					newBSy_2 = newBSy_2 + dy[i];

					newBS_1 = newBSx_1 * 4 + newBSy_1;
					newBS_2 = newBSx_2 * 4 + newBSy_2;

					/*
					i = 1 newBS=原newBS左边的棋子=BS左边两格棋子
					i = 3 newBS=原newBS右边的棋子=BS右边两格棋子
					*/
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;

					/*
					i = 1 曹操右移一格
					i = 3 曹操左移一格
					*/
				}
				insert_queue(newChess);
			}
		}
	}
	else { //横放BS_2在BS_1的右边
	 //第一个空格周围的小兵走两个格子，即第一个格子上，左，下
		for (i = 0; i < 3; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;//newBS_2 = 0
			/*newBS_2=0
			i = 0 newBS_1 = BS_1上边的棋子
			i = 1 newBS_1 = BS_1左边的棋子
			i = 2 newBS_1 = BS_1下边的棋子
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*newBS_1是小兵
				BS_1周围的棋子与BS_2互换
				*/
				insert_queue(newChess);
			}
		}
		//第二个空格周围的小兵走两个格子，即第二个格子下，上，右
		for (i = 2; i < 5; i++) {
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];
			newBS_2 = newBSx_2 * 4 + newBSy_2;
			/*
			i = 2 newBS_2 = BS_2下边的棋子
			i = 3 newBS_2 = BS_2右边的棋子
			i = 4 newBS_2 = BS_2上边的棋子
			*/
			if (newBSx_2 >= 0 && newBSx_2 < 5 && newBSy_2 >= 0 && newBSy_2 < 4 && chess[newBS_2] >= 1 && chess[newBS_2] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_1] = newChess[newBS_2];
				newChess[newBS_2] = 0;
				/*newBS_2是小兵
				BS_2周围的棋子与BS_1互换
				*/
				insert_queue(newChess);
			}
		}
		for (i = 3; i < 6; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			/*
			i = 3 newBS_1 = BS_1右边的棋子
			i = 4 newBS_1 = BS_1上边的棋子
			i = 5 newBS_1 = BS_1左边的棋子
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*newBS_1是小兵
				将BS_1周围的小兵与BS_2交换
				*/
				insert_queue(newChess);
			}
		}
		for (i = 1; i < 4; i += 2) { //横将左右移动
			newBSx_1 = BSx_1 + dx[i] * 2;
			newBSy_1 = BSy_1 + dy[i] * 2;
			newBSx_2 = BSx_2 + dx[i] * 2;
			newBSy_2 = BSy_2 + dy[i] * 2;

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 1 newBS = BS 左边两格的棋子
			i = 3 newBS = BS 右边两格的棋子
			*/

			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 3 && chess[newBS_1] == chess[newBS_2]) {
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //横将移动
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
				}
				insert_queue(newChess);
			}
		}

		for (i = 0; i < 3; i += 2) {  //横将上下移动
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 3 && chess[newBS_1] == chess[newBS_2]) {
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) {
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
				}
				else { //曹操移动
					newBSx_1 = newBSx_1 + dx[i];
					newBSy_1 = newBSy_1 + dy[i];
					newBSx_2 = newBSx_2 + dx[i];
					newBSy_2 = newBSy_2 + dy[i];

					newBS_1 = newBSx_1 * 4 + newBSy_1;
					newBS_2 = newBSx_2 * 4 + newBSy_2;
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
				}
				insert_queue(newChess);
			}
		}
	}
}
int Search::bfs() {
	memset(dist, 0, sizeof(dist));
	init_lookup_table();  //初始化查找表，将三个哈希表初始赋值为0

	while (front < rear) {
		State& s = st[front];
		if (s[13] == 10 && s[14] == 10 && s[17] == 10 && s[18] == 10) {
			return front;
		}
		try_to_insert(s);
		//广度优先，看当前空格有什么棋子可以移动
		move(s);
		front++;
	}
	return 0;
}

void Search::move(char* chess) {
	int i;
	int BS_1 = 20; //空格所在位置
	int BS_2 = 20;
	for (i = 0; i < 20; i++) {
		if (chess[i] == 0 && BS_1 == 20) {
			BS_1 = i;
		}
		else if (chess[i] == 0) {
			BS_2 = i;
			break;
		}
	} //找到空格所在位置

	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;
	int BSx_2 = BS_2 / 4;
	int BSy_2 = BS_2 % 4;  //获取空格的行列编号，x是行编号，y是列编号

	//判断空格样式，若两个空格分开，则分开处理，若两个空格连并，则合并处理
	if (BSx_2 == (BSx_1 + 1) && BS_2 == BS_1 + 4) { //判断条件为两个是否相邻（竖放）
		walk_2(chess, BS_1, BS_2);
		switch (mark) {
		case 1:
			walk1_1(chess, BS_1);
            walk1_1(chess, BS_2);
			break;
		case 2:
			walk2_1(chess, BS_1);
            walk2_1(chess, BS_2);
			break;
		case 3:
			walk3_1(chess, BS_1);
			walk3_1(chess, BS_2);
			break;
		case 4:
			walk1_1(chess, BS_1);
			walk1_1(chess, BS_2);
			break;
		}

	}
	else if (BSy_2 == (BSy_1 + 1) && BS_2 == BS_1 + 1) {//（横放）
		walk_2(chess, BS_1, BS_2);
		switch (mark) {
		case 1:
			walk1_1(chess, BS_1);
			walk1_1(chess, BS_2);
			break;
		case 2:
			walk2_1(chess, BS_1);
			walk2_1(chess, BS_2);
			break;
		case 3:
			walk3_1(chess, BS_1);
			walk3_1(chess, BS_2);
			break;
		case 4:
			walk1_1(chess, BS_1);
			walk1_1(chess, BS_2);
			break;
		}
	}
	else { //当两者不相邻时
		switch (mark) {
		case 1:
			walk1_1(chess, BS_1);
			walk1_1(chess, BS_2);
			break;
		case 2:
			walk2_1(chess, BS_1);
			walk2_1(chess, BS_2);
			break;
		case 3:
			walk3_1(chess, BS_1);
			walk3_1(chess, BS_2);
			break;
		case 4:
			walk1_1(chess, BS_1);
			walk1_1(chess, BS_2);
			break;
		}
	}
}

void Search::Run() {
	switch (mark)
	{
	case 1:
		memcpy(st[1], chess1, sizeof(chess1));   //起始状态
		break;
	case 2:
		memcpy(st[1], chess2, sizeof(chess2));   //起始状态
		break;
	case 3:
		memcpy(st[1], chess3, sizeof(chess3));   //起始状态
		break;
	case 4:
		memcpy(st[1], chess4, sizeof(chess4));   //起始状态
		break;
/*	case 5:
		memcpy(st[1], chess5, sizeof(chess5));   //起始状态
		break;*/
	}
	int ans = bfs();
	if (ans > 0) {
		int n = front;
		count = dist[front];
		int k = dist[front];
		while (n != 0) {
			memcpy(answer[k], st[n], sizeof(answer[k]));
			k--;
			n = cur[n];
		}
	}
}
void Search::Run1(char ch[5][4]) {
	switch (mark)
	{
	case 1:
		memcpy(st[1], ch, 20);   //起始状态
		break;
	case 2:
		memcpy(st[1], ch, 20);   //起始状态
		break;
	case 3:
		memcpy(st[1], ch, 20);   //起始状态
		break;
	case 4:
		memcpy(st[1], ch, 20);   //起始状态
		break;
		/*	case 5:
				memcpy(st[1], chess5, sizeof(chess5));   //起始状态
				break;*/
	}
	int ans = bfs();
	if (ans > 0) {
		int n = front;
		count = dist[front];
		int k = dist[front];
		while (n != 0) {
			memcpy(answer[k], st[n], sizeof(answer[k]));
			k--;
			n = cur[n];
		}
	}
}