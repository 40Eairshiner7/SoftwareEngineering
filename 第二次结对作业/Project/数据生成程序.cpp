#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include<cstdlib>
#include<cstring>
using namespace std;

int n,m;

string tag[50];

void printWeekday(int i) {
	if (i==1) printf("Mon.");
	if (i==2) printf("Tues.");
	if (i==3) printf("Wed.");
	if (i==4) printf("Thur.");
	if (i==5) printf("Fri.");
	if (i==6) printf("Sat.");
	if (i==7) printf("Sun.");
}

void solveFree_time() {
	printf("\"free_time\": [");
	int flag=1;
	for (int i=1; i<=7; i++) {
		int cur=8;
		while (cur<=20) {
			int len=rand()%7;
			if(len==0 || len>=5) {
				cur++;
				continue;
			}
			if (flag!=1) printf(",");
			printf("\"");
			printWeekday(i);
			printf("%02d:00~%02d:00",cur,cur+len);
			printf("\"");
			cur=cur+len+(rand()%2);
			flag=0;
		}
	}
	printf("]");
}

void solveEvent_schedules() {
	printf("\"event_schedules\": [");
	int flag=1,cnt=0;
	for (int i=1; i<=7; i++) {
		int tmp=rand()%12+1;
		if (tmp+cnt*2>7) {
			continue;
		}
		cnt++;
		int start=rand()%12+9;
		int len=(rand()%5)/2+1;
		if (flag!=1) printf(",");
		printf("\"");
		printWeekday(i);
		printf("%02d:00~%02d:00",start,start+len);
		printf("\"");
		flag=0;
		if (cnt>=3) break;
	}
	printf("]");
}

void solveStudent_no(int i) {
	printf("\"student_no\":");
	printf("\"031502");
	printf("%03d\"",i);
}

void solveApplications_department() {
	printf("\"applications_department\": [");
	int vis[50];
	memset(vis, 0, sizeof(vis));
	int num=sqrt(rand()%16)+2;
	for (int i=1; i<=num; ) {
		int tmp=rand()%m+1;
		if (vis[tmp]==0) {
			if (i!=1) printf(",");
			printf("\"D");
			printf("%03d\"",tmp);
			vis[tmp]=1;
			i++;
		}
	}
	printf("]");
}

void solveTags(int num) {
	printf("\"tags\": [");
	int vis[50];
	memset(vis, 0, sizeof(vis));
	for (int i=1; i<=num; ) {
		int tmp=rand()%30+1;
		if (vis[tmp]==0) {
			if (i!=1) printf(",");
			printf("\"");
			cout << tag[tmp];
			printf("\"");
			i++;
		}
	}
	printf("]");
}

void solveStu(int i) {
	solveFree_time();
	printf(",");
	solveStudent_no(i);
	printf(",");
	solveApplications_department();
	printf(",");
	int tmp=rand()%4+2;
	solveTags(tmp);
}

void solveMember_limit() {
	printf("\"member_limit\":");
	int tmp=sqrt(rand()%35);
	printf("%d",10+tmp);
}

void solveDepartment_no(int i) {
	printf("\"department_no\":");
	printf("\"D");
	printf("%03d\"",i);
}

void solveDep(int i) {
	solveEvent_schedules();
	printf(",");
	solveMember_limit();
	printf(",");
	solveDepartment_no(i);
	printf(",");
	int tmp=sqrt(rand()%80)+2;
	solveTags(tmp);
}

void theTags() {
	tag[1]="reading";
	tag[2]="jog";
	tag[3]="climbing";
	tag[4]="film";
	tag[5]="English";
	tag[6]="music";
	tag[7]="dance";
	tag[8]="basketball";
	tag[9]="chess";
	tag[10]="programming";
	tag[11]="xxx";
	tag[12]="yyy";
	tag[13]="zzz";
	tag[14]="aaa";
	tag[15]="bbb";
	tag[16]="ccc";
	tag[17]="ddd";
	tag[18]="eee";
	tag[19]="fff";
	tag[20]="ggg";
	tag[21]="hhh";
	tag[22]="iii";
	tag[23]="jjj";
	tag[24]="kkk";
	tag[25]="lll";
	tag[26]="mmm";
	tag[27]="nnn";
	tag[28]="ooo";
	tag[29]="ppp";
	tag[30]="qqq";
}

int main() {
	freopen("input_data.txt", "w", stdout);
	n=300;m=20;
	srand((int)time(0));
	
	theTags();
	
	printf("{");
	printf("\"students\":[");
	for (int i=1; i<=300; i++) {
		if (i!=1) printf(",");
		printf("{");
		solveStu(i);
		printf("}");
	}
	printf("]");
	printf(",");
	printf("\"departments\":[");
	for (int i=1; i<=20; i++) {
		if (i!=1) printf(",");
		printf("{");
		solveDep(i);
		printf("}");
	}
	printf("]");
	printf("}");
	
	return 0;
}
