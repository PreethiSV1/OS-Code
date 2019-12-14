//
//  page_replacement.c
//  
//
//  Created by Preethi on 15/04/19.
//

#include <stdio.h>

int search (int number, int frameNumber, int frames[]) {
    
    int i;
    for (i = 0; i < frameNumber; i++)
        if (frames[i] == number)
            return 1;
    return 0;
    
}

void fifo(int refstr[], int pages, int frameNumber) {

    int i, frames[frameNumber];
    for (i = 0; i < frameNumber; i++)
        frames[i] = -1;

    
    int pageFaults = 0, changeMe = 0;
    
    for (i = 0; i < pages; i++) {
        
        if (search(refstr[i], frameNumber, frames) == 0)
        {
            frames[changeMe] = refstr[i];
            pageFaults++;
            printf("Page Fault %d  : %d %d %d\n",pageFaults, frames[0],frames[1], frames[2]);
            if (changeMe == frameNumber-1)
                changeMe = 0;
            else
                changeMe++;
        }
        
    }
    printf("\nPage Faults : %d\n",pageFaults);
    
}

int findlru (int refstr[], int position, int pages, int frames[], int frameNumber) {
    
    int i, j, min, chosen, used[frameNumber];
    for (i = 0; i < frameNumber; i++) {
        
        for (j = position; j >= 0; --j) {
            
            if (refstr[j] == frames[i]) {
                
                used[i] = j;
                break;
            }
        }
    }
    min = used[0], chosen = 0;
    for (i = 1; i < frameNumber; i++)
    {
        if (min > used[i])
        {
            min = used[i];
            chosen = i;
        }
    }
    return chosen;
}

int findoptimal (int refstr[], int position, int pages, int frames[], int frameNumber) {
    
    int i, j, max, chosen, use[frameNumber];
    for (i = 0; i < frameNumber; i++) {
        use[i] = 999;
        for (j = position+1; j < pages; ++j) {
            
            if (refstr[j] == frames[i]) {
                use[i] = j;
                break;
            }
        }
    }
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


void lruOrOptimal (int refstr[], int pages, int frameNumber, int method) {

    int i, frames[frameNumber];
    for (i = 0; i < frameNumber; i++)
        frames[i] = -1;
    
    int pageFaults = 0, changeMe = 0;
    for (i = 0; i < pages; i++) {
        
        if (i < frameNumber) {
            
            frames[i] = refstr[i];
            pageFaults++;
            printf("Page Fault %d  : %d %d %d\n",pageFaults, frames[0],frames[1], frames[2]);
            
        }
        
        else if (search(refstr[i], frameNumber, frames) == 0)
        {
            if (method == 0)
                changeMe = findoptimal (refstr, i, pages, frames, frameNumber);
            else
                changeMe = findlru (refstr, i, pages, frames, frameNumber);
                

            frames[changeMe] = refstr[i];
            
            pageFaults++;
            printf("Page Fault %d  : %d %d %d\n",pageFaults, frames[0],frames[1], frames[2]);
        }
        
    }
    printf("\nPage Faults : %d\n",pageFaults);
    
}


int main () {
    
    int refstr[] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4,6, 2, 3, 0, 1};
    int pages = 20, frameNumber = 3;
    
    //int refstr[] = {1, 3, 0, 3, 5, 6, 3};
    //int pages = 7, frameNumber = 3;
    
    printf("\nFIFO Replacement : \n");
    fifo(refstr, pages, frameNumber);
    printf("\nOptimal Replacement : \n");
    lruOrOptimal(refstr, pages, frameNumber, 0); // 0 for Optimal
    printf("\nLRU Replacement : \n");
    lruOrOptimal(refstr, pages, frameNumber, 1); // 1 for LRU
    
}
