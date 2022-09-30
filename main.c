#include <unistd.h>
#include <stdio.h>
#include "header.h"
       #include <sys/time.h>

int glob;

int current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long int milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}
int getindexbyid(t_list *philos)
{
	int i = 0;
	pthread_t self_id = pthread_self();
	while (i < philos->nphilo)
	{
		
		if (self_id == philos->p_philo[i])
		{

			break;
		}
		i++;
	}
	return (i);
	
}
pthread_mutex_t **chopstick = NULL;

void philo_take_fork(t_list *philos)
{
	pthread_mutex_lock(&philos->mutexx);
	printf("%d philosopher %d has taken fork\n",current_timestamp() - (int)philos->ctime ,getindexbyid(philos));
	pthread_mutex_unlock(&philos->mutexx);

}

void philo_start_eating(t_list *philos)
{
	pthread_mutex_lock(&philos->mutexx);
	
	printf("%d philosopher %d has started eating\n",current_timestamp() - (int)philos->ctime,getindexbyid(philos));
	pthread_mutex_unlock(&philos->mutexx);

}

void philo_start_thinking(t_list *philos)
{
	
	printf("%d philosopher %d has started thinking\n",current_timestamp() - (int)philos->ctime ,getindexbyid(philos));
}

void philo_died(t_list *philos)
{
	pthread_mutex_lock(&philos->mutexx);
	printf("%d philosopher %d has died\n",current_timestamp() - (int)philos->ctime ,getindexbyid(philos));
	pthread_mutex_unlock(&philos->mutexx);

}


void *check_death(t_list *philo_inf)
{
	//printf("%lld , %lld \n",philo_inf->ctime , current_timestamp() - philo_inf->timest);
	//return 0;
	while (1)
	{
		if (philo_inf->time_to_die <= current_timestamp() - philo_inf->ctime)
		{
			philo_died(philo_inf);
			exit(-1);
		}
	}
}

void checkeat(t_list *philo)
{
	if ((philo->f_control > philo->nphilo))
	{
		printf("round ended\n");
		exit(1);
	}
}
void *routinee(t_list *philo_inf)
{
	pthread_t tid ;
	philo_inf->ctime = current_timestamp() ;
	pthread_create(&tid,NULL,&check_death,philo_inf);
	pthread_detach(tid);
	while (1)
	{
		philo_start_thinking(philo_inf);
		
		pthread_mutex_lock(&chopstick[getindexbyid(philo_inf)]);
		
		philo_take_fork(philo_inf);
		
		pthread_mutex_lock(&chopstick[(getindexbyid(philo_inf) + 1) % philo_inf->nphilo]);
		
		philo_start_eating(philo_inf);
		
		sleep(philo_inf->time_to_eat);
		
		checkeat(philo_inf);
		
		philo_inf->f_control++;
		pthread_mutex_unlock(&chopstick[getindexbyid(philo_inf)]);

  		pthread_mutex_unlock(&chopstick[(getindexbyid(philo_inf) + 1) % philo_inf->nphilo]);
		//
	}
}



void init_that_shit(char **argv, t_list *philost)
{
	philost->nphilo = ft_atoi(argv[1]);
	philost->time_to_die = ft_atoi(argv[2]);
	philost->time_to_eat = ft_atoi(argv[3]);
	philost->time_to_sleep = ft_atoi(argv[4]);
	philost->timest = 0;
	philost->f_control = 0;
	philost->ctime = 0;
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

	int i = 0;
	chopstick = malloc(sizeof(pthread_mutex_t *) * philost.nphilo + 1);
	printf("args error \n");
	while(i < philost.nphilo)
	{
		//chopstick[i] = NULL;
		pthread_mutex_init(&chopstick[i], NULL);
		i++;
	}
	philost.timest = current_timestamp();
	printf("number of philos : %d \n",philost.nphilo);
	printf("time to die : %d \n",philost.time_to_die);
	printf("time to eat : %d \n",philost.time_to_eat);
	printf("time to sleep: %d \n",philost.time_to_sleep);
	printf("number of rounds : %s \n",argv[5]);
	i = 0;
	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo + 1);
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