#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int executeCommand(char *command, char** args)
{
    for(int i = 0; i < 20; i++)
    {
        args[i] = strsep(&command, " ");
        if(args[i] == NULL)
            break;
    }
    if(strcmp(args[0], "exit") == 0)
        return -1;
    
    pid_t pid = fork();
    
    if (pid == -1)
        printf("fork error\n");
    
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            printf("Exec error\n");
    }
    else
    {
        int childStatus;
        waitpid(pid, &childStatus, 0);
    }
    return 0;
}

int main()
{
    char command[1000];
    char* args[100];
    while(1)
    {
        printf("\nShell@preethi >> ");
        gets(command);
        if (executeCommand(command,args) == -1)
            break;
    }
    return 0;
}
