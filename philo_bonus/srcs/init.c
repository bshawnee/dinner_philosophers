#include "../headers/phil_bonus.h"

pid_t	*run_process(int *param, sem_t **sem)
{
	int		i;
	pid_t	*pids;
	time_t	zero_time;

	i = 0;
	zero_time = get_time();
	pids = malloc(sizeof(pid_t) * param[COUNT_PHIL]);
	if (!pids)
		return (NULL);
	while (i < param[COUNT_PHIL])
	{
		pids[i] = fork();
		if (!pids[i])
			dinner_process(zero_time, i, param, sem);
		else if (pids[i] < 0)
		{
			while (--i >= 0)
				kill(pids[i], 9);
			free(pids);
			return (NULL);
		}
		i++;
	}
	return (pids);
}

void	*control_worker(void *arg)
{
	t_control_proc	*cntrl;
	int				i;

	i = 1;
	cntrl = arg;
	while (i <= cntrl->count)
	{
		sem_wait(cntrl->sem[i + SEM_PRINT]);
		i++;
	}
	sem_wait(cntrl->sem[SEM_PRINT]);
	sem_post(cntrl->sem[SEM_EXIT]);
	return (arg);
}

int	create_fork(int *param)
{
	pid_t			*phil_pid;
	sem_t			**forks;
	pthread_t		worker;
	t_control_proc	cntrl;

	forks = get_sem(param[COUNT_PHIL]);
	if (!forks)
		return (1);
	phil_pid = run_process(param, forks);
	if (param[MUST_EAT] == 1 )
	{
		cntrl.count = param[COUNT_PHIL];
		cntrl.sem = forks;
		pthread_create(&worker, NULL, control_worker, &cntrl);
		pthread_detach(worker);
	}
	if (!phil_pid)
	{
		close_sem(&forks, param[COUNT_EAT]);
		return (1);
	}
	sem_wait(forks[SEM_EXIT]);
	free_and_exit(param, phil_pid, forks);
	return (0);
}
