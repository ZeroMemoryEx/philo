/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:11:05 by ahadane           #+#    #+#             */
/*   Updated: 2022/11/10 01:11:10 by ahadane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_printf(t_philo *p, int philo, char *str, long long int time)
{
	pthread_mutex_lock(p->mutexx);
	printf("%lld %d %s", time, philo, str);
	pthread_mutex_unlock(p->mutexx);
}
