#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#include <pthread.h>
#include <stdatomic.h>

void	ft_av_putchar(int op);
int		ft_atoi(const char *str);
typedef struct s_list
{
	int				nphilo;
	int				timex;
	long long int	time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_of_rounds;
    pthread_mutex_t mutexx;
    pthread_mutex_t *mudeath;
    pthread_t       *p_philo;
	pthread_mutex_t	*chopstick;
	pthread_mutex_t *meatround;
	long long int	*death_spv;
}t_list;

typedef struct s_philo
{
	int					nphilo;
	int					i;
	long long int		start;
	int					time_to_eat;
	long long int		time_to_die;
	int					time_to_sleep;
	long long int		*death_spv;
	int					num_of_rounds;
	int					eats;
	int					n_argc;
	pthread_mutex_t		*mutexx;
    pthread_mutex_t 	*mudeath;
    pthread_mutex_t 	meatround;
	pthread_mutex_t		*chopstick;
} t_philo;

#endif