#include "../headers/phil.h"

static size_t	skip_ch(const char *str, int *neg)
{
	size_t	i;

	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == ' ' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*neg = -1;
		i++;
	}
	return (i);
}

int	ft_usleep(time_t usec, int *sig_die)
{
	struct timeval	time;
	time_t			zero_time;
	time_t			current_time;

	gettimeofday(&time, NULL);
	zero_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	current_time = zero_time;
	while (usec > current_time - zero_time && !(*sig_die))
	{
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		usleep(100);
	}
	if ((*sig_die))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;
	int		neg;

	neg = 1;
	i = skip_ch(str, &neg);
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nbr = nbr * 10 + (str[i++] - '0');
		if (nbr * neg > __INT_MAX || nbr * neg < __INT_MIN)
		{
			if (nbr * neg > __INT_MIN)
				return (-1);
			return (0);
		}
	}
	if (neg == -1 && nbr != 0)
		nbr = -nbr;
	return (nbr);
}

int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}

void	ft_swap_nums(int *n1, int *n2)
{
	int	tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}
