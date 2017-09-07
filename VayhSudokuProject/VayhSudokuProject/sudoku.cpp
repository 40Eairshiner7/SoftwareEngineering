//
//  main.cpp
//  shudu
//
//  Created by airshiner on 9/7/17.
//  Copyright © 2017 airshiner. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

const int STARTNUM = (4 + 0) % 9 + 1;
const int ALL = 8 * 7 * 6 * 5 * 4 * 3 * 2;
int first, cnt, now, n;

char ch[1000];
int arr[11], cur[11][11];
int one[11], two[11];

int read() {
	int x = 0, f = 1, i = 0;
	int len = (int)strlen(ch);
	if (len>8) return -1;
	if (ch[0]<'0' || ch[0]>'9') {
		if (ch[0] == '-') f = -1, i++;
		else return -1;
	}
	while (i<len) {
		if (ch[i]<'0' || ch[i]>'9') return -1;
		x = x * 10 + ch[i++] - '0';
	}
	return x*f;
}

void init() {
	srand((int)time(0));
	now = cnt = 0;
	for (int i = 0; i<9; i++) {
		arr[cnt++] = i;
	}
	first = rand() % ALL;
}

void update() {
	cnt = 0;
	for (int i = 0; i<9; i++) {
		if (arr[i] != -1) arr[cnt++] = arr[i];
	}
}

void println() {
	for (int i = 0; i<9; i++) {
		for (int l = 0; l<9; l++) {
			printf("%d ", cur[i][l] + 1);
		}
		printf("\n");
	}
	printf("\n");
}

void get_abc(int k, int &a, int &b, int &c) {
	if (k<36) a = 0;
	else a = 1, k -= 36;
	b = k / 6;
	k -= (b * 6);
	c = k;
}

void solvea(int a) {
	if (a == 0) {
		for (int i = 0; i<9; i++) {
			cur[1][i] = cur[0][(i + 3) % 9];
			cur[2][i] = cur[0][(i + 6) % 9];
		}
	}
	else {
		for (int i = 0; i<9; i++) {
			cur[1][i] = cur[0][(i + 6) % 9];
			cur[2][i] = cur[0][(i + 3) % 9];
		}
	}
	for (int i = 0; i<9; i++) {
		one[i] = cur[0][(i + 1) % 9];
		two[i] = cur[0][(i + 2) % 9];
	}
}

void solveb(int b) {
	if (b<2) {
		for (int i = 0; i<9; i++) {
			cur[3][i] = one[i];
		}
	}
	else if (b<4) {
		for (int i = 0; i<9; i++) {
			cur[3][i] = one[(i + 3) % 9];
		}
	}
	else {
		for (int i = 0; i<9; i++) {
			cur[3][i] = one[(i + 6) % 9];
		}
	}
	if (b % 2 == 1) {
		for (int i = 0; i<9; i++) {
			cur[4][i] = cur[3][(i + 3) % 9];
			cur[5][i] = cur[3][(i + 6) % 9];
		}
	}
	else {
		for (int i = 0; i<9; i++) {
			cur[5][i] = cur[3][(i + 3) % 9];
			cur[4][i] = cur[3][(i + 6) % 9];
		}
	}
}

void solvec(int c) {
	if (c<2) {
		for (int i = 0; i<9; i++) {
			cur[6][i] = two[i];
		}
	}
	else if (c<4) {
		for (int i = 0; i<9; i++) {
			cur[6][i] = two[(i + 3) % 9];
		}
	}
	else {
		for (int i = 0; i<9; i++) {
			cur[6][i] = two[(i + 6) % 9];
		}
	}
	if (c % 2 == 1) {
		for (int i = 0; i<9; i++) {
			cur[7][i] = cur[6][(i + 3) % 9];
			cur[8][i] = cur[6][(i + 6) % 9];
		}
	}
	else {
		for (int i = 0; i<9; i++) {
			cur[8][i] = cur[6][(i + 3) % 9];
			cur[7][i] = cur[6][(i + 6) % 9];
		}
	}
}

void solvecur0(int num) {
	int tot = ALL;
	memset(cur, 0, sizeof(cur));
	cnt = 0;
	for (int i = 0; i<9; i++) {
		arr[cnt++] = i;
	}
	cur[0][0] = STARTNUM - 1;
	arr[cur[0][0]] = -1;
	for (int j = 1; j<9; j++) {
		update();
		tot /= (9 - j);
		int choose = num / tot;
		cur[0][j] = arr[choose];
		arr[choose] = -1;
		num -= (tot*choose);
	}
}

void solvecur() {
	for (int k = 0; k<72; k++) {
		if (now >= n) return;
		int a = 0, b = 0, c = 0;
		get_abc(k, a, b, c);
		solvea(a);
		solveb(b);
		solvec(c);
		println();
		now++;
		if (now >= n) return;
	}
}

int main(int argc, char *argv[]) {
	freopen("sudoku.txt", "w", stdout);
	if (argc == 3) {
		string op = *(argv + 1);
		if (op != "-c") {
			printf("Input wrong!\n");
			return 0;
		}
		string str = *(argv + 2);
		int len = (int)str.length();
		for (int i = 0; i<len; i++) {
			ch[i] = str[i];
		}
		n = read();
		if (n>1e6 || n<0) {
			printf("Input Wrong!\n");
			return 0;
		}
		init();
		for (int i = first; ; i = (i + 1) % ALL) {
			solvecur0(i);
			solvecur();
			if (now >= n) break;
		}
	}
	else {
		printf("Input Wrong!");
	}

	return 0;
}