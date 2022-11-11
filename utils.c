/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadane <ahadane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:11:25 by ahadane           #+#    #+#             */
/*   Updated: 2022/11/11 02:32:26 by ahadane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long long int	c_time(void)
{
	struct timeval	te;
	long long int	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

void	ft_av_putchar(int op)
{
	if (op == 99)
		exit(-1);
	write(2, "param error\n", 12);
	exit(-1);
}

int	struct_cloner(t_list *src, t_philo *dest, int argc)
{
	int	i;

	i = 0;
	while (i < src->nphilo)
	{
		dest->i = i;
		dest->eats = src->eats;
		dest->start = src->start;
		dest->time_to_die = src->time_to_die;
		dest->time_to_eat = src->time_to_eat;
		dest->time_to_sleep = src->time_to_sleep;
		dest->mutexx = &src->mutexx;
		dest->meatround = src->meatround;
		dest->mudeath = src->mudeath;
		dest->stick = src->stick;
		dest->nphilo = src->nphilo;
		dest->n_argc = argc;
		dest->death_spv = src->death_spv;
		dest->num_of_rounds = src->num_of_rounds;
		pthread_create(&src->p_philo[i], NULL, routinee, dest);
		pthread_detach(src->p_philo[i++]);
		usleep(100);
		dest = malloc(sizeof(t_philo));
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	nbr;
	int					i;
	int					j;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	j = i;
	while (str[j])
		if (str[j] < '0' || str[j++] > '9')
			ft_av_putchar (1);
	while (str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + str[i++] - '0';
	return (((int)nbr) * sign);
}

void	ft_sleep(time_t sec)
{
	long long int	sleep;

	sleep = sec + c_time();
	while (1)
	{
		if (sleep <= c_time())
			return ;
		usleep(250);
	}
}
