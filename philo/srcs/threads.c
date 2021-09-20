#include "../headers/phil.h"

time_t	timestamp(time_t *start_time)
{
	return (get_time() - (*start_time));
}

int	print_status(const char *str, t_phil *phil)
{
	if (!(*phil->sig_die))
	{
		pthread_mutex_lock(&phil->mute->print);
		printf("%12ld %5d %s\n", timestamp(phil->current_time), phil->id + 1, \
		str);
		pthread_mutex_unlock(&phil->mute->print);
		return (0);
	}
	return (1);
}

static int	thread_cicle(t_phil *phil, int *forks, int *eat_count)
{
	pthread_mutex_lock(&phil->mute->forks[forks[LEFT_FORK]]);
	if (print_status("has taking a fork", phil))
		return (1);
	pthread_mutex_lock(&phil->mute->forks[forks[RIGHT_FORK]]);
	if (print_status("has taking a fork", phil))
		return (1);
	phil->last_eat = timestamp(phil->current_time);
	if (print_status("is eating", phil))
		return (1);
	if (phil->params[MUST_EAT] && *eat_count > 0)
	{
		if (!(--(*eat_count)))
			phil->done_eat = 1;
	}
	if (ft_usleep(phil->params[T_T_EAT], phil->sig_die))
		return (1);
	pthread_mutex_unlock(&phil->mute->forks[forks[RIGHT_FORK]]);
	pthread_mutex_unlock(&phil->mute->forks[forks[LEFT_FORK]]);
	return (0);
}

static int	add_thread_cicle(t_phil *phil, int *forks, int *eat_count)
{
	if (print_status("is thinking", phil))
		return (1);
	if (phil->id & 1)
		usleep(500);
	if (thread_cicle(phil, forks, eat_count))
		return (1);
	if (print_status("is sleeping", phil))
		return (1);
	if (ft_usleep(phil->params[T_T_SLEEP], phil->sig_die))
		return (1);
	return (0);
}

void	*thread_dinner(void *arg)
{
	t_phil	*phil;
	int		forks[2];
	int		eat_count;

	phil = arg;
	if (phil->params[MUST_EAT])
		eat_count = phil->params[COUNT_EAT];
	forks[LEFT_FORK] = phil->id;
	forks[RIGHT_FORK] = (phil->id + 1) % phil->params[COUNT_PHIL];
	if (forks[LEFT_FORK] > forks[RIGHT_FORK])
		ft_swap_nums(&forks[LEFT_FORK], &forks[RIGHT_FORK]);
	while (phil->state != DIE)
	{
		if (add_thread_cicle(phil, forks, &eat_count))
		{
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
