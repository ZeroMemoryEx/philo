#include <unistd.h>
#include <stdio.h>
#include "header.h"
#include <sys/time.h>

 long long int 
	current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); 
    long long int milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; 
    return milliseconds;
}

void	ft_sleep(time_t sec)
{
	long long int tim = current_timestamp();
	long long int sleep = sec + tim;
	while (1)
	{
		
		if (sleep <= current_timestamp())
			break;
		usleep(100);
	}
}

void check_eat_rounds(t_philo *philo)
{
	if (philo->n_argc != 6)
		return ;
	int i = 0;
	int pass = 0;
	while(i < philo->nphilo)
	{
		if (philo[i].eats == philo->num_of_rounds)
			pass++;
		else
			break;
		if (pass == philo->num_of_rounds)
		{
			pthread_mutex_lock(philo->mutexx);
			exit(-1);
		}
	}
}

void
	*routinee(
	void *philo_inf)
{
	t_philo *p = (t_philo*)philo_inf;

	int i = p->i;
	while (1)
	{
		pthread_mutex_lock(&p->chopstick[i]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d take fork \n",current_timestamp() - p->start,i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(&p->chopstick[(i + 1) % p->nphilo]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d take fork \n",current_timestamp() - p->start ,i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start eating \n",current_timestamp() - p->start ,i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(&p->mudeath[i]);
		p->death_spv[i] =  current_timestamp();
		pthread_mutex_unlock(&p->mudeath[i]);
		pthread_mutex_lock(&p->meatround);
		p->eats++;
		pthread_mutex_unlock(&p->meatround);
		ft_sleep(p->time_to_eat);
  		pthread_mutex_unlock(&p->chopstick[(i + 1) % p->nphilo]);
		pthread_mutex_unlock(&p->chopstick[i]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start sleeping \n",current_timestamp() - p->start ,i + 1);
		pthread_mutex_unlock(p->mutexx);
		ft_sleep(p->time_to_sleep);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start thinking \n",current_timestamp() - p->start ,i + 1);
		pthread_mutex_unlock(p->mutexx);
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
	philost->time_to_sleep = ft_atoi(argv[4]);
	philost->start = current_timestamp();
}

int main(int argc , char **argv)
{
	t_list	philost;
	t_philo	*philo;
	if (argc == 5 || argc == 6)
	{
		init_that_shit(argv,&philost);
		if (argc == 6)
			philost.num_of_rounds = ft_atoi(argv[5]);
	}
	else
	{
		printf("args error \n");
		exit(-1);
	}
	int i = 0;

	philost.death_spv  = malloc(sizeof(  long long int) * (philost.nphilo));
	philost.chopstick = malloc(sizeof(pthread_mutex_t) * (philost.nphilo ));
	philost.mudeath = malloc(sizeof(pthread_mutex_t));
	philost.meatround = malloc(sizeof(pthread_mutex_t));
	if (!philost.chopstick)
		return (-1);
	if (philost.chopstick)
	{
		while(i < philost.nphilo)
		{
			philost.death_spv[i] = current_timestamp();
			pthread_mutex_init(&philost.chopstick[i], NULL);
			pthread_mutex_init(&philost.mudeath[i],NULL);
			pthread_mutex_init(&philost.meatround[i],NULL);
			i++;
		}
	}	
	else
	{
		return(-1); 
	}
	pthread_mutex_init(&philost.mutexx,NULL);

	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo );
	if (!philost.p_philo)
		return (-1);

	i = 0;
	while (i < philost.nphilo)
	{
		philo = malloc(sizeof(t_philo ) * 1);
		philo->i = i;
		philo->eats = 0;
		philo->start = philost.start;
		philo->time_to_die = philost.time_to_die;
		philo->time_to_eat = philost.time_to_eat;
		philo->time_to_sleep = philost.time_to_sleep;
		philo->mutexx = &philost.mutexx;
		philo->meatround = philost.meatround[0];
		philo->mudeath = philost.mudeath;
		philo->chopstick = philost.chopstick;
		philo->nphilo = philost.nphilo;
		philo->n_argc = argc;
		philo->death_spv = philost.death_spv;
		philo->num_of_rounds = philost.num_of_rounds;
		pthread_create(&philost.p_philo[i], NULL, routinee, philo);
		pthread_detach(philost.p_philo[i]);
		usleep(50);
		i++;
	}
	int ck;
	usleep(300);
	while(1)
	{
		pthread_mutex_lock(&philo->meatround);
			
		check_eat_rounds(philo);

		pthread_mutex_unlock(&philo->meatround);
		ck = 0;
		while(ck < philost.nphilo)
		{
			pthread_mutex_lock(&philost.mudeath[ck]);


			if ((current_timestamp() - philost.death_spv[ck]) >= philost.time_to_die)
			{
				pthread_mutex_lock(&philost.mutexx);
				printf("%lld %d died\n",current_timestamp() - philost.death_spv[ck], ck + 1);
				exit(-1);
			}
			pthread_mutex_unlock(&philost.mudeath[ck]);
			usleep(100);
			ck++;
		}
	}
}