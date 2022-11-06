#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#include <pthread.h>
#include <stdatomic.h>

void	ft_av_putchar(int op);
int	ft_atoi(const char *str);
typedef struct s_list
{
	int				nphilo;
	int				timex;
    long long int   timest;
	int             time_to_die;
    int             time_to_eat;
    int             f_control;
    int             time_to_sleep;
    long long int   ctime;
    int				*indg;
    int             num_of_rounds;
	atomic_int		i;
    pthread_mutex_t mutexx;
    pthread_t       *p_philo;
	pthread_mutex_t	*chopstick;
}t_list;

#endif