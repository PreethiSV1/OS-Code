#include<stdio.h>
#include<stdlib.h>
typedef struct Node Node;
typedef struct Node
{
    int p_no, at, bt, st, ct, tat, wt;
    Node *next;
};

void print(Node *head, int n)
{
    Node *temp = head;
    Node *prev = NULL;
    while(temp!=NULL)
    {
        if(temp==head)
        {
            temp->st = temp->at;
        }
        else
        {
            temp->st = prev->ct;
        }
        temp->ct = temp->st + temp->bt;
        temp->tat = temp->ct - temp->at;
        temp->wt = temp->tat - temp->bt;
        
        prev = temp;
        temp = temp->next;
    }
    
    int totalTAT = 0, totalWT = 0;
    if(head==NULL)
    {
        printf("\nNo entries");
    }
    else
    {
        Node *temp = head;
        printf("Process.No\t AT \t BT \t CT \t TAT \t WT\n");
        while(temp!=NULL)
        {
            printf("P%d\t\t %d \t %d \t %d \t %d \t %d\n",temp->p_no,temp->at,temp->bt,temp->ct,temp->tat,temp->wt);
            totalTAT+=temp->tat;
            totalWT+=temp->wt;
            temp = temp->next;
        }
        printf("Average TAT  = %f\n",(float)totalTAT/n);
        printf("Average WT  = %f\n",(float)totalWT/n);
    }
}



Node* create_node()
{
    Node *new_node = NULL;
    int p_no, at, bt;
    printf("Enter Process No, Arrival Time, Burst Time : ");
    scanf("%d %d %d",&p_no,&at,&bt);
    new_node = (Node *)malloc(sizeof(Node));
    new_node->p_no = p_no;
    new_node->at = at;
    new_node->bt = bt;
    new_node->next = NULL;
    return new_node;
    
}

void insert_at_end(Node **head)
{
    Node *new_node;
    new_node = create_node();
    Node *temp = (*head);
    if((*head)==NULL)
    {
        (*head) = new_node;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new_node;
    }
}

void FCFSsort(Node *head)
{
    int swapped, i;
    Node *p1,*p2 = NULL;
    
    if (head == NULL)
        return;
    
    do
    {
        swapped = 0;
        p1 = head;
        
        while (p1->next != p2)
        {
            if (p1->at > p1->next->at)
            {
                swap(p1, p1->next);
                swapped = 1;
            }
            p1 = p1->next;
        }
        p2 = p1;
    }
    while (swapped);
}

void swap(Node *a, Node *b)
{
    int temp = a->p_no;
    a->p_no = b->p_no;
    b->p_no = temp;
    
    temp = a->at;
    a->at = b->at;
    b->at = temp;
    
    temp = a->bt;
    a->bt = b->bt;
    b->bt = temp;
}


int main()
{
    
    Node *head = NULL;
    int i,n;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        insert_at_end(&head);
    }
    FCFSsort(head);
    print(head, n);
    
}
