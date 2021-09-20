#include "../headers/phil.h"

static t_mtx	*get_mutex(const int *param)
{
	t_mtx	*mtx;
	int		i;

	i = 0;
	mtx = malloc(sizeof(t_mtx));
	if (!mtx)
		return (NULL);
	mtx->forks = malloc(sizeof(pthread_mutex_t) * param[COUNT_PHIL]);
	if (!mtx->forks)
	{
		free(mtx);
		return (NULL);
	}
	while (i < param[COUNT_PHIL])
	{
		pthread_mutex_init(&mtx->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mtx->print, NULL);
	return (mtx);
}

static void	init_phil_param(t_phil **phil, time_t *t, int *param, t_mtx *mtx)
{
	int	i;

	i = 0;
	while (i < param[COUNT_PHIL])
	{
		phil[i]->done_eat = 0;
		phil[i]->sig_die = phil[0]->sig_die;
		phil[i]->id = i;
		phil[i]->params = param;
		phil[i]->mute = mtx;
		phil[i]->current_time = t;
		phil[i]->last_eat = 0;
		i++;
	}
}

int	get_phil_param(t_phil **phil, int *param)
{
	t_mtx	*mtx;
	time_t	*time;

	phil[0]->sig_die = malloc(sizeof(int));
	if (!phil[0]->sig_die)
		return (0);
	time = malloc(sizeof(time_t));
	if (!time)
		return (0);
	*time = get_time();
	mtx = get_mutex(param);
	if (!mtx)
	{
		free(phil[0]->sig_die = malloc(sizeof(int)));
		free(time);
		return (0);
	}
	*phil[0]->sig_die = 0;
	init_phil_param(phil, time, param, mtx);
	return (1);
}

t_phil	**init_phil(int *params)
{
	t_phil	**phil;
	int		i;

	phil = (t_phil **)malloc(sizeof(t_phil *) * params[COUNT_PHIL]);
	if (!phil)
		return (NULL);
	i = 0;
	while (i < params[COUNT_PHIL])
	{
		phil[i] = (t_phil *)malloc(sizeof(t_phil));
		if (!phil[i])
			return (free_phil(i, &phil));
		i++;
	}
	if (!get_phil_param(phil, params))
		return (free_phil(params[COUNT_PHIL], &phil));
	return (phil);
}

int	all_eated(int *eat, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (eat[i] == 1)
			i++;
		else
			break ;
	}
	if (i == count)
		return (1);
	return (0);
}
