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
	if(n<=0) {
		printf("Invalid input...");
		return 0;
	}
	vector<node> pro;
	printf("Enter the arrival time and burst time of each process:\n");
	for(int i=0;i<n;++i) {
		int at,bt;
		scanf("%d",&at);
		scanf("%d",&bt);
		if(at<0 or bt<0) {
			printf("Invalid input...");
			return 0;
		}
		node temp;
		temp.process = i+1;
		temp.burst = bt;
		temp.arrival = at;
		temp.waiting = 0;
		temp.priority = 0;
		temp.turnaround = 0;
		pro.push_back(temp);
	}
	//running queue;
	vector<node> running;
	//done queue;
	vector<node> done;
	//sorting pro queue;
	for(int i=0;i<pro.size();++i) {
		for(int j=0;j<pro.size()-i-1;++j) {
			if(pro[j].arrival>pro[j+1].arrival) {
				node temp = pro[j];
				pro[j] = pro[j+1];
				pro[j+1] = temp;
			}
		}
	}
	printf("After sorting, pro list is: ");
	for(int i=0;i<pro.size();++i) {
		printf("P%d ",pro[i].process);
	}printf("\n");
	running.push_back(pro[0]);
	int at = pro[0].arrival;
	pro.erase(pro.begin());
	while(pro[0].arrival==at) {
		running.push_back(pro[0]);
		pro.erase(pro.begin());
	}
	//sorting running list;
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
//	printf("Before while loop, running list is: ");
//	for(int i=0;i<running.size();++i) {
//		printf("P%d ",running[i].process);
//	}printf("\n");
//	printf("Before while loop, pro list is: ");
//	for(int i=0;i<pro.size();++i) {
//		printf("P%d ",pro[i].process);
//	}printf("\n");
	int timer = 0;
	int idle = timer - 0;
	while(done.size()!=n) {
		if(running.size()==0) {
//			idle += pro[0].arrival - timer;
			running.push_back(pro[0]);
			pro.erase(pro.begin());
		}
		if(timer<running[0].arrival) {
			idle += running[0].arrival - timer;
			timer = running[0].arrival;
		}
		timer += running[0].burst;
		running[0].turnaround = timer - running[0].arrival;
		done.push_back(running[0]);
//		printf("Running P%d\n", running[0].process);
//		printf("Idle time %d ", idle);
//		printf("Timer %d ",timer);
//		printf("Running time %d\n",running[0].arrival);
		running.erase(running.begin());
		vector<int> index;
		for(int i=0;i<pro.size();++i) {
			if(pro[i].arrival<=timer) {
				running.push_back(pro[i]);
				index.push_back(i);
			}
		}
		int remove = 0;
		for(int i=0;i<index.size();++i) {
			pro.erase(pro.begin() + index[i]-remove);
			remove++;
		}
//		printf("After adding, running list is: ");
//		for(int i=0;i<running.size();++i) {
//			printf("P%d ",running[i].process);
//		}
//		printf("\n");
//		printf("After adding, pro list is: ");
//		for(int i=0;i<pro.size();++i) {
//			printf("P%d ",pro[i].process);
//		}
//		printf("\n");
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
			for(int i=0;i<running.size();++i) {
				for(int j=0;j<running.size()-i-1;++j) {
					if(running[j].priority<running[j+1].priority) {
						node temp = running[j];
						running[j] = running[j+1];
						running[j+1] = temp;
					}
				}
			}
			int firstpriority = running[0].priority;
			int lastindex;
			for(int i=1;i<running.size();++i) {
				if(running[i].priority == firstpriority)
					lastindex = i;
				else
					break;
			}
			for(int i=0;i<lastindex;++i) {
				for(int j=0;j<lastindex-i-1;++j) {
					if(running[j].burst>running[j+1].burst) {
						node temp = running[j];
						running[j] = running[j+1];
						running[j+1] = temp;
					}
				}
			}
		}
//		printf("Running list is: ");
//		for(int i=0;i<running.size();++i) {
//			printf("P%d ",running[i].process);
//		}
//		printf("\n");
//		printf("Done list is: ");
//		for(int i=0;i<done.size();++i) {
//			printf("P%d ",done[i].process);
//		}
//		printf("\n");
	}
	printf(" * * * * * * * * * * * * * * * After scheduling * * * * * * * * * * * * * * *\n");
	double awt=0, atat=0;
	printf("Process\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
	for(int i=0;i<n;++i) {
		printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", done[i].process, done[i].arrival, done[i].burst, done[i].waiting, done[i].turnaround);
		awt += done[i].waiting;
		atat += done[i].turnaround;
	}
	awt /= n;
	atat /= n;
	printf("Average waiting time is: %.2f\n", awt);
	printf("Average turnaround time is: %.2f\n", atat);
	printf("Total time for which CPU was idle is: %d", idle);
}
