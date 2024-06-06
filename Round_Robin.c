#include "stdio.h"
#include <conio.h>

void main()
{
    int i, numberofprocess, sum=0,count=0, j, quantum, wait_time=0, turn_ard_time=0, processes[10], 
    arrival_time[10], burst_time[10], temp[10], swap=0, counter_time=0, counter_switch=0, total_switch=0;
    float wait_content, avg_wait_time, avg_turn_ard_time,throughput;
    printf("Total number of processes in the system: ");
    scanf("%d", &numberofprocess);

    printf("\nEnter the arrival and burst time for each process\n");
    for(i=0; i<numberofprocess; i++){

        printf("\nArrival time of process[%d]: ", i+1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time of process[%d]: ", i+1);
        scanf("%d", &burst_time[i]);
        processes[i] = i+1;
    }

    for(i=0;i<numberofprocess-1;i++)
    {
        for(j=0;j<numberofprocess-1;j++)
        {
            if(arrival_time[j]>arrival_time[j+1])
            {
                swap=processes[j+1];
                processes[j+1]=processes[j];
                processes[j]=swap;
                swap=arrival_time[j+1];
                arrival_time[j+1]=arrival_time[j];
                arrival_time[j]=swap;
                swap=burst_time[j+1];
                burst_time[j+1]=burst_time[j];
                burst_time[j]=swap;
            }
        }
    }

    printf("\nEnter the desired time quantum for the process: ");
    scanf("%d", &quantum);
    printf("\nProcess No\t\tBurst Time\t\tCompletion Time\t\tTurnaround Time\t\tWaiting Time ");

    for(i = 0; i < numberofprocess; i++){
        temp[i] = burst_time[i];
    }

    for(i = 0; i < numberofprocess; i++){
        counter_time =burst_time[i];
        wait_content = (float)counter_time/(float)quantum;
        if(wait_content<=1.0){
            counter_switch++;

        }
        if(wait_content>1.0){
            counter_switch = counter_switch+(int)wait_content;
        }

    }

    for(int l = 0, sum=0,  j = numberofprocess; j!=0;){

        if (arrival_time[0] !=  0 && sum == 0){
            sum = sum + arrival_time[0];
        }
        if(temp[l] <= quantum && temp[l] > 0){
            sum = sum + temp[l];
            temp[l] = 0;
            count=1;
        }
        else if(temp[l] > 0){
            temp[l] = temp[l] - quantum;
            sum = sum + quantum;
        }
        if(temp[l]==0 && count==1){
            j--;
            printf("\nP[%d]\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d", processes[l], burst_time[l], sum, sum-arrival_time[l], sum-arrival_time[l]-burst_time[l]);
            wait_time = wait_time + sum-arrival_time[l] - burst_time[l];
            turn_ard_time = turn_ard_time + sum - arrival_time[l];
            count =0;

        }
        if(l==numberofprocess-1){
            l=0;

        }
        else if(arrival_time[l+1]<=sum){
            l++;
        }
        total_switch = sum+ counter_switch;
    }

    throughput = (float)numberofprocess/(float)total_switch;
    avg_wait_time = wait_time * 1.0/numberofprocess;
    avg_turn_ard_time = turn_ard_time * 1.0/numberofprocess;
    printf("\n\nAverage Turn Around Time: %.2f ms", avg_turn_ard_time);
    printf("\nAverage Waiting Time: %.2f ms", avg_wait_time);
    printf("\nThroughput = %.3f processes/ms", throughput);
}
