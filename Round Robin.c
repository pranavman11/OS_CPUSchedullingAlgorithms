#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct totalProcess {
	int id, at, bt, rem, wt, tat, ct;
};

typedef struct totalProcess Process;

void getAvgWaitingTime(Process arr[], int n, int quantum) {
	int sum_wt = 0, sum_tat = 0, i;

	int *sub_at = (int *) malloc(sizeof(int) * n);
	for(i = 0; i < n; i++) {
		arr[i].rem = arr[i].bt;
		sub_at[i] = arr[i].at;
	}
	printf("The Sequence is: ");
	int time = 0;
	while(1) {
		bool flag = true;
		for(i = 0; i < n; i++) {
			if(sub_at[i] <= time) {
				if(sub_at[i] <= quantum) {
					if(arr[i].rem > 0) {
						flag = false;
						if(arr[i].rem > quantum) {
							time += quantum;
							arr[i].rem = arr[i].rem - quantum;
							sub_at[i] = sub_at[i] + quantum;
							printf(" %d", arr[i].id);
						}
						else {
							time += arr[i].rem;
							arr[i].tat = time - arr[i].at;
							arr[i].wt = arr[i].tat - arr[i].bt;
							arr[i].rem = 0;
							printf(" %d", arr[i].id);
						}
					}
				}
				else if(sub_at[i] > quantum) {
					for(int j = 0; j < n; j++) {
						if(sub_at[j] < sub_at[i]) {
							if(arr[j].rem > 0) {
								flag = false;
								if(arr[j].rem > quantum) {
									time += quantum;
									arr[j].rem = arr[j].rem - quantum;
									sub_at[j] = sub_at[j] + quantum;
									printf(" %d", arr[j].id);
								}
								else {
									time += arr[j].rem;
									arr[j].tat = time - arr[j].at;
									arr[j].wt = arr[j].tat - arr[j].bt;
									arr[j].rem = 0;
									printf(" %d", arr[j].id);
								}
							}
						}
					}
					if(arr[i].rem > 0) {
						flag = false;
						if(arr[i].rem > quantum) {
							time += quantum;
							arr[i].rem = arr[i].rem - quantum;
							sub_at[i] = sub_at[i] + quantum;
							printf(" %d", arr[i].id);
						}
						else {
							time += arr[i].rem;
							arr[i].tat = time - arr[i].at;
							arr[i].wt = arr[i].tat - arr[i].bt;
							arr[i].rem = 0;
							printf(" %d", arr[i].id);
						}
					}
				}
			}
			else if(sub_at[i] > time) {
				time++;
				i--;
			}
		}
		if(flag) {
			break;
		}
	}
	printf("\n\nProcess  |  WaitngTime  |  TurnAroundTime\n");

	for(i = 0 ; i < n; ++i) {
		sum_wt = sum_wt + arr[i].wt;
		sum_tat = sum_tat + arr[i].tat;
		printf(" %d.\t\t%d\t\t%d\n", i, arr[i].wt, arr[i].tat);
	}

	printf("Average waiting time: %.3f\n", (float)sum_wt / n);
	printf("& Average Turn-Around time: %.3f\n",(float)sum_tat / n);
}

int main() {
	printf("Enter number of processes: ");
	int n, i;
	scanf("%d", &n);

	Process *arr = (Process *) malloc(sizeof(Process) * n);

	printf("Enter burst time and arrival time for each process:\n");
	for(i = 0; i < n; ++i) {
		printf("P%d:\t", i);
		scanf("%d%d", &arr[i].bt, &arr[i].at);
		arr[i].id = i;
		arr[i].rem = arr[i].bt;
	}

	printf("Enter the time quantum: ");
	int quantum;
	scanf("%d", &quantum);
	printf("\n");

	getAvgWaitingTime(arr, n, quantum);
	return 0;
}
/*OUTPUT
Enter number of processes: 5
Enter burst time and arrival time for each process:
P0:	10 0
P1:	1 2
P2:	2 3
P3:	1 6
P4:	5 7
Enter the time quantum: 2

The Sequence is:  0 1 0 2 0 3 0 4 0 4 4

Process  |  WaitngTime  |  TurnAroundTime
 0.		6		16
 1.		0		1
 2.		2		4
 3.		3		4
 4.		7		12
Average waiting time: 3.600
& Average Turn-Around time: 7.400
*/
