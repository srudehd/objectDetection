#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(void)
{
        pid_t ppid;

        ppid = getppid();

        while(1)
        {
                printf("HI\n");
                kill(ppid,SIGUSR1);
                sleep(1);
        }
        return 0;
}

