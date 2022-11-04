#include <unistd.h>
#include <stdio.h>
#include "header.h"
#include <sys/time.h>

int 
	current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long int milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}


void 
*check_death(
	t_list *philo_inf)
{
	while (1)
	{
		if (philo_inf->time_to_die <= current_timestamp() - philo_inf->ctime)
		{
			philo_died(philo_inf);
			exit(-1);
		}
	}
}

void 
checkeat(
	t_list *philo)
{
	if ((philo->f_control > philo->nphilo))
	{
		printf("round ended\n");
		exit(1);
	}
}

void
	*routinee(
	void *philo_inf)
{
	t_list *p = (t_list*)philo_inf;

	p->ctime = current_timestamp() ;

	int i = p->i;

	while (1)
	{
		pthread_mutex_lock(&p->chopstick[(i + 1) % p->nphilo]);

		printf("%d take fork \n",i);

		pthread_mutex_lock(&p->chopstick[i]);

		printf("%d take fork \n",i);

		printf("%d  start eating \n",i);

		usleep(p->time_to_eat *  1000);

  		pthread_mutex_unlock(&p->chopstick[(i + 1) % p->nphilo]);

		pthread_mutex_unlock(&p->chopstick[i]);

		usleep(p->time_to_sleep *  1000);

		pthread_mutex_lock(&p->mutexx);

		printf("%d  start thinking \n",i);

		pthread_mutex_unlock(&p->mutexx);
	}
	return 0;
}

void 
init_that_shit(
	char **argv, 
	t_list *philost )
{
	philost->nphilo = ft_atoi(argv[1]);
	philost->time_to_die = ft_atoi(argv[2]);
	philost->time_to_eat = ft_atoi(argv[3]);
	philost->time_to_sleep = ft_atoi(argv[4]);
	philost->timest = 0;
	philost->f_control = 0;
	philost->ctime = 0;
}

int
main(
	int argc ,
	char **argv )
{
	t_list philost;
	if (argc == 4 || argc == 5)
	{
		init_that_shit(argv,&philost);
	}
	else
	{
		printf("args error \n");
		exit(-1);
	}
	int i = 0;

	philost.chopstick = malloc(sizeof(pthread_mutex_t) * (philost.nphilo + 1));
	if (!philost.chopstick)
		return (-1);
	pthread_mutex_init(&philost.mutexx, NULL);
	if (philost.chopstick)
	{
		while(i < philost.nphilo)
		{
			pthread_mutex_init(&philost.chopstick[i], NULL);
			i++;
		}
	}	
	else
	{
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	philost.timest = current_timestamp();
	printf("number of philos : %d \n",philost.nphilo);
	printf("time to die : %d \n",philost.time_to_die);
	printf("time toclea eat : %d \n",philost.time_to_eat);
	printf("time to sleep: %d \n",philost.time_to_sleep);
	printf("number of rounds : %s \n",argv[5]);
	philost.i = 0;
	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo + 1);
	if (!philost.p_philo)
		return (-1);
	while (philost.i < philost.nphilo)
	{
		pthread_create(&philost.p_philo[philost.i], NULL, routinee, &philost);
		usleep(50);
		philost.i++;
	}
	while(1)
	{
		usleep(500);
	}
	
}