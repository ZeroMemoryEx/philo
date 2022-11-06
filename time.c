#include <stdio.h>
#include<sys/time.h>
#include <errno.h>
#include <unistd.h>

int 
	current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long int milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

void ft_sleep(time_t sec)
{

	int tim = current_timestamp();
	while(1)
	{
		int sleep = sec  + tim;
		if (sleep <= current_timestamp())
			break;
		usleep(100);
	}
}

int main()
{
	ft_sleep(4000);
}