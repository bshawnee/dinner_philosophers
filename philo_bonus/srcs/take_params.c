#include "../headers/phil_bonus.h"

static int	correct_input(const char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	*correct_params_add(int *params)
{
	if (params[COUNT_PHIL] < 1 || params[T_T_DIE] < 1 || params[T_T_EAT] < 1 \
	|| params[T_T_SLEEP] < 1 || params[COUNT_EAT] < 1)
	{
		free(params);
		return (NULL);
	}
	return (params);
}

int	*correct_params(const char **argv)
{
	int	*params;

	if (!correct_input(argv))
		return (NULL);
	params = (int *)malloc(sizeof(int) * 6);
	if (!params)
		return (NULL);
	params[COUNT_PHIL] = ft_atoi(argv[COUNT_PHIL + 1]);
	params[T_T_DIE] = ft_atoi(argv[T_T_DIE + 1]);
	params[T_T_EAT] = ft_atoi(argv[T_T_EAT + 1]);
	params[T_T_SLEEP] = ft_atoi(argv[T_T_SLEEP + 1]);
	if (argv[MUST_EAT + 1])
	{
		params[MUST_EAT] = 1;
		params[COUNT_EAT] = ft_atoi(argv[MUST_EAT + 1]);
	}
	else
	{
		params[MUST_EAT] = 0;
		params[COUNT_EAT] = 1;
	}
	return (correct_params_add(params));
}
