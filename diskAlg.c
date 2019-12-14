//
//  diskAlg.c
//  
//
//  Created by Preethi on 23/04/19.
//

#include <stdio.h>
#include <stdlib.h>

int search (int array[], int size, int number) {
    
    for (int i = 0; i < size; i++)
        if (array[i] == number)
            return 1;
    return 0;
    
}

void fcfs(int requests[], int num, int head) {
    
    int i, temp = head, seekOperations = 0;
    
    printf("Seek Sequence : %d\t",temp);
    
    for (i = 0; i < num; i++) {
        
        seekOperations = seekOperations + abs(temp - requests[i]);
        temp = requests[i];
        printf("%d\t",temp);
    }
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
}


void sstf(int requests[], int num, int head) {
    
    int i, min, dummy, temp = head, seekOperations = 0;
    
    for (i = 0; i < num; i++) {
        
        min = abs(temp - requests[i]);
        for (int j = i+1; j < num; j++) { //check for minimum seek time in the remaining requests
            
            if (abs(temp - requests[j]) < min)
            {
                min = abs(temp - requests[j]);
                // swap
                dummy = requests[j];
                requests[j] = requests[i];
                requests[i] = dummy;
            }
        }
        temp = requests[i];
        
    }
    
    temp = head;
    printf("Seek Sequence : %d\t",temp);
    
    for (i = 0; i < num; i++) {
        
        seekOperations += abs(temp - requests[i]);
        temp = requests[i];
        printf("%d\t",temp);
    }
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
    
}

void scan(int requests[], int num, int head) {
    
    int i, minimum, maximum, temp = head, seekOperations = 0;
    
    printf("Enter the minimum and maximum limit : ");
    scanf("%d %d",&minimum, &maximum);
    
    printf("Seek Sequence : %d\t",temp);
    
    // move to left end
    for (i = head-1; i >= minimum; i--) {
        
        if (search(requests, num, i) || i == minimum) {
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
    
    }
    
    // reverse and move to right end
    for (i = head+1; i <= maximum; i++) {
        
        if (search(requests, num, i)) {
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
        
    }
    
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
}

void cscan(int requests[], int num, int head) {
    
    int i, minimum, maximum, temp = head, seekOperations = 0;
    
    printf("Enter the minimum and maximum limit : ");
    scanf("%d %d",&minimum, &maximum);
    
    printf("Seek Sequence : %d\t",temp);
    
    // move to left end
    for (i = head-1; i >= minimum; i--) {
        
        if (search(requests, num, i) || i == minimum) {
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
        
    }
    seekOperations += maximum - minimum; // circular scan jumps from 0 to max.
    temp = maximum;

    // rotate and move from right to left
    for (i = maximum-1; i > head; i--) {
        
        if (search(requests, num, i)) {
            
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
    }
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
}


void look(int requests[], int num, int head) {
    
    int i, minimum, maximum, temp = head, seekOperations = 0;
    
    printf("Enter the minimum and maximum limit : ");
    scanf("%d %d",&minimum, &maximum);
    
    printf("Seek Sequence : %d\t",temp);
    
    // move to left end
    for (i = head-1; i >= minimum; i--) {
        
        if (search(requests, num, i)) {
            
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
        
    }
    
    // reverse and move to right end
    for (i = head+1; i <= maximum; i++) {
        
        if (search(requests, num, i)) {
            
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
        
    }
    
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
}

void clook(int requests[], int num, int head) {
    
    int i, minimum, maximum, min, max, temp = head, seekOperations = 0, flag = 0;
    
    printf("Enter the minimum and maximum limit : ");
    scanf("%d %d",&minimum, &maximum);
    
    printf("Seek Sequence : %d\t",temp);
    
    // move to left end
    for (i = head-1; i >= minimum; i--) {
        
        if (search(requests, num, i)) {
            
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
    }
    min = temp; // circular look jumps from left end to right end.
    
    // rotate and move from right to left
    for (i = maximum-1; i > head; i--) {
        
        if (search(requests, num, i)) {
            
            if (flag != 0) {
                
                max = i;
                seekOperations += (max - min);
                flag = 1;
            }
            seekOperations += abs(temp - i);
            temp = i;
            printf("%d\t",temp);
        }
    }
    
    printf("\nNumber of Seek Operations = %d\n",seekOperations);
}

int main() {
    
    int num, head;
    printf("Enter the number of requests : ");
    scanf("%d",&num);
    int requests[num];
    for (int i = 0; i < num; i++) {
        scanf("%d",&requests[i]);
    }
    printf("Enter initial head position : ");
    scanf("%d",&head);
    
    printf("\n FCFS \n");
    fcfs(requests, num, head);
    
    printf("\n SSTF \n");
    sstf(requests, num, head);
    
    printf("\n SCAN \n");
    scan(requests, num, head);
    
    printf("\n CSCAN \n");
    cscan(requests, num, head);
    
    printf("\n LOOK \n");
    look(requests, num, head);
    
    printf("\n CLOOK \n");
    clook(requests, num, head);

}
