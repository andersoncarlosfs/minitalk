#include <signal.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h>

void sighandler(int pid, char *message)
{
    int microseconds;
    int index;
    int size;
    int byte;
    int bit;
    
    while(message[index++] != '\0')
    {
        size++;
    }
    
    microseconds = 1000000 / ((size + 1) * 8); // Time to wait
    
    if (microseconds > 1000)
    {
        microseconds = 500;
    }
    
    index = 0;
    
    while(index < size)
    {
        byte = message[index];
        bit = 7;

        while (bit >= 0)
        {
            if(byte % 2 == 0)
            {
                kill(pid, SIGUSR2);
            }
            else
            {
                kill(pid, SIGUSR1);
            }

            byte = byte / 2;
            
            usleep(microseconds);
            
            bit--;
        }
	    
        index++;
    }
    
    bit = 8;
    
    while (bit--)
    {
        kill(pid, SIGUSR2); // sending null or 0
        
        usleep(microseconds);
    }
}

int main (int argc, char **argv)
{
	if (argc == 3)
    {
        sighandler(atoi(argv[1]), argv[2]); //
    }
	
    exit(EXIT_FAILURE);
}
