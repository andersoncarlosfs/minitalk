// https://stackoverflow.com/questions/67985972/how-can-you-send-a-string-given-has-argument-to-a-program-to-another-program-usi
#include <signal.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h>

int size;
int byte; // character

void sighandler(int signum)
{
    int bit;
    
    if(SIGUSR1 == signum)
    {
        bit = 1;
    }
    
    if(SIGUSR2 == signum)
    {
        bit = 0;
    }
    
    if (bit)
    {
        for (int exponent = 0; exponent < size; exponent++)
        {
            bit *= 2; // factors
        }
        
        byte += bit;
    }
    
    if (size++ >= 7)
    {
        if(byte == 0)
        {
            printf("\n");
        }
        else
        {
            printf("%c", byte);
        }
    
        size = 0;
        byte = 0;
    }
}

int main ()
{
    // https://man7.org/linux/man-pages/man2/sigaction.2.html
    // https://www.gnu.org/software/libc/manual/html_node/Blocking-for-Handler.html
    // https://stackoverflow.com/questions/26667734/handling-signals-in-different-ways
    // setting the handlers
    struct sigaction sigactionhandler;
    // blocking the handlers
    sigset_t sigmask;
    
    sigemptyset (&sigmask);
    
    // https://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html
    for (int sig = 0; sig <= SIGSYS; ++sig) /***/
    {
        if (sig != SIGUSR1 && sig != SIGUSR2) /**/
        {
            sigaddset (&sigmask, 0);
        }
    }
    
    sigactionhandler.sa_handler = sighandler;
    sigactionhandler.sa_mask = sigmask;
    sigactionhandler.sa_flags = 0;
    
    printf("%d\n", getpid()); //
    
    size = 0;
    byte = 0;
    
    for(;;) //
    {
        sigaction(SIGUSR1, &sigactionhandler, NULL); /**/
        sigaction(SIGUSR2, &sigactionhandler, NULL); /**/
        pause();
    }
    
    return 0;
}

/* Manage a dynamic list of signals, because you don’t have to predefine the size of an array */
/* Manage SIGRTMAX because it does not exist on Darwin (Mac) */
