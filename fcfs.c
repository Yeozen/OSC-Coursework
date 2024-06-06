#include <stdio.h>
int main() {
 int i,j,idle,p;
 int arrival_time[10], burst_time[10],completeTime[10],waitTime[10],turnaroundTime[10],process[10];
 float avg_turn_ard_time=0,avg_wait_time=0,thoughput = 0;

 //get user input for number of processes
 printf("Enter the no process in the system: ");
 scanf("%d",&p);

 //get user input for arrival and burst time of each processes
 printf("\nEnter the arrival and burst time for each process\n");
    for(i=0; i<p; i++){
        process[i] = i+1;
        printf("\nArrival time of process[%d]: ", i+1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time of process[%d]: ", i+1);
        scanf("%d", &burst_time[i]);

    }


//sorting for arrival time
int temp1,temp2,temp3;
 for(int i=0;i<p-1;i++) {
   for(int j=i+1;j<p;j++) {
     if(arrival_time[i]>arrival_time[j]) {
        temp1=process[i];
        process[i]=process[j];
        process[j]=temp1;
        temp2=arrival_time[i];
        arrival_time[i]=arrival_time[j];
        arrival_time[j]=temp2;
        temp3=burst_time[i];
        burst_time[i]=burst_time[j];
        burst_time[j]=temp3;
     }
   }
 }

//check for idle time and add it to completion time
 for(int i=0;i<p;i++) {
  if(i==0) {
   //idle time for p1
   completeTime[i]=burst_time[i]+arrival_time[0];
  } else {
     if(completeTime[i-1]<arrival_time[i]) {
        //idle time between processes
        completeTime[i]=completeTime[i-1]+burst_time[i]+(arrival_time[i]-completeTime[i-1]);
     } else {
        //no idle
        completeTime[i]=completeTime[i-1]+burst_time[i];
       }
   }
 }
printf("\nProcess\t  ArrivalTime\t BurstTime\t CompleteTime\t TurnAroundTime\t  WaitingTime");
//calculate the turnaround time, wait time and their average
 for(int i=0;i<p;i++) {
    turnaroundTime[i]=completeTime[i]-arrival_time[i];
    waitTime[i]=turnaroundTime[i]-burst_time[i];
    avg_turn_ard_time+=turnaroundTime[i];
    avg_wait_time+=waitTime[i];
    thoughput += burst_time[i];
  }
avg_turn_ard_time=avg_turn_ard_time/p;
avg_wait_time=avg_wait_time/p;
thoughput = p/(thoughput+(p-1));


 for(int i=0;i<p;i++) {
  printf("\nP[%d]\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d",process[i],arrival_time[i],burst_time[i],completeTime[i],turnaroundTime[i],waitTime[i]);
 }
  printf("\n\nAverage Turn Around Time: %.2f ms", avg_turn_ard_time);
  printf("\nAverage Waiting Time: %.2f ms", avg_wait_time);
  printf("\nThroughput = %.3f process/ms \n", thoughput);

}
