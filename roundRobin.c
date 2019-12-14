#include<stdio.h>
struct process
{
    int name,at,ct,bt,wt,tt,rt;
    int completed;
}p[10];

typedef struct process Process;
int n, q[10], front=-1, rear=-1;

void enqueue(int i)
{
    if(rear==10)
    {
        printf("overflow");
        return;
    }
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;
}

int dequeue()
{
    if(front==-1)
    {
        printf("underflow");
        return 0;
    } 
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
        return temp;
}

int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return 1;
    }
    return 0;
}

void sortByArrival()
{
    Process temp;
    int i,j;
    for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++)
    {
         if(p[i].at>p[j].at)
         {
              temp=p[i];
              p[i]=p[j];
              p[j]=temp;
         }
    }
}

void main()
{
    int i,j,time=0,sum_bt=0,tq;
    char c;
    float avgwt=0,avgtat=0;
    printf("Enter no of processes : ");
    scanf("%d",&n);
    for(i=0;i<n;i++,c++)
    {
         p[i].name=i+1;
         printf("\nEnter the arrival time and burst time of process %d : ",p[i].name);
         scanf("%d%d",&p[i].at,&p[i].bt);
         p[i].rt=p[i].bt;
         p[i].completed=0;
         sum_bt+=p[i].bt;
    }

    printf("\nEnter the time quantum : ");
    scanf("%d",&tq);
    
    sortByArrival();
    enqueue(0);          // enqueue the first process
    printf("Process execution order : ");
    for(time=p[0].at;time<sum_bt;)       // run until the total burst time reached
    {   
        i=dequeue();
       
        if(p[i].rt<=tq)
        {                          // for processes having remaining time with less than or equal time quantum
            time+=p[i].rt;
            p[i].rt=0;
            p[i].completed=1;         
            printf(" %d ",p[i].name);
            p[i].ct = time;
            p[i].wt= time-p[i].at-p[i].bt;
            p[i].tt= time-p[i].at;     
            for(j=0;j<n;j++)                // enqueue the processes which have come while scheduling
            {
                if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
         else               // more than time quantum
         {
          time+=tq;
          p[i].rt-=tq;
          printf(" %d ",p[i].name);
          for(j=0;j<n;j++)             //enqueue the processes which have come scheduling first
                {
                     if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                      {
                        enqueue(j);
                      }
                }
               enqueue(i);   // then enqueue the uncompleted process
         }
    }
    
    printf("\nName\tAT\tBT\tCT\tWT\tTAT");
    for(i=0;i<n;i++)
    {
        avgwt+=p[i].wt;
        avgtat+=p[i].tt;
        printf("\n%d\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tt);
    }
    printf("\nAverage WT:%f",avgwt/n);
    printf("\nAverage TAT:%f\n",avgtat/n);

}
