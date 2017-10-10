#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include"json/json.h"
#include"json_read.h"
#pragma warning(disable:4996)
using namespace std;
int n, m;
void match() {
	for (int xx = 1; xx <= 15; xx++) {
		for (int i = 0; i < m; i++) 
		{
			if (departments[i].getNumOfMember() >=departments[i].getMemberLimit() ) continue;
			int numOfEvent = departments[i].getNumOfEvents(), numOfTags = departments[i].getNumOfTags();
			int event[300];
			mptags.clear();
			for (int j = 1; j <= numOfEvent; j++) event[j] = departments[i].getKthEvent(j);
			for (int j = 1; j <= numOfTags; j++) mptags[departments[i].getKthTags(j)] = 1;
			node best;
			best.id = -1; best.score = 0;

			for (int j = 0; j < n; j++)
			{
				//if (i==1) cout << "i=" << i << "  j=" << j << endl;
				int flag2 = 0, score = 0;
				for (int k = 1; k <= numOfEvent; k++) 
				{
					if (students[j].judgeSpareTime(event[k]) != 1)
					{
						flag2 = 1;
						//if (i==1) cout << j << " " << event[k] << endl;
						break;
					}
				}
				int numOfApply = students[j].getNumOfApplyDepartments();
				for (int k = 1; k <= numOfApply; k++) 
				{
					if (students[j].getKthApplications(k) == departments[i].getDepartment_no()) 
					{
						score += (12 - 2 * k);
						break;
					}
				}
				//cout << "i=" << i << " j=" << j << " flag2=" << flag2 << " vis[i][j]=" << vis[i][j] << " score=" << score << endl;
				if (flag2 == 1 || vis[i][j] == 1 || score == 0) continue;
				//cout << "hello" << endl;
				int numOfTags = students[j].getNumOfTags();
				for (int k = 1; k <= numOfTags; k++) 
				{
					if (mptags[students[j].getKthTags(k)] == 1) score++;
				}
				if (score>=best.score) 
				{
					best.score = score;
					best.id = j;
				}
			}
			
			
			//cout << best.id << " " << best.score << endl;
			if (best.id != -1) 
			{
				departments[i].addMember(students[best.id]);
				students[best.id].addAcceptDepartments(departments[i].getDepartment_no());
				vis[i][best.id] = 1;
				for (int j = 1; j <= departments[i].getNumOfEvents(); j++) 
				{
					students[best.id].updateSpareTime(departments[i].getKthEvent(j));
				}
			}
		}
	}
}

void solveUnlucky_student() {
	printf("\"unlucky_student\": [");
	int flag = 1;
	for (int i = 0; i < n; i++) {
		if (students[i].getNumOfAcceptDepartments() == 0) {
			if (flag != 1) printf(",");
			printf("\"");
			cout << students[i].getStudent_no() ;
			printf("\"");
			flag = 0;
		}
	}
	printf("]");
}

void solveAdmitted() {
	printf("\"admitted\": [");
	int flag1 = 1;
	for (int i = 0; i < m; i++) {
		int num = departments[i].getNumOfMember();
		if (num <= 0) continue;
		if (flag1 != 1) printf(",");
		printf("{\"member\": [");
		for (int j = 1; j <= num; j++) {
			if (j != 1) printf(",");
			printf("\"");
			cout << departments[i].getKthMember(j).getStudent_no() ;
			printf("\"");
		}
		printf("],");
		printf("\"department_no\": \"");
		cout << departments[i].getDepartment_no();
		printf("\"}");
		flag1 = 0;
	}
	printf("]");
}

void solveUnlucky_department() {
	printf("\"unlucky_department\": [");
	int flag = 1;
	for (int i = 0; i < m; i++) {
		if (departments[i].getNumOfMember() == 0) {
			if (flag != 1) printf(",");
			printf("\"");
			cout << departments[i].getDepartment_no() ;
			printf("\"");
			flag = 0;
		}
	}
	printf("]");
}

void print() {
	printf("{");
	solveUnlucky_student();
	printf(",");
	solveAdmitted();
	printf(",");
	solveUnlucky_department();
	printf("}");
}

int main() {
	freopen("output_data.txt", "w", stdout);
	json_read();
	n = N;
	m = M;
	
	//system("pause");
	
	match();

	print();
	return 0;
}