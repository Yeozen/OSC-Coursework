#include<stdio.h>

struct process
{
    int average_time,burst_time,waiting_time,turn_around_time,remaining_time,CT,number;
}Queue1[10],Queue2[10];//Two queues


int n, context_switches=0;
//sorting it by arrival time
void SortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Queue1[i].average_time>Queue1[j].average_time)
                    {
                          temp=Queue1[i];
                          Queue1[i]=Queue1[j];
                          Queue1[j]=temp;
                    }
            }
    }
}

int main()
{
     int i,j,k=0,r=0,time=0,quantum=5,key=0;
     int total_waiting_time,total_turnaroundtime = 0,total_burstingtime=0;
     //taking the number of processes
     printf("Enter no of processes:");
     scanf("%d",&n);
     for(i=0;i<n;i++)
     {
         //taking the arrival time and burst time
         printf("\nEnter the arrival time of process %d: ",i+1);
         scanf("%d",&Queue1[i].average_time);
         printf("Enter the burst time of process %d: ",i+1);
         scanf("%d",&Queue1[i].burst_time);
         Queue1[i].number = i+1;
         Queue1[i].remaining_time=Queue1[i].burst_time;/*save burst time in remaining time for each process*/
         total_burstingtime+=Queue1[i].burst_time;
    }



//sorting done by taken arrival time
SortByArrival();
if (Queue1[0].average_time != 0){
    total_burstingtime += Queue1[0].average_time;
}
time=Queue1[0].average_time;
printf("\nProcess in first queue following Round Robin with time quantum=5:");
printf("\nProcess\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\t\t");


for(i=0;i<n;i++)
{
//if remaining time is lower than time quantum
  if(Queue1[i].remaining_time<=quantum)
  {

       time+=Queue1[i].remaining_time;//from arrival time of first process to completion of this process
       Queue1[i].remaining_time=0;
       Queue1[i].waiting_time=time-Queue1[i].average_time-Queue1[i].burst_time;//the amount of time process has been waiting in the first queue
       Queue1[i].turn_around_time=time-Queue1[i].average_time;//amount of time to execute the process
       printf("\nP[%d]\t\t%d\t\t\t%d\t\t\t%d",Queue1[i].number,Queue1[i].burst_time,Queue1[i].waiting_time,Queue1[i].turn_around_time);


  }
    else//process moves to queue 2 with FCFS
    {
      Queue2[r].average_time=time;
      time+=quantum;
      Queue2[r].burst_time=Queue1[i].remaining_time;
      Queue2[r].remaining_time=Queue1[r].burst_time;
      Queue2[r].number=Queue1[i].number;
      r=r+1;
      key=2;
      context_switches++;
    }
  }

{if(key==2)
printf("\nProcess in second queue following FCFS: ");
}
for(i=0;i<r;i++)
{
    //taking the remaining time
    if(i==0){
            Queue2[i].CT=Queue2[i].burst_time+time;
    }
        else{
            Queue2[i].CT=Queue2[i-1].CT+Queue2[i].burst_time-quantum;
        }
}

for(i=0;i<r;i++)
    {
        //taking the turn around time from completion time
        Queue2[i].turn_around_time=Queue2[i].CT;
        //taking the waiting time from the difference between turn around time and burst time
        Queue2[i].waiting_time=Queue2[i].turn_around_time-Queue2[i].burst_time;
        printf("\nP[%d]\t\t%d\t\t\t%d\t\t\t%d",Queue2[i].number,Queue2[i].burst_time,Queue2[i].waiting_time,Queue2[i].turn_around_time);


    }

    for(i=0;i<n;i++)
    {
        //calculating the total waiting time
        total_waiting_time += Queue2[i].waiting_time + Queue1[i].waiting_time;
        //calculating the total turnaround time
        total_turnaroundtime += Queue2[i].turn_around_time + Queue1[i].turn_around_time;
    }
        //calculating the average time
        float average_waiting_time = (float)total_waiting_time / (float)n;
        //calculating the average turnaround time
        float average_turnaround_time = (float)total_turnaroundtime / (float)n;
        //calculating the throughput
        float throughput = (float)n/(float)(context_switches+total_burstingtime+(n-1));
        printf("\nAverage waiting time = %.2f ms",average_waiting_time);
        printf("\nAverage turn around time = %.2f ms",average_turnaround_time);
        printf("\nThroughput = %0.3f processes/ms\n",throughput);
}
