#include "../headers/phil.h"

void	*free_phil(int i, t_phil ***phil)
{
	t_phil	**tmp;

	tmp = *phil;
	i--;
	while (i >= 0)
	{
		free((tmp[i]));
		i--;
	}
	free(*phil);
	return (NULL);
}

static int	start_threads(t_phil **phil, int arg)
{
	int	i;

	i = 0;
	while (i < phil[0]->params[COUNT_PHIL])
	{
		if (arg == 1 && !(phil[0]->id & 1))
		{
			pthread_create(&phil[i]->thread, NULL, thread_dinner, phil[i]);
			pthread_detach(phil[i]->thread);
		}
		else if (arg == 0 && (phil[0]->id & 1))
		{
			pthread_create(&phil[i]->thread, NULL, thread_dinner, phil[i]);
			pthread_detach(phil[i]->thread);
		}
		i++;
	}
	return (0);
}

static int	run_thread(t_phil **phil)
{
	int			i;

	i = 0;
	*phil[0]->current_time = get_time();
	start_threads(phil, 0);
	usleep(500);
	start_threads(phil, 1);
	return (check_die(phil));
}

int	init_lunch(int *param)
{
	t_phil	**phil;

	if (!param)
		return (1);
	phil = init_phil(param);
	if (!phil)
	{
		free(param);
		return (1);
	}
	if (run_thread(phil))
	{
		free_all(&phil);
		return (1);
	}
	free_all(&phil);
	return (0);
}
