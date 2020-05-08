#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    pid_t  pid = fork();
    switch (pid)
    {
        case -1:
            printf("Error");
            return 0;
        case 0:
            execl("/usr/bin/gnome-terminal", "gnome-terminal", "--", "./child", argv[5], NULL);
            break;
        default:
            printf("PID: %d\n", getpid());
	    time_t T= time(NULL);

    	    struct  tm tm = *localtime(&T);

    	    printf("System Date is: %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    	    printf("System Time is: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);

            wait(&pid);
    }

    return 0;
}
