#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct totalProcess {
	int id, bt, at, wt, tat, pri;
};

int comparator1(const void *p, const void *q) {
	int l = ((struct totalProcess *)p)->at;
	int r = ((struct totalProcess *)q)->at;
	if(l == r) {
		int ll = ((struct totalProcess *)p)->pri;
		int rr = ((struct totalProcess *)q)->pri;
		return (ll - rr);
	}
	return (l - r);
}

int comparator2(const void *p, const void *q) {
	int l = ((struct totalProcess *)p)->id;
	int r = ((struct totalProcess *)q)->id;
	return (l - r);
}

void getAvgTime(int n, struct totalProcess arr[]) {
	int i;

	qsort((void *) arr, n, sizeof(struct totalProcess), comparator1);
	arr[0].wt = 0;

	printf("The execution order will be: \n");
	for(i = 0; i < n; ++i) {
		printf("%d -> ", arr[i].id);
	}

	printf("\n\n");

	for(int i = 1; i < n; ++i) {
		arr[i].wt = arr[i - 1].bt + arr[i - 1].wt;
	}
	qsort((void *) arr, n, sizeof(struct totalProcess), comparator2);

	for(i = 0; i < n ; ++i) {
		arr[i].tat = arr[i].bt + arr[i].wt;
	}

	printf("Process  |  WaitngTime  |  TurnAroundTime\n");

	int sum_wt = 0, sum_tat = 0; 
	for(i = 0 ; i < n; ++i) {
		sum_wt = sum_wt + arr[i].wt;
		sum_tat = sum_tat + arr[i].tat;
		printf(" %d.\t\t%d\t\t%d\n", i, arr[i].wt, arr[i].tat);
	}

	printf("Average waiting time: %.3f\n& Average Turn-Around time: %.3f\n", ((float)sum_wt / (float)n), ((float)sum_tat / (float)n));
} 

int main() {
	printf("Enter number of processes: ");
	int n;
	scanf("%d", &n);

	struct totalProcess *arr = (struct totalProcess *) malloc(sizeof(struct totalProcess) * n);

	printf("Enter burst time, arrival and priority time for each process:\n");
	for(int i = 0; i < n; ++i) {
		printf("P%d: ", i);
		scanf("%d%d%d", &arr[i].bt, &arr[i].at, &arr[i].pri);
		arr[i].id = i;
	}
	printf("\n");
	getAvgTime(n, arr);
	return 0;
}
/*OUTPUT
Enter number of processes: 5
Enter burst time, arrival and priority time for each process:
P0: 10 0 3
P1: 1 2 1
P2: 2 3 3
P3: 1 6 4
P4: 5 7 2

The execution order will be: 
0 -> 1 -> 2 -> 3 -> 4 -> 

Process  |  WaitngTime  |  TurnAroundTime
 0.		0		10
 1.		10		11
 2.		11		13
 3.		13		14
 4.		14		19
Average waiting time: 9.600
& Average Turn-Around time: 13.400
*/

