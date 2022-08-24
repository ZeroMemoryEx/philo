#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

void	ft_av_putchar(int op);
int	ft_atoi(const char *str);
typedef struct s_list
{
	int				nphilo;
	int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_of_rounds;
    pthread_mutex_t mutexx;
    pthread_t       *p_philo;
}t_list;

#endif