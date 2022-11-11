/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadane <marvin@42.fr>   		       	    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:53:28 by ahadane           #+#    #+#             */
/*   Updated: 2022/11/10 00:57:17 by ahadane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include	<stdlib.h>
# include	<limits.h>
# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<sys/time.h>

typedef struct s_list
{
	int				nphilo;
	long long int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_rounds;
	pthread_t		*p_philo;
	pthread_mutex_t	mutexx;
	pthread_mutex_t	*mudeath;
	pthread_mutex_t	*chopstick;
	pthread_mutex_t	meatround;
	long long int	start;
	long long int	*death_spv;
	int				*eats;

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
	int					*eats;
	int					n_argc;
	pthread_mutex_t		*mutexx;
	pthread_mutex_t		*mudeath;
	pthread_mutex_t		meatround;
	pthread_mutex_t		*chopstick;
}	t_philo;

void			ft_av_putchar(int op);
int				ft_atoi(const char *str);
int				struct_cloner(t_list *src, t_philo *dest, int argc);
void			ft_sleep(time_t sec);
void			*routinee(void *philo_inf);
void			check_eat_rounds(t_philo *philo);
int				init_that_shit(char	**argv, t_list *philost);
long long int	c_time(void);
int				check_death(t_philo *philo, t_list *philost);
void			ft_printf(t_philo *p, int philo, char *str, long long int time);
#endif
