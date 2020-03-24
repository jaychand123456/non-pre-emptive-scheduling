#include<bits/stdc++.h>
using namespace std;

struct node {
	int process;
	int burst;
	int arrival;
	int waiting;
	int priority;
	int turnaround;
};

int main() {
	int n;
	printf("Enter the number of process: ");
	scanf("%d",&n);
	map<int, vector<node> > maps;
	printf("Enter the arrival time and burst time of each process:\n");
	for(int i=0;i<n;++i) {
		int at,bt;
		scanf("%d", &at);
		scanf("%d", &bt);
		node temp;
		temp.process = i+1;
		temp.burst = bt;
		temp.arrival = at;
		temp.waiting = 0;
		temp.priority = 0;
		temp.turnaround = 0;
		maps[at].push_back(temp);
	}
}
