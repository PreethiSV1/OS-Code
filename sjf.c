#include<stdio.h>
int main()
{
    int i,j,n,temp;
    
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    
    int p[n],bt[n],at[n],wt[n],tat[n],ct[n],st[n];
    
    for (i = 0; i < n; i++)
    {
        printf("Enter Process No, Arrival Time, Burst Time : ");
        scanf("%d %d %d",&p[i],&at[i],&bt[i]);
    }
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(at[i] < at[j])
            {
                temp=p[j];
                p[j]=p[i];
                p[i]=temp;
                
                temp=at[j];
                at[j]=at[i];
                at[i]=temp;
                
                temp=bt[j];
                bt[j]=bt[i];
                bt[i]=temp;
            }
        }
    }

    for (i = 1; i < n; i++) 
    {
        if(at[i] == at[0])
        {
                if(bt[i] < bt[0])
                {
                    temp=p[0];
                    p[0]=p[i];
                    p[i]=temp;
                    
                    temp=at[0];
                    at[0]=at[i];
                    at[i]=temp;
                    
                    temp=bt[0];
                    bt[0]=bt[i];
                    bt[i]=temp;
                }
        }
        else 
            break;
    }
    
    
    
    int min,k=1,timeC=0;
    for(j=0;j<n;j++)
    {
        timeC=timeC+bt[j];
        min=bt[k];
        for(i=k;i<n;i++)
        {
            if (timeC>=at[i] && bt[i]<bt[k])
            {
                temp=p[k];
                p[k]=p[i];
                p[i]=temp;
                
                temp=at[k];
                at[k]=at[i];
                at[i]=temp;
                
                temp=bt[k];
                bt[k]=bt[i];
                bt[i]=temp;
            }
        }
        k++;
    }
    
    
    for(i = 0; i < n; i++)
    {
        if (i == 0)
            st[i] = at[i];
        else
            st[i] = ct[i-1];
        
        ct[i] = st[i] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    
    
    int totalTAT = 0, totalWT = 0;
    printf("Process.No\t AT \t BT \t CT \t TAT \t WT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t\t %d \t %d \t %d \t %d \t %d\n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
        totalTAT+=tat[i];
        totalWT+=wt[i];
    }
    printf("Average TAT  = %.2f\n",(float)totalTAT/n);
    printf("Average WT  = %.2f\n",(float)totalWT/n);
    
    return 0;
}
