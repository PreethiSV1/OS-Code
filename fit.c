//
//  fit.c
//  
//
//  Created by Preethi on 15/04/19.
//

#include <stdio.h>

void acceptData (int *m, int *n, int blockSize[10], int processSize[10]) {
    
    int i;
    printf("Enter number of blocks : ");
    scanf("%d",n);
    printf("Enter size of each block : \n");
    for (i = 0; i < *n; ++i)
    {
        scanf("%d",&blockSize[i]);
    }
    printf("Enter number of processes : ");
    scanf("%d",m);
    printf("Enter size of each process : \n");
    for (i = 0; i < *m; ++i)
    {
        scanf("%d",&processSize[i]);
    }
    
}

void printData(int m, int n, int blockSize[10], int processSize[10], int allocated[10] ) {
    
    int i, j;
    printf("Process No.\tProcess Size\tAllocated Block No. and Size\n");
    for (i = 0; i < m; i++) {
        if (allocated[i] == -1)
            printf("%d\t\t%d\t\tNot Allocated\n",i+1,processSize[i]);
        else
            printf("%d\t\t%d\t\t %d\t\t%d\n", i+1, processSize[i], allocated[i]+1, blockSize[allocated[i]]);
        
            
    }
}

void initialize(int m, int n, int allocated[10], int full[10]) {
    
    int i,j;
    for (i = 0; i < m; ++i)
    {
        allocated[i] = -1;
    }
    for (i = 0; i < n; ++i)
    {
        full[i] = 0;
    }
    
}

void firstFit (int m, int n, int blockSize[10], int processSize[10]) {
    
    int i, j, full[n], allocated[m];
    initialize(m,n,allocated,full);
    
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if ((processSize[i] <= blockSize[j]) && (full[j] == 0)) {
                
                full[j] = 1;
                allocated[i] = j;
                break;
            }
        }
    }
    printData(m,n,blockSize,processSize,allocated);
}


int findmin (int i, int n, int blockSize[10], int processSize[10], int full[10]) {
    
    int j, chosen = 9, flag = -1;
    blockSize[chosen] = 10000;
    for (j = 0; j < n; ++j)
    {
        if ((blockSize[j] >= processSize[i]) && (full[j] == 0) && (blockSize[j] <= blockSize[chosen]))
        {
            chosen = j;
            flag = 1;
        }
    }
    
    if (flag == 1)
    {
        
        full[chosen] = 1;
        return chosen;
    }
    else
        return -1;
}

void bestFit (int m, int n, int blockSize[10], int processSize[10]) {
    
    int i, chosen, full[n], allocated[m];
    
    initialize(m,n,allocated,full);
    
    for (i = 0; i < m; ++i) //process
    {
        allocated[i] = findmin(i, n, blockSize, processSize, full);
    }
    printData(m,n,blockSize,processSize,allocated);
    
}

int findmax (int i, int n, int blockSize[10], int processSize[10], int full[10]) {
    
    int j, chosen = 9, flag = -1;
    blockSize[chosen] = 0;
    for (j = 0; j < n; j++)
    {
        if ((blockSize[j] >= processSize[i]) && (full[j] == 0) && (blockSize[j] >= blockSize[chosen]))
        {
            chosen = j;
            flag = 1;
        }
    }
    
    if (flag == 1)
    {
        full[chosen] = 1;
        return chosen;
    }
    else
        return -1;
    
}

void worstFit (int m, int n, int blockSize[10], int processSize[10]) {
    
    int i, chosen, full[n], allocated[m];

    initialize(m,n,allocated,full);
    
    for (i = 0; i < m; ++i) //process
    {
        allocated[i] = findmax(i, n, blockSize, processSize, full);
    }
    printData(m,n,blockSize,processSize,allocated);
    
}

int main () {
    
    int n, m, blockSize[10], processSize[10];
    
    /*int n = 5, m = 4;
    int blockSize[] = {100,500,200,300,600};
    int processSize[] = {212,417,112,426};*/
    
    acceptData(&m, &n, blockSize, processSize);
    printf("\nFirst Fit Algorithm : \n");
    firstFit(m, n, blockSize, processSize);
    
    printf("\nBest Fit Algorithm : \n");
    bestFit(m, n, blockSize, processSize);
    
    printf("\nWorst Fit Algorithm : \n");
    worstFit(m, n, blockSize, processSize);
    
}
