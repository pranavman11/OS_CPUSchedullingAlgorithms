//FCFS
#include <stdio.h>
#include <stdlib.h>

void getAvgTime(int n, int bt[], int at[]) {
	int *wt = (int *) malloc(sizeof(int) * n), *tat = (int *) malloc(sizeof(int) * n), i;
	int *rt = (int *) malloc(sizeof(int) * n);

	rt[0] = 0;
	wt[0] = 0;

	for(i = 1; i < n ; i++) {
		rt[i] = rt[i - 1] + bt[i - 1];
		wt[i] = rt[i] - at[i];
		if(wt[i] < 0) {
			wt[i] = 0;
		}
	}

  	for(i = 0; i < n ; i++) {
		tat[i] = bt[i] + wt[i]; 
	}

  	printf("Process  |  WaitngTime  |  TurnAroundTime\n");

	int sum_wt = 0, sum_tat = 0; 
	for(i = 0 ; i < n ; i++) {
		sum_wt = sum_wt + wt[i];
		sum_tat = sum_tat + tat[i];
		printf(" %d.\t\t%d\t\t%d\n", i, wt[i], tat[i]);
	}

	printf("Average waiting time: %.3f\n& Average Turn-Around time: %.3f\n", ((float)sum_wt / (float)n), ((float)sum_tat / (float)n));
} 

int main() {
	printf("Enter number of processes: ");
	int n;
	scanf("%d", &n);

	int *burst_time = (int *) malloc(sizeof(int) * n);
	int *arrival_time = (int *) malloc(sizeof(int) * n);

	printf("Enter burst time and arrival time for each process:\n");
	for(int i = 0; i < n; ++i) {
		printf("P%d: ", i);
		scanf("%d%d", &burst_time[i], &arrival_time[i]);
	}
	printf("\n");
	getAvgTime(n, burst_time, arrival_time);
	return 0;
}
/*OUTPUT
Enter number of processes: 5
Enter burst time and arrival time for each process:
P0: 10 0
P1: 1 2
P2: 2 3
P3: 1 6
P4: 5 7 

Process  |  WaitngTime  |  TurnAroundTime
 0.		0		10
 1.		8		9
 2.		8		10
 3.		7		8
 4.		7		12
Average waiting time: 6.000
& Average Turn-Around time: 9.800
*/
