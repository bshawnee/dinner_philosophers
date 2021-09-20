#include "../headers/phil_bonus.h"

void	free_and_exit(int *param, pid_t *forks, sem_t **sem)
{
	int	i;

	i = 0;
	while (i < param[COUNT_PHIL])
	{
		kill(forks[i], 9);
		i++;
	}
	free(forks);
	close_sem(&sem, param[COUNT_EAT]);
	free(param);
}
