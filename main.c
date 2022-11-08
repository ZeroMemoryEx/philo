#include <unistd.h>
#include <stdio.h>
#include "header.h"
#include <sys/time.h>

 long long int 
	current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long int milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

void ft_sleep(time_t sec)
{

	 long long int tim = current_timestamp();
	while(1)
	{
		 long long int sleep = sec + tim;
		if (sleep <= current_timestamp())
			break;
		usleep(99);
	}
}

void 
*check_death(
	t_list *philo_inf)
{
	while (1)
	{
		if (philo_inf->time_to_die <= current_timestamp() - philo_inf->ctime)
		{
			printf("philo diead\n");
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

unsigned long int ctimev(unsigned int now)
{
	return (current_timestamp() - now);
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
		pthread_mutex_lock(&p->dick[i]);
		p->death_spv[i] =  current_timestamp() - p->start;
		// printf(">>%d         %d\n",p->death_spv[i], i + 1);
		pthread_mutex_unlock(&p->dick[i]);
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
	philost->timest = 0;
	philost->f_control = 0;
	philost->ctime = 0;
}

int main(int argc , char **argv)
{
	t_list philost;
	t_philo *philo;
	if (argc == 4 || argc == 5)
		init_that_shit(argv,&philost);
	else
	{
		printf("args error \n");
		exit(-1);
	}
	int i = 0;
	philost.timest = current_timestamp();

	philost.death_spv  = malloc(sizeof(  long long int) * (philost.nphilo));
	philost.chopstick = malloc(sizeof(pthread_mutex_t) * (philost.nphilo + 1));
	philost.dick = malloc(sizeof(pthread_mutex_t) * (philost.nphilo + 1));
	if (!philost.chopstick)
		return (-1);
	if (philost.chopstick)
	{
		while(i < philost.nphilo)
		{
			philost.death_spv[i] = 0;
			pthread_mutex_init(&philost.chopstick[i], NULL);
			pthread_mutex_init(&philost.dick[i],NULL);

			i++;
		}
	}	
	else
	{
		printf("error\n");
		exit(EXIT_FAILURE); // not allowed
	}
	pthread_mutex_init(&philost.mutexx,NULL);
	//printf("number of philos : %d \n",philost.nphilo);
	//printf("time to die : %d \n",philost.time_to_die);
	//printf("time toclea eat : %d \n",philost.time_to_eat);
	//printf("time to sleep: %d \n",philost.time_to_sleep);
	//printf("number of rounds : %s \n",argv[5]);
	philost.i = 0;
	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo );
	if (!philost.p_philo)
		return (-1);

	// while (i < nummber_of_philo)
	// {
	// 	pthread_create(&philost.p_philo[philost.i], NULL, routinee, philost[philost.i]);
	// 	usleep(50);
	// 	philost.i++;
	// }
	while (philost.i < philost.nphilo)
	{
		philo = malloc(sizeof(t_philo ) * 1);
		philo->i = philost.i;
		philo->start = philost.timest;
		philo->time_to_die = philost.time_to_die;
		philo->time_to_eat = philost.time_to_eat;
		philo->time_to_sleep = philost.time_to_sleep;
		philo->mutexx = &philost.mutexx;
		philo->dick = philost.dick;
		philo->chopstick = philost.chopstick;
		philo->nphilo = philost.nphilo;
		philo->death_spv = philost.death_spv;
		pthread_create(&philost.p_philo[philost.i], NULL, routinee, philo);
		pthread_detach(philost.p_philo[philost.i]);
		usleep(500);
		philost.i++;
	}
	int ck;
	// usleep(500);
	while(1)
	{
		ck = 0;
		while(ck < philost.nphilo)
		{
			pthread_mutex_lock(&philost.dick[ck]);
			// printf ("last time philo number %i eats is %lld \n", ck + 1, philost.death_spv[ck]);
			if ((current_timestamp() - philost.timest) -  philost.death_spv[ck] >= philost.time_to_die)
			{
			// // printf(">>%d         %d\n",philost.death_spv[ck], ck);
			// // (current_timestamp - start) - last eat >= time to die
			// // printf("ck %d last %i \n", ck, (philost.death_spv[ck] - philost.timest));
			// if ((current_timestamp() - philost.timest) - (philost.death_spv[ck] - philost.timest) >= philost.time_to_die )
			// {
			// 	printf("diff %lld last %lld die %lld\n", (current_timestamp() - philost.timest), (philost.death_spv[ck]), philost.time_to_die);
				pthread_mutex_lock(&philost.mutexx);
				printf(">>%d died %lld            %lld\n",ck + 1,philost.death_spv[ck], philost.time_to_die + philost.death_spv[ck]);
				exit(-1);
			}
			pthread_mutex_unlock(&philost.dick[ck]);
			// usleep(40);
			ck++;
		}
	}
	while(1);
}