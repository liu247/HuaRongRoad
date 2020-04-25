#include "pch.h"
#include "Search.h"

Search::Search() {
	/*����malloc�ڶ��ڴ��п����ڴ�ռ�,���Ĵ�С��Ԫ�صĸ������Ը��������͵ĳ���*/ 
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
	n1 = (p[1] << 3) + (p[2] << 5) + p[0]; //ÿ���۵�ʱ��Ӧ��ַ��Ӹ�������,��ǿɢ��
	n2 = (p[3] << 1) + (p[4] << 4);
	m0 = (n2 << 6) ^ (n1 << 3); //��ǿɢ�в���
	//��һ��ϣ����
	h1 = n1 + n2 + m0;
	h2 = n1 - n2 + m0;
	hs17(h1, h);//h1Ϊɢ�к�,hΪ��һ��ϣ����
	if (!hsb[h]) {
		hsb[h] = h1;  //h1Ϊɢ�к�,hΪ��һ��ϣ����
		return 1;
	}
	if (hsb[h] == h1) return 0;

	//�ڶ���ϣ����
	h1 = n1 - n2 + m0;
	hs15(h1, h);//h1Ϊɢ�в�,hΪ�ڶ���ϣ
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
		rear++;  //����ɹ�������ұ��޸Ķ�βָ��
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

	if (BS_1 - 4 >= 0 && BS_1 - 4 < 20 && chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 8) { //����Ϸ��������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //�����ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && ((chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 4) || chess[BS_1 - 1] == 9)) {//������Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && ((chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 4) || chess[BS_1 + 1] == 9)) { 		//����ҷ��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BS_1 + 4 >= 0 && BS_1 + 4 < 20 && chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 8) {		//����·��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //�����ƶ�
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

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4) || chess[BS_1 - 4] == 9)) { //����Ϸ��������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //�����ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 8) {//������Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 8) { 		//����ҷ��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4) || chess[BS_1 + 4] == 9)) {		//����·��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //�����ƶ�
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

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4) || (chess[BS_1 - 4] >= 7 && chess[BS_1 - 4] <= 9))) { //����Ϸ��������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		else { //�����ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 8] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 6) {//������Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 6) { 		//����ҷ��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4) || (chess[BS_1 + 4] >= 7 && chess[BS_1 + 4] <= 9))) {		//����·��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 4];
			newChess[BS_1 + 4] = 0;
		}
		else { //�����ƶ�
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

	if (BSx_1 - 1 >= 0 && BS_1 - 4 >= 0 && ((chess[BS_1 - 4] >= 1 && chess[BS_1 - 4] <= 4))) { //����Ϸ��������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 4] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 4];
			newChess[BS_1 - 4] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 - 1 >= 0 && chess[BS_1 - 1] >= 1 && chess[BS_1 - 1] <= 9) {//������Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 - 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 - 1];
			newChess[BS_1 - 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSy_1 + 1 < 4 && chess[BS_1 + 1] >= 1 && chess[BS_1 + 1] <= 9) { 		//����ҷ��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 1] <= 4) { //С���ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 1] = 0;
		}
		else { //�Ὣ�ƶ�
			newChess[BS_1] = newChess[BS_1 + 1];
			newChess[BS_1 + 2] = 0;
		}
		insert_queue(newChess);
	}
	if (BSx_1 + 1 < 5 && BS_1 + 4 >= 0 && ((chess[BS_1 + 4] >= 1 && chess[BS_1 + 4] <= 4))) {		//����·��Ƿ�������Ƿ�����ƶ�
		memcpy(newChess, chess, sizeof(newChess));
		if (chess[BS_1 + 4] <= 4) { //С���ƶ�
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
	int BSy_2 = BS_2 % 4;  //��ȡ�ո�����б��

	int newBSx_1, newBSy_1;
	int newBSx_2 = 0, newBSy_2 = 0;
	int  newBS_1, newBS_2;   //�¿ո�λ��

	char newChess[20];
	int i;

	/*
	�����ŵĿո���Χ�����ƶ����ƶ�����
	*/
	if (BS_2 - BS_1 == 4) { //����
		//��һ���ո���Χ��С�����������ӣ�����һ�������ϣ�����
		for (i = 3; i < 6; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			/*
			i = 3 newBS_1=BS_1 �ұߵ�����
			i = 4 newBS_1=BS_1 �ϱߵ�����
			i = 5 newBS_1=BS_1 ��ߵ�����
			*/
			newBS_2 = newBSx_2 * 4 + newBSy_2;//newBS_2 = 0
			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				/*С����ǰ����*/
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*BS_2��BS_1�·��ĵ㣬newBS_1��С��
				BS_1 ��Χ��С��������BS_2����
				*/
				insert_queue(newChess);
			}
		}
		//�ڶ����ո���Χ��С�����������ӣ����ڶ��������£�����
		for (i = 5; i < 8; i++) {
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];
			newBS_2 = newBSx_2 * 4 + newBSy_2;
			/*
			i = 5 newBS_2=BS_2 ��ߵ�����
			i = 6 newBS_2=BS_2 �±ߵ�����
			i = 7 newBS_2=BS_2 �ұߵ�����
			*/
			if (newBSx_2 >= 0 && newBSx_2 < 5 && newBSy_2 >= 0 && newBSy_2 < 4 && chess[newBS_2] >= 1 && chess[newBS_2] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_1] = newChess[newBS_2];
				newChess[newBS_2] = 0;
				/*BS_2��BS_1�·��ĵ㣬newBS_2��С��
				BS_2 ��Χ��С��������BS_1����
				*/
				insert_queue(newChess);
			}
		}

		/*
		���������ƶ�����
		*/
		for (i = 0; i < 3; i += 2) {
			newBSx_1 = BSx_1 + 2 * dx[i];
			newBSy_1 = BSy_1 + 2 * dy[i];
			newBSx_2 = BSx_2 + 2 * dx[i];
			newBSy_2 = BSy_2 + 2 * dy[i];

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 0 newBS = BS�Ϸ����������
			i = 2 newBS = BS�·����������
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] == chess[newBS_2]) {
				/*newBSx_1��newBSx_2��ͬһ��
				i = 0 BS_1��BS_2�Ϸ����������
				i = 2 BS_1��BS_2�·����������
				*/
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //�����ƶ�
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
					/*
					i = 0 BS_1��BS_2�Ϸ���������������ƶ�����
					i = 2 BS_1��BS_2�·���������������ƶ�����
					*/
					insert_queue(newChess);
				}
			}
		}

		/*
		���������ƶ�һ��
		*/
		for (i = 1; i < 4; i += 2) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 1 newBS = BS��ߵ�����
			i = 3 newBS = BS�ұߵ�����
			*/

			if (newBSx_1 >= 0 && newBSx_1 < 4 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] == chess[newBS_2]) {
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //�����ƶ�
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
					/*
					i = 1 BS��ߵ��������������ƶ�
					i = 3 BS�ұߵ�����������ƶ�
					*/
				}
				else { //�ܲ��ƶ�
					newBSx_1 = newBSx_1 + dx[i];
					newBSy_1 = newBSy_1 + dy[i];
					newBSx_2 = newBSx_2 + dx[i];
					newBSy_2 = newBSy_2 + dy[i];

					newBS_1 = newBSx_1 * 4 + newBSy_1;
					newBS_2 = newBSx_2 * 4 + newBSy_2;

					/*
					i = 1 newBS=ԭnewBS��ߵ�����=BS�����������
					i = 3 newBS=ԭnewBS�ұߵ�����=BS�ұ���������
					*/
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;

					/*
					i = 1 �ܲ�����һ��
					i = 3 �ܲ�����һ��
					*/
				}
				insert_queue(newChess);
			}
		}
	}
	else { //���BS_2��BS_1���ұ�
	 //��һ���ո���Χ��С�����������ӣ�����һ�������ϣ�����
		for (i = 0; i < 3; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;//newBS_2 = 0
			/*newBS_2=0
			i = 0 newBS_1 = BS_1�ϱߵ�����
			i = 1 newBS_1 = BS_1��ߵ�����
			i = 2 newBS_1 = BS_1�±ߵ�����
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*newBS_1��С��
				BS_1��Χ��������BS_2����
				*/
				insert_queue(newChess);
			}
		}
		//�ڶ����ո���Χ��С�����������ӣ����ڶ��������£��ϣ���
		for (i = 2; i < 5; i++) {
			newBSx_2 = BSx_2 + dx[i];
			newBSy_2 = BSy_2 + dy[i];
			newBS_2 = newBSx_2 * 4 + newBSy_2;
			/*
			i = 2 newBS_2 = BS_2�±ߵ�����
			i = 3 newBS_2 = BS_2�ұߵ�����
			i = 4 newBS_2 = BS_2�ϱߵ�����
			*/
			if (newBSx_2 >= 0 && newBSx_2 < 5 && newBSy_2 >= 0 && newBSy_2 < 4 && chess[newBS_2] >= 1 && chess[newBS_2] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_1] = newChess[newBS_2];
				newChess[newBS_2] = 0;
				/*newBS_2��С��
				BS_2��Χ��������BS_1����
				*/
				insert_queue(newChess);
			}
		}
		for (i = 3; i < 6; i++) {
			newBSx_1 = BSx_1 + dx[i];
			newBSy_1 = BSy_1 + dy[i];
			newBS_1 = newBSx_1 * 4 + newBSy_1;
			/*
			i = 3 newBS_1 = BS_1�ұߵ�����
			i = 4 newBS_1 = BS_1�ϱߵ�����
			i = 5 newBS_1 = BS_1��ߵ�����
			*/
			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 4 && chess[newBS_1] >= 1 && chess[newBS_1] <= 4) {
				memcpy(newChess, chess, sizeof(newChess));
				newChess[BS_2] = newChess[newBS_1];
				newChess[newBS_1] = 0;
				/*newBS_1��С��
				��BS_1��Χ��С����BS_2����
				*/
				insert_queue(newChess);
			}
		}
		for (i = 1; i < 4; i += 2) { //�Ὣ�����ƶ�
			newBSx_1 = BSx_1 + dx[i] * 2;
			newBSy_1 = BSy_1 + dy[i] * 2;
			newBSx_2 = BSx_2 + dx[i] * 2;
			newBSy_2 = BSy_2 + dy[i] * 2;

			newBS_1 = newBSx_1 * 4 + newBSy_1;
			newBS_2 = newBSx_2 * 4 + newBSy_2;

			/*
			i = 1 newBS = BS ������������
			i = 3 newBS = BS �ұ����������
			*/

			if (newBSx_1 >= 0 && newBSx_1 < 5 && newBSy_1 >= 0 && newBSy_1 < 3 && chess[newBS_1] == chess[newBS_2]) {
				memcpy(newChess, chess, sizeof(newChess));
				if (chess[newBS_2] != 10) { //�Ὣ�ƶ�
					newChess[BS_1] = newChess[newBS_1];
					newChess[BS_2] = newChess[newBS_2];
					newChess[newBS_1] = newChess[newBS_2] = 0;
				}
				insert_queue(newChess);
			}
		}

		for (i = 0; i < 3; i += 2) {  //�Ὣ�����ƶ�
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
				else { //�ܲ��ƶ�
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
	init_lookup_table();  //��ʼ�����ұ���������ϣ���ʼ��ֵΪ0

	while (front < rear) {
		State& s = st[front];
		if (s[13] == 10 && s[14] == 10 && s[17] == 10 && s[18] == 10) {
			return front;
		}
		try_to_insert(s);
		//������ȣ�����ǰ�ո���ʲô���ӿ����ƶ�
		move(s);
		front++;
	}
	return 0;
}

void Search::move(char* chess) {
	int i;
	int BS_1 = 20; //�ո�����λ��
	int BS_2 = 20;
	for (i = 0; i < 20; i++) {
		if (chess[i] == 0 && BS_1 == 20) {
			BS_1 = i;
		}
		else if (chess[i] == 0) {
			BS_2 = i;
			break;
		}
	} //�ҵ��ո�����λ��

	int BSx_1 = BS_1 / 4;
	int BSy_1 = BS_1 % 4;
	int BSx_2 = BS_2 / 4;
	int BSy_2 = BS_2 % 4;  //��ȡ�ո�����б�ţ�x���б�ţ�y���б��

	//�жϿո���ʽ���������ո�ֿ�����ֿ������������ո���������ϲ�����
	if (BSx_2 == (BSx_1 + 1) && BS_2 == BS_1 + 4) { //�ж�����Ϊ�����Ƿ����ڣ����ţ�
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
	else if (BSy_2 == (BSy_1 + 1) && BS_2 == BS_1 + 1) {//����ţ�
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
	else { //�����߲�����ʱ
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
		memcpy(st[1], chess1, sizeof(chess1));   //��ʼ״̬
		break;
	case 2:
		memcpy(st[1], chess2, sizeof(chess2));   //��ʼ״̬
		break;
	case 3:
		memcpy(st[1], chess3, sizeof(chess3));   //��ʼ״̬
		break;
	case 4:
		memcpy(st[1], chess4, sizeof(chess4));   //��ʼ״̬
		break;
/*	case 5:
		memcpy(st[1], chess5, sizeof(chess5));   //��ʼ״̬
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
		memcpy(st[1], ch, 20);   //��ʼ״̬
		break;
	case 2:
		memcpy(st[1], ch, 20);   //��ʼ״̬
		break;
	case 3:
		memcpy(st[1], ch, 20);   //��ʼ״̬
		break;
	case 4:
		memcpy(st[1], ch, 20);   //��ʼ״̬
		break;
		/*	case 5:
				memcpy(st[1], chess5, sizeof(chess5));   //��ʼ״̬
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