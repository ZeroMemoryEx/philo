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
     long long int				timest;
	 long long int             time_to_die;
    int             time_to_eat;
    int             f_control;
    int             time_to_sleep;
     long long int   ctime;
    int				*indg;
    int             num_of_rounds;
	atomic_int		i;// not allowed
    pthread_mutex_t mutexx;
    pthread_mutex_t *dick;
    pthread_t       *p_philo;
	pthread_mutex_t	*chopstick;
	 long long int	*death_spv;
}t_list;

typedef struct s_philo
{
		int				nphilo;

	int					i;
	 long long int 	start;
	int					time_to_eat;
	 long long int					time_to_die;
	int					time_to_sleep;
		 long long int	*death_spv;

	int					num_of_rounds;
	pthread_mutex_t 	*mutexx;
    pthread_mutex_t 	*dick;
	pthread_mutex_t		*chopstick;
} t_philo;
#endif