#include<stdio.h>
#include<stdlib.h>

void accept(int A[][10],int N[][10],int M[10][10],int R[10],int *n,int *m){
    int i,j;
    printf("\nEnter total no. of processes and resources : ");
    scanf("%d %d",n,m);
    
    printf("\nEnter available resources : \n");
    for(i=0;i<*m;i++)
    {
        scanf("%d",&R[i]);
    }
    
    printf("\nEnter values for Allocated matrix : \n");
    for (i=0; i<*n; i++)
        for (j=0; j<*m; j++)
            scanf("%d",&A[i][j]);
    
    printf("\nEnter values for Maximum matrix : \n");
    for (i=0; i<*n; i++)
        for (j=0; j<*m; j++)
            scanf("%d",&M[i][j]);
    
    
    printf("\n Need Matrix : \n");
    for(i=0;i<*n;i++)
    {    for(j=0;j<*m;j++)
    {
        N[i][j]=M[i][j]-A[i][j];
        printf("%d\t",N[i][j]);
    }
        printf("\n");
    }
    
}

//Safety algorithm
int safety(int A[][10],int N[][10],int AV[10],int n,int m,int a[]){
    
    int i,j,k,x=0;
    int F[10],R[10];
    int pflag=0,flag=0;
    for(i=0;i<n;i++)
        F[i]=0;
    for(i=0;i<m;i++)
        R[i]=AV[i];
    
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            if(F[i] == 0)
            {
                flag=0;
                for(j=0;j<m;j++)
                {
                    if(N[i][j] > R[j])
                        flag=1;
                }
                if(flag == 0 && F[i] == 0)
                {
                    for(j=0;j<m;j++)
                        R[j]+=A[i][j];
                    F[i]=1;
                    pflag++;
                    a[x++]=i;
                }
            }
        }
        if(pflag == n)
            return 1;
    }
    return 0;
}


int banker(int A[][10],int N[][10],int R[10],int n,int m)
{
    int j,i,a[10];
    j=safety(A,N,R,n,m,a);
    if(j != 0 )
    {
        printf("\n\n");
        printf("\n The safety sequence is : \n");
        for(i=0;i<n;i++)
            printf(" P%d  ",a[i]);
        return 1;
    }
    else
    {
        printf("\n Deadlock has occured.\n");
        return 0;
    }
}



int main()
{
    int A[10][10], M[10][10], N[10][10], R[10];
    int n,m,pid;
    accept(A,N,M,R,&n,&m);
    banker(A,N,R,n,m);
    return 0;
}
