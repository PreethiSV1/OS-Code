#include<stdio.h>

int main()

{

	 int at[10],bt[10],rt[10],tat[10],wt[10],ct[10],pt[10],endTime,i,smallest;

	 int remain=0,n,time,sum_wait=0,sum_turnaround=0;

	 printf("Enter no of Processes : ");

	 scanf("%d",&n);

	 for(i=0;i<n;i++)

 	{

		 printf("Enter Arrival Time, Burst Time, Priority for Process %d : ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pt[i]);

		 rt[i]=bt[i];

 	}


	 rt[9]=9999;
	 pt[9]=9999;

	 for(time=0;remain!=n;time++)

	 {

		 smallest=9;

		 for(i=0;i<n;i++)

		 {

			 if(at[i]<=time && pt[i]<pt[smallest] && rt[i]>0)

			 {

			 	smallest=i;

			 }

		 }

		 rt[smallest]--;

		 if(rt[smallest]==0)

		 {

			 remain++;

			 endTime=time+1;
			 
			 ct[smallest] = endTime;

			 tat[smallest] = endTime-at[smallest];

			 wt[smallest] = tat[smallest]-bt[smallest];

			 //printf("\nP[%d]\t|\t%d\t|\t%d",smallest+1,endTime-at[smallest],endTime-bt[smallest]-at[smallest]);

			 sum_wait+=wt[smallest];

			 sum_turnaround+=tat[smallest];
		 }

	 }
	 printf("Process.No\t AT \t BT \t Pr \t CT \t TAT \t WT\n");

	 for (i = 0; i < n; i++)
	 {
	 	printf("P%d\t\t %d \t %d \t %d \t %d \t %d \t %d\n",i+1,at[i],bt[i],pt[i],ct[i],tat[i],wt[i]);

	 }

	 printf("\n\nAverage waiting time = %f\n",sum_wait*1.0/n);

	 printf("Average Turnaround time = %f",sum_turnaround*1.0/n);

	 return 0;

}