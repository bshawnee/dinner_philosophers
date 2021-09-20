#include "../headers/phil_bonus.h"

void	print_msg(char *msg, int id, time_t zero, sem_t *sem)
{
	sem_wait(sem);
	printf("%12ld %5d %s\n", timestamp(zero), id + 1, msg);
	sem_post(sem);
}

int	init_lunch(int *param)
{
	if (!param)
		return (1);
	if (param[COUNT_PHIL] == 1)
	{
		printf("%12d %5d is thinking\n", 0, 1);
		printf("%12d %5d has taking a fork\n", 0, 1);
		ft_usleep(param[T_T_DIE]);
		printf("%12d %5d died\n", param[T_T_DIE], 1);
		free(param);
		return (0);
	}
	sem_unlink(S_EXT_NAME);
	sem_unlink(S_FRK_NAME);
	sem_unlink(S_PRT_NAME);
	sem_unlink(S_EAT_NAME);
	if (!param)
		return (1);
	if (create_fork(param))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: parameters\n");
		return (1);
	}
	else if (init_lunch(correct_params((const char **)argv)))
	{
		printf("Error: fatal\n");
		return (1);
	}
	return (0);
}
