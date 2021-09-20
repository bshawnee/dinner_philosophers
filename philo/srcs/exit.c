#include "../headers/phil.h"
#include <string.h>

void	free_all(t_phil ***phil)
{
	int	*param;

	free((*phil[0])->sig_die);
	destroy_mutex((*phil[0])->mute, (*phil[0])->params);
	free((*phil[0])->current_time);
	param = (*phil[0])->params;
	free_phil((*phil[0])->params[COUNT_PHIL], phil);
	free(param);
}

void	destroy_mutex(t_mtx *mtx, const int *params)
{
	int	i;

	i = 0;
	while (i < params[COUNT_PHIL])
	{
		pthread_mutex_destroy(&mtx->forks[i]);
		i++;
	}
	free(mtx->forks);
	pthread_mutex_destroy(&mtx->print);
	free(mtx);
}

static void	die_cicle(t_phil **phil, int *eat)
{
	int		i;

	i = 0;
	while (i < phil[0]->params[COUNT_PHIL])
	{
		if (phil[i]->done_eat)
			eat[i] = 1;
		if (all_eated(eat, phil[0]->params[COUNT_PHIL]))
		{
			*phil[0]->sig_die = 1;
			return ;
		}
		if (timestamp(phil[i]->current_time) - phil[i]->last_eat >= \
		phil[0]->params[T_T_DIE])
		{
			pthread_mutex_lock(&phil[i]->mute->print);
			*phil[0]->sig_die = 1;
			printf("%12ld %5d died\n", timestamp(phil[i]->current_time), \
			phil[i]->id + 1);
			return ;
		}
		i++;
		if (i == phil[0]->params[COUNT_PHIL])
			i = 0;
	}
}

int	check_die(t_phil **phil)
{
	int	*eat;

	eat = malloc(sizeof(int) * phil[0]->params[COUNT_PHIL]);
	if (!eat)
		return (1);
	memset(eat, 0, phil[0]->params[COUNT_PHIL] - 1);
	die_cicle(phil, eat);
	free(eat);
	return (0);
}
