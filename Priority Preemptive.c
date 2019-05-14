#include<stdio.h>
#include<stdlib.h>
double curr=0;

struct process{
	int pid;
	double arrivaltime;
	double bursttime;
 	double bursttimecopy;

	double rt;
	int priority;
};
void display(int * arr,double total){
  int i;

  printf("| %d ",arr[0]);
  for(i=1;i<total;i++){
    if(arr[i-1]==arr[i]){
      printf("%d ",arr[i]);
    }else{
      printf("| %d ",arr[i] );
    }
  }
  printf(" |" );
}

int tat(int *arr,int pid,double start,double total){
  int end,diff,i;
  
  for(i=total;i>0;i--){
    if(arr[i]==pid){
      
      end=i;
      break;
    }
  }
  diff=end-start;
  return (diff+1);
}
int minPT(struct process *arr,int n){
	int i;
	int min=9999;
	int mini;
	for(i=0;i<n;i++){
		if(arr[i].priority<min && arr[i].arrivaltime<=curr && arr[i].bursttime>0){
			min=arr[i].priority;
			mini=i;
		}
	}
	
	return mini;
			
}
int main(){
  printf("HIGEST PIORITY FIRST PREEMPTIVE\n\n" );
  double totalwt,totaltat,avgwt,avgtat;
	int no_pro,i,j,start=1,run;
	double total,totalcopy;
	struct process temp;
	struct process *arr;
	int *arrrun;
    printf("enter no of process\n");
    scanf("%d",&no_pro);
    
    arr=(struct process *)malloc(sizeof(struct process)*no_pro);
    for(i=0;i<no_pro;i++){
    	printf("enter pid,arrivaltime,bursttime,priority\n");
      double temp;
    	scanf("%d",&arr[i].pid);
    	scanf("%lf",&arr[i].arrivaltime);
    	scanf("%lf",&temp);
      arr[i].bursttime=temp;
      arr[i].bursttimecopy=temp;
    	scanf("%d",&arr[i].priority);
    	arr[i].rt=arr[i].bursttime;
      arr[i].bursttimecopy=arr[i].bursttime;
    }

    
    for(i=1;i<no_pro;i++){
    	for(j=0;j<i;j++){
    		if(arr[j].arrivaltime>arr[i].arrivaltime){
    			temp=arr[i];
    			arr[i] = arr[j];
    			arr[j]=temp;
    		}
    	}
    }
    
   
    for(i=0;i<no_pro;i++){
    	total+=arr[i].bursttime;
    }
    totalcopy=total;
    
    arrrun=(int *)malloc(sizeof(struct process)*total);
    
    i=0;
    while(total){
    	//printf("starting at time %lf\n",curr);
    	run=minPT(arr,no_pro);
    	arrrun[i]=run+1;
    	i++;
    	arr[run].rt--;
    	arr[run].bursttime--;
    	curr++;
    	total--;
    	if(arr[run].bursttime==0){
    		arr[run].priority=9999;
    	}
    //	printf("running process %d\t at time %lf\n",arr[run].pid,curr);
   	}
    
  
    display(arrrun,totalcopy);
  
    for(i=0;i<no_pro;i++){
      printf("\n process id %d",arr[i].pid);
      int turnaround=tat(arrrun,arr[i].pid,arr[i].arrivaltime,totalcopy);
      totaltat+=turnaround;
      
      int waittime=turnaround-arr[i].bursttimecopy;
      totalwt+=waittime;
      printf("\tturn around time %d",turnaround);
      printf("\twaiting time %d",waittime);

    }
    printf("\naverage waittime is %lf",totalwt/no_pro);
    printf("\naverage turnaround time is %lf\n",totaltat/no_pro);
   	
   	
  
	return 0;
}
/*OUTPUT
HIGEST PRIORITY FIRST PREEMPTIVE

enter no of process
5
enter pid,arrivaltime,bursttime,priority
1 0 10 3
enter pid,arrivaltime,bursttime,priority
2 2 1 1 
enter pid,arrivaltime,bursttime,priority
3 3 2 3
enter pid,arrivaltime,bursttime,priority
4 6 1 4
enter pid,arrivaltime,bursttime,priority
5 7 5 2
| 1 1 | 2 | 1 1 1 1 | 5 5 5 5 5 | 1 1 1 1 | 3 3 | 4  |
 process id 1 turn around time 16 waiting time 6
 process id 2 turn around time 1  waiting time 0
 process id 3 turn around time 15 waiting time 13
 process id 4 turn around time 13 waiting time 12
 process id 5 turn around time 5  waiting time 0
average waittime is 6.200000
average turnaround time is 10.000000
*/
