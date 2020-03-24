#include<bits/stdc++.h>
#include<conio.h>
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
	map<int, vector<node> >::iterator itr;
	//running queue
	vector<node> running;
	//done queue
	vector<node> done;
	for(int i=0;i<maps.begin()->second.size();++i) {
		running.push_back(maps.begin()->second[i]);
	}
	maps.erase(maps.begin());
	//sorting running list
	for(int i=0;i<running.size();++i) {
		for(int j=0;j<running.size()-i-1;++j) {
			if(running[j].burst>running[j+1].burst) {
				node temp = running[j];
				running[j] = running[j+1];
				running[j+1] = temp;
			}
		}
	}
	for(int i=0;i<running.size();++i) {
		running[i].priority = 1;
	}
	int timer = running[0].arrival;
	while(done.size()!=n) {timer += running[0].burst;
		running[0].turnaround = timer - running[0].arrival;
		done.push_back(running[0]);
		running.erase(running.begin());
		for(itr=maps.begin();itr!=maps.end();++itr) {
			if(itr->first<=timer) {
				for(int i=0;i<itr->second.size();++i) {
					bool inrunning = false;
					for(int j=0;j<running.size();++j) {
						if(running[j].process==itr->second[i].process) {
							inrunning = true;
							break;
						}
					}
					bool indone = false;
					for(int j=0;j<done.size();++j) {
						if(done[j].process==itr->second[i].process) {
							indone = true;
							break;
						}
					}
					if(inrunning==false && indone==false) {
						running.push_back(itr->second[i]);
					}
				}
			}
		}
		for(int i=0;i<running.size();++i) {
				running[i].waiting = timer - running[i].arrival;
				running[i].priority = 1 + ((running[i].waiting)/running[i].burst);
		}
		bool notsame = false;
		int firstpriority = running[0].priority;
		for(int i=1;i<running.size();++i) {
			if(running[i].priority!=firstpriority) {
				notsame = true;
				break;
			}
		}
		if(!notsame) {
//			cout<<"Sorting based on time...\n";
// 			sorting running list based on time
			for(int i=0;i<running.size();++i) {
				for(int j=0;j<running.size()-i-1;++j) {
					if(running[j].burst>running[j+1].burst) {
						node temp = running[j];
						running[j] = running[j+1];
						running[j+1] = temp;
					}
				}
			}
		}
		else {
//			cout<<"Sorting based on priority...\n";
// 			sorting running list based on priority
			for(int i=0;i<running.size();++i) {
				for(int j=0;j<running.size()-i-1;++j) {
					if(running[j].priority<running[j+1].priority) {
						node temp = running[j];
						running[j] = running[j+1];
						running[j+1] = temp;
					}
				}
			}
// 			sorting based on time until same priority
			int firstpriority = running[0].priority;
			int lastindex;
			for(int i=1;i<running.size();++i) {
				if(running[i].priority==firstpriority)
					lastindex = i;
				else
					break;
			}
//			cout<<"last index is: "<<lastindex<<"\n";
			for(int i=0;i<lastindex;++i) {
				for(int j=0;j<lastindex-i;++j) {
					if(running[j].burst>running[j+1].burst) {
						node temp = running[j];
						running[j] = running[j+1];
						running[j+1] = temp;
					}
				}
			}
		}
	}
	printf(" * * * * * After scheduling * * * * *\n");
	double awt=0, atat=0;
	printf("Process\t\tWaiting Time\tTurnaround Time\n");
	for(int i=0;i<n;++i) {
		printf("P%d\t\t%d\t\t%d\n", done[i].process, done[i].waiting, done[i].turnaround);
		awt += done[i].waiting;
		atat += done[i].turnaround;
	}
	awt /= n;
	atat /= n;
	printf("Average waiting time is: %.2f\n", awt);
	printf("Average turnaround time is: %.2f\n", atat);
	printf("Enter any key to exit...\n");
	getch();
}
