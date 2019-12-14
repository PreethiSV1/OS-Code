//
//  optimal_replacement.c
//  
//
//  Created by Preethi on 17/04/19.
//

#include <stdio.h>
#include <stdlib.h>

// search whether a particular number is present in the frames
int search (int number, int frameCapacity, int frames[]) {
    
    int i;
    for (i = 0; i < frameCapacity; i++)
        if (frames[i] == number)
            return 1;
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

//finds the optimal number (not required presently) in the frames and returns its index.
int findOptimal (int refstr[], int position, int refStrSize, int frames[], int frameNumber) {
    
    int i, j, max, chosen, use[frameNumber];
    for (i = 0; i < frameNumber; i++) {
        
        // find the later to be used index (after the current position) in reference string for each number in the frames
        
        use[i] = 999; //if number is never required later, 999 is assigned.
        
        for (j = position+1; j < refStrSize; ++j) {
            
            if (refstr[j] == frames[i]) {
                use[i] = j;
                break;
            }
        }
    }
    
    //find the maximum of all the use values & find its index - ie the index of value that is not required for now.
    max = use[0], chosen = 0;
    for (i = 1; i < frameNumber; i++)
    {
        if (max < use[i])
        {
            max = use[i];
            chosen = i;
        }
    }
    return chosen;
}


// returns the number of page faults after doing page replacement by Optimal algorithm
int optimalReplacement (int refStr[], int refStrSize, int frameCapacity) {
    
    printf("\n Optimal Replacement with %d frames \n\n", frameCapacity);
    int i, j, frames[frameCapacity];
    
    // set -1 to all frames indicating that all are empty (-1)
    for (i = 0; i < frameCapacity; i++)
    {
        frames[i] = -1;
    }
    
    int pageFaultCount = 0, changeMe = 0;
    for (i = 0; i < refStrSize; i++) {
        
        if (search(refStr[i], frameCapacity, frames) == 0)
        {
            
            if (frames[frameCapacity-1] == -1) {
                for (j = 0; j < frameCapacity; j++)
                    if (frames[j] == -1)
                    {
                        changeMe = j;
                        break;
                    }
            }
            
            else {
                changeMe = findOptimal (refStr, i, refStrSize, frames, frameCapacity);
            }
            frames[changeMe] = refStr[i];
            pageFaultCount++;
            printFrame(pageFaultCount, frames, frameCapacity);
            
        }
    }
    
    printf("\nPage Faults : %d\n\n",pageFaultCount);
    return pageFaultCount;
}

//Driver function
int main() {
    
    int refStrSize, frameCapacity, pageFault[5];
    //int refStr[20] = {1,2,3,2,3,1,4,5,3,6,8,9,4,7,3,2,0,8,6,5};

    // Getting user input for size and values of reference string
    
    printf("Enter size of reference string : ");
    scanf("%d",&refStrSize);
    
    int refStr[refStrSize];
    
    printf("Enter values in the reference string : \n");
    for (int i = 0; i < refStrSize; ++i)
    {
        scanf("%d",&refStr[i]);
    }
    //Using Optimal algorithm and finding number of page faults for each frame capacity
    
    for(frameCapacity = 4; frameCapacity <= 6; frameCapacity++)
    {
        pageFault[frameCapacity-3] = optimalReplacement(refStr, refStrSize, frameCapacity);
    }
    
    // Output number of page faults for each frame capacity from 3 to 7
    
    printf("Number of Frames \t Page Faults \n");
    for (frameCapacity = 4; frameCapacity <= 6; frameCapacity++)
    {
        printf("\t %d \t \t %d \n",frameCapacity, pageFault[frameCapacity-3]);
    }
}
