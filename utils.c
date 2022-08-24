
#include "header.h"

void	ft_av_putchar(int op)
{
	if (op == 99)
		exit(-1);
	write(2, "Error\n", 6);
	exit(-1);
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