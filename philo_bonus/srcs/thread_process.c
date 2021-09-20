#include "../headers/phil_bonus.h"

static void	*worker(void *arg)
{
	t_arg_worker	*work;

	work = arg;
	while (timestamp(work->zero_time) - *work->last_eat < work->param[T_T_DIE])
		usleep(100);
	sem_wait(work->sem[SEM_PRINT]);
	printf("%12ld %5d died\n", timestamp(work->zero_time), work->id + 1);
	sem_post(work->sem[SEM_EXIT]);
	return (NULL);
}

static void	dinner_cicle(t_arg_worker *w)
{
	if (w->id % 2)
		usleep(500);
	print_msg("is thinking", w->id, w->zero_time, w->sem[SEM_PRINT]);
	sem_wait(w->sem[SEM_FORKS]);
	print_msg("has taking a fork", w->id, w->zero_time, w->sem[SEM_PRINT]);
	sem_wait(w->sem[SEM_FORKS]);
	print_msg("has taking a fork", w->id, w->zero_time, w->sem[SEM_PRINT]);
	print_msg("is eating", w->id, w->zero_time, w->sem[SEM_PRINT]);
	*w->last_eat = timestamp(w->zero_time);
	if (w->param[MUST_EAT])
	{
		w->param[COUNT_EAT]--;
		if (w->param[COUNT_EAT] == 0)
		{
			w->param[MUST_EAT] = 0;
			sem_post(w->sem[SEM_PRINT + w->id + 1]);
		}
	}
	ft_usleep(w->param[T_T_EAT]);
	sem_post(w->sem[SEM_FORKS]);
	sem_post(w->sem[SEM_FORKS]);
	print_msg("is sleeping", w->id, w->zero_time, w->sem[SEM_PRINT]);
	ft_usleep(w->param[T_T_SLEEP]);
}

int	dinner_process(time_t zero_time, int id, int *param, sem_t **sem)
{
	time_t			last_eat;
	pthread_t		death_checker;
	t_arg_worker	arg_work;

	last_eat = zero_time;
	arg_work.sem = sem;
	arg_work.zero_time = zero_time;
	arg_work.last_eat = &last_eat;
	arg_work.param = param;
	arg_work.id = id;
	pthread_create(&death_checker, NULL, worker, &arg_work);
	pthread_detach(death_checker);
	while (1)
	{
		dinner_cicle(&arg_work);
	}
	return (0);
}
