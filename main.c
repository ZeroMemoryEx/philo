/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadane <ahadane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:43:35 by ahadane           #+#    #+#             */
/*   Updated: 2022/11/09 23:54:30 by ahadane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"header.h"

void	check_eat_rounds(t_philo *philo)
{
	int	i;
	int	pass;

	if (philo->n_argc != 6)
		return ;
	i = 0;
	pass = 0;
	while (i < philo->nphilo)
	{
		if (philo[i].eats == philo->num_of_rounds)
			pass++;
		else
			break ;
		if (pass == philo->num_of_rounds)
		{
			pthread_mutex_lock(philo->mutexx);
			exit(-1);
		}
	}
}

void	*routinee(void *philo_inf)
{
	t_philo	*p;
	int		i;

	p = (t_philo *) philo_inf;
	i = p->i;
	while (1)
	{
		pthread_mutex_lock(&p->chopstick[i]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d take fork \n", c_time() - p->start, i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(&p->chopstick[(i + 1) % p->nphilo]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d take fork \n", c_time() - p->start, i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start eating \n", c_time() - p->start, i + 1);
		pthread_mutex_unlock(p->mutexx);
		pthread_mutex_lock(&p->mudeath[i]);
		p->death_spv[i] = c_time();
		pthread_mutex_unlock(&p->mudeath[i]);
		pthread_mutex_lock(&p->meatround);
		p->eats++;
		pthread_mutex_unlock(&p->meatround);
		ft_sleep(p->time_to_eat);
		pthread_mutex_unlock(&p->chopstick[(i + 1) % p->nphilo]);
		pthread_mutex_unlock(&p->chopstick[i]);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start sleeping \n", c_time() - p->start, i + 1);
		pthread_mutex_unlock(p->mutexx);
		ft_sleep(p->time_to_sleep);
		pthread_mutex_lock(p->mutexx);
		printf("%lld %d  start thinking \n", c_time() - p->start, i + 1);
		pthread_mutex_unlock(p->mutexx);
	}
	return (0);
}

int	init_that_shit(char	**argv, t_list *philost)
{
	int	i;

	i = 0;
	philost->nphilo = ft_atoi(argv[1]);
	philost->time_to_die = ft_atoi(argv[2]);
	philost->time_to_eat = ft_atoi(argv[3]);
	philost->time_to_sleep = ft_atoi(argv[4]);
	philost->time_to_sleep = ft_atoi(argv[4]);
	philost->start = c_time();
	philost->death_spv = malloc(sizeof(long long int) * (philost->nphilo));
	philost->chopstick = malloc(sizeof(pthread_mutex_t) * (philost->nphilo));
	philost->mudeath = malloc(sizeof(pthread_mutex_t));
	if (!philost->death_spv || !philost->chopstick || !philost->mudeath)
		return (-1);
	while (i < philost->nphilo)
	{
		philost->death_spv[i] = c_time();
		pthread_mutex_init(&philost->chopstick[i], NULL);
		pthread_mutex_init(&philost->mudeath[i++], NULL);
	}
	return (0);
}

int	check_death(t_philo *philo, t_list *philost)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&philo->meatround);
		check_eat_rounds(philo);
		pthread_mutex_unlock(&philo->meatround);
		i = 0;
		while (i < philost->nphilo)
		{
			pthread_mutex_lock(&philost->mudeath[i]);
			if ((c_time() - philost->death_spv[i]) >= philost->time_to_die)
			{
				pthread_mutex_lock(&philost->mutexx);
				printf("%lld %d died\n", c_time() - philost->death_spv[i], i + 1);
				break;
			}
			pthread_mutex_unlock(&philost->mudeath[i]);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	philost;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if ((argc == 5 || argc == 6) && !init_that_shit(argv, &philost))
	{
		if (argc == 6)
			philost.num_of_rounds = ft_atoi(argv[5]);
	}
	else
	{
		printf("args error \n");
		return (-1);
	}
	pthread_mutex_init(&philost.mutexx, NULL);
	pthread_mutex_init(&philost.meatround, NULL);
	philost.p_philo = malloc(sizeof(pthread_t) * philost.nphilo);
	if (!philost.p_philo || struct_cloner(&philost, philo, argc))
		return (-1);
	return (check_death(philo, &philost));
}
