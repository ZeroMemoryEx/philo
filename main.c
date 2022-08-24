#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "header.h"

int glob;

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}
long long int getindexbyid(t_list *philos)
{
	int i = 0;
	pthread_t self_id = pthread_self();
	while (philos->p_philo[i] != self_id)
		i++;
	return (i);
}

void philo_take_fork(t_list *philos)
{
	
	printf("philosopher %d has taken fork\n",getindexbyid(philos));
}

void philo_start_eating(t_list *philos)
{
	
	printf("philosopher %d has started eating\n",getindexbyid(philos));
}

void philo_start_thinking(t_list *philos)
{
	
	printf("philosopher %d has started thinking\n",getindexbyid(philos));
}

void philo_died(t_list *philos)
{
	
	printf("philosopher %d has died\n",getindexbyid(philos));
	exit(-1);
}
void *routinee(t_list *philo_inf)
{
	pthread_mutex_lock(&philo_inf->mutexx);

	philo_take_fork(philo_inf);
	pthread_mutex_unlock(&philo_inf->mutexx);
}


void init_that_shit(char **argv, t_list *philost)
{
	philost->nphilo = ft_atoi(argv[1]);
	philost->time_to_die = ft_atoi(argv[2]);
	philost->time_to_eat = ft_atoi(argv[3]);
	philost->time_to_sleep = ft_atoi(argv[4]);
}
int main(int argc , char **argv)
{
	t_list philost;
	if (argc == 4 || argc == 5)
	{
		
		init_that_shit(argv,&philost);
		
		pthread_mutex_init(&philost.mutexx , NULL);
	}
	else
	{
		printf("args error \n");
		exit(-1);
	}

	printf("number of philos : %d \n",philost.nphilo);
	printf("time to die : %d \n",philost.time_to_die);
	printf("time to eat : %d \n",philost.time_to_eat);
	printf("time to sleep: %d \n",philost.time_to_sleep);
	printf("number of rounds : %s \n",argv[5]);

	int i = 0;
	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo);
	while (i < philost.nphilo )
	{
		pthread_create(&philost.p_philo[i],NULL,&routinee,(void*)&philost);
		i++;
	}
	i = 0;
	while (i < philost.nphilo)
	{
		pthread_join(philost.p_philo[i],NULL);
		i++;
	}
	
}
