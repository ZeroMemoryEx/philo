/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadane <marvin@42.fr>           		    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:43:35 by ahadane           #+#    #+#             */
/*   Updated: 2022/11/10 01:10:02 by ahadane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"header.h"

void	check_eat_rounds(t_philo *philox)
{
	int		i;
	t_philo	philo;

	philo = *philox;
	if (philo.n_argc != 6)
		return ;
	i = 0;
	while (i < philo.nphilo)
	{
		if (philo.eats[i] != philo.num_of_rounds)
			return ;
		i++;
	}
	pthread_mutex_lock(philox->mutexx);
	exit(-1);
}

void	*routinee(void *philo_inf)
{
	t_philo	*p;
	int		i;

	p = (t_philo *) philo_inf;
	i = p->i;
	while (1)
	{
		pthread_mutex_lock(&p->stick[i]);
		ft_printf(p, i + 1, "take fork \n", c_time() - p->start);
		pthread_mutex_lock(&p->stick[(i + 1) % p->nphilo]);
		ft_printf(p, i + 1, "take fork \n", c_time() - p->start);
		ft_printf(p, i + 1, "start eating\n", c_time() - p->start);
		pthread_mutex_lock(&p->mudeath[i]);
		p->death_spv[i] = c_time();
		pthread_mutex_unlock(&p->mudeath[i]);
		pthread_mutex_lock(&p->meatround);
		p->eats[i]++;
		pthread_mutex_unlock(&p->meatround);
		ft_sleep(p->time_to_eat);
		pthread_mutex_unlock(&p->stick[(i + 1) % p->nphilo]);
		pthread_mutex_unlock(&p->stick[i]);
		ft_printf(p, i + 1, "start sleeping\n", c_time() - p->start);
		ft_sleep(p->time_to_sleep);
		ft_printf(p, i + 1, "start thinking\n", c_time() - p->start);
	}
}

int	init_that_shit(char	**argv, t_list *p_lst)
{
	int	i;

	i = 0;
	p_lst->nphilo = ft_atoi(argv[1]);
	p_lst->time_to_die = ft_atoi(argv[2]);
	p_lst->time_to_eat = ft_atoi(argv[3]);
	p_lst->time_to_sleep = ft_atoi(argv[4]);
	p_lst->p_philo = malloc(sizeof(pthread_t) * (p_lst->nphilo));
	p_lst->start = c_time();
	p_lst->death_spv = malloc(sizeof(long long int) * (p_lst->nphilo));
	p_lst->stick = malloc(sizeof(pthread_mutex_t) * (p_lst->nphilo));
	p_lst->eats = malloc(sizeof(int) * (p_lst->nphilo));
	p_lst->mudeath = malloc(sizeof(pthread_mutex_t));
	if (!p_lst->death_spv || !p_lst->stick || !p_lst->mudeath)
		return (-1);
	if (!p_lst->p_philo)
		return (-1);
	while (i < p_lst->nphilo)
	{
		p_lst->eats[i] = 0;
		p_lst->death_spv[i] = c_time();
		pthread_mutex_init(&p_lst->stick[i], NULL);
		pthread_mutex_init(&p_lst->mudeath[i++], NULL);
	}
	return (0);
}

int	check_death(t_philo *philo, t_list *ph1)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&philo->meatround);
		check_eat_rounds(philo);
		pthread_mutex_unlock(&philo->meatround);
		i = 0;
		while (i < philo->nphilo)
		{
			pthread_mutex_lock(&ph1->mudeath[i]);
			if ((c_time() - ph1->death_spv[i]) >= ph1->time_to_die)
			{
				pthread_mutex_lock(&ph1->mutexx);
				printf("%lld %d died\n", c_time() - ph1->death_spv[i], i + 1);
				exit(-1);
				break ;
			}
			pthread_mutex_unlock(&ph1->mudeath[i]);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	p_lst;
	t_philo	*philo;

	if ((argc == 5 || argc == 6) && !init_that_shit(argv, &p_lst))
	{
		philo = malloc(sizeof(t_philo));
		if (argc == 6)
		{
			p_lst.num_of_rounds = ft_atoi(argv[5]);
			if (ft_atoi(argv[5]) == 0)
				return (-1);
		}
	}
	else
	{
		printf("args error \n");
		return (-1);
	}
	pthread_mutex_init(&p_lst.mutexx, NULL);
	pthread_mutex_init(&p_lst.meatround, NULL);
	if (struct_cloner(&p_lst, philo, argc))
		return (-1);
	return (check_death(philo, &p_lst));
}
