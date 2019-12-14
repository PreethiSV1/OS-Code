//
//  lru_replacement.c
//  
//
//  Created by Preethi on 17/04/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// search whether a particular number is present in the frames
int search (int number, int frameCapacity, int frames[]) {
    
    int i;
    for (i = 0; i < frameCapacity; i++) {
        if (number == frames[i]) {
            return 1;
        }
    }
    return 0;
}

// prints the contents of the frames after a particular page fault
void printFrame (int pageFaultCount, int frames[], int frameCapacity) {
    
    int i;
    printf("Page Fault %d :", pageFaultCount);
    for (i = 0; i < frameCapacity; ++i)
        printf ("\t%d",frames[i]);

    printf("\n");
    
}

//finds the Least recently used number in the frames and returns its index.
int findLRU (int refStr[], int position, int refStrSize, int frames[], int frameCapacity) {
    
    int i, j, min, chosen, used[frameCapacity];
    for (i = 0; i < frameCapacity; i++) {
        
        // find the previously used index (before the current position) in reference string for each number in the frames
        for (j = position; j >= 0; --j) {
            
            if (refStr[j] == frames[i]) {
                
                used[i] = j;
                break;
            }
        }
    }
    
    //find the minimum of all the used values & find its index - ie that is the least recently used index.
    min = used[0], chosen = 0;
    for (i = 1; i < frameCapacity; i++)
    {
        if (min > used[i])
        {
            min = used[i];
            chosen = i;
        }
    }
    return chosen;
}

// returns the number of page faults after doing page replacement by LRU algorithm
int lruReplacement (int refStr[], int refStrSize, int frameCapacity) {
    
    printf("\n LRU Replacement with %d frames \n\n", frameCapacity);
    int i, j, frames[frameCapacity];
    
    // set -1 to all frames indicating that all are empty (-1)
    for (i = 0; i < frameCapacity; i++)
    {
        frames[i] = -1;
    }
    int pageFaultCount = 0, changeMe = 0;
    for (i = 0; i < refStrSize; ++i) {
        if ((search(refStr[i], frameCapacity, frames) == 0))
        {
            if (frames[frameCapacity-1] == -1) {
                
                for (j = 0; j < frameCapacity; j++) {
                    if (frames[j] == -1)
                    {
                        changeMe = j;
                        break;
                    }
                    
                }
            }
            else {
                changeMe = findLRU (refStr, i, refStrSize, frames, frameCapacity);
            }
            frames[changeMe] = refStr[i];
            pageFaultCount++;
            printFrame(pageFaultCount, frames, frameCapacity);
            
        }
        
    }
    printf("\nPage Faults : %d\n\n",pageFaultCount);
    return pageFaultCount;
}

//function to generate reference string of size refStrSize with random values from 0 to 9
void generateRefStr (int refStrSize, int refStr[]) {
    
    srand(time(0));
    int i;
    printf("Randomly generated Reference String : ");
    for (i = 0; i < refStrSize; i++) {
        
        refStr[i] = rand() % 10; // converts random value to a value between 0 and 9
        printf(" %d ", refStr[i]);
        
    }
    printf("\n");
}

//Driver function
int main() {
    
    int refStrSize, frameCapacity, pageFault[5];
    
    //int refStr[20] = {1,2,3,2,3,1,4,5,3,6,8,9,4,7,3,2,0,8,6,5};
    
    // input size of reference string and generate reference string with random values.
    
    printf("Enter size of reference string : ");
    scanf("%d",&refStrSize);
    
    int refStr[refStrSize];
    
    generateRefStr(refStrSize, refStr);
    
    //Using LRU algorithm and finding number of page faults for each frame capacity
    
    for(frameCapacity = 1; frameCapacity <= 5; frameCapacity++)
    {
        pageFault[frameCapacity-1] = lruReplacement(refStr, refStrSize, frameCapacity);
    }
    
    // Output number of page faults for each frame capacity from 1 to 5
    
    printf("Number of Frames \t Page Faults \n");
    for (frameCapacity = 1; frameCapacity <= 5; frameCapacity++)
    {
        printf("\t %d \t \t %d\n",frameCapacity, pageFault[frameCapacity-1]);
    }
}
