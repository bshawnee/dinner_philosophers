#include "../headers/phil_bonus.h"

int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}

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
