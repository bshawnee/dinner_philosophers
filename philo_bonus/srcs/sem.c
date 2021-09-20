#include "../headers/phil_bonus.h"

static int	sem_for_eat(sem_t ***sem, int count)
{
	int		i;
	char	name_sem[10];

	memset(name_sem, '1', 10);
	i = SEM_PRINT + 1;
	while (i <= count + SEM_PRINT)
	{
		(*sem)[i] = sem_open(name_sem, O_CREAT, S_IRWXG, 0);
		if ((*sem)[i] == SEM_FAILED)
		{
			return (1);
		}
		name_sem[0] += 1;
		i++;
	}
	return (0);
}

static sem_t	**add_get_sem(sem_t ***sem, int count)
{
	(*sem)[SEM_PRINT] = sem_open(S_PRT_NAME, O_CREAT, S_IRWXG, 1);
	if ((*sem)[SEM_PRINT] == SEM_FAILED)
	{
		sem_close((*sem)[SEM_FORKS]);
		sem_unlink(S_FRK_NAME);
		sem_close((*sem)[SEM_EXIT]);
		sem_unlink(S_EXT_NAME);
		free((*sem));
		return (NULL);
	}
	if (sem_for_eat(sem, count))
		return (NULL);
	return (*sem);
}

sem_t	**get_sem(int count)
{
	sem_t	**sem;
	int		i;

	i = 0;
	sem = malloc(sizeof(sem_t *) * (count + 3));
	if (!sem)
		return (NULL);
	sem[SEM_FORKS] = sem_open(S_FRK_NAME, O_CREAT, S_IRWXG, count);
	if (sem[SEM_FORKS] == SEM_FAILED)
	{
		free(sem);
		return (NULL);
	}
	sem[SEM_EXIT] = sem_open(S_EXT_NAME, O_CREAT, S_IRWXG, 0);
	if (sem[SEM_EXIT] == SEM_FAILED)
	{
		sem_close(sem[SEM_FORKS]);
		sem_unlink(S_FRK_NAME);
		free(sem);
		return (NULL);
	}
	return (add_get_sem(&sem, count));
}

void	close_sem(sem_t ***sem, int count)
{
	char	name_sem[10];
	int		i;

	i = SEM_PRINT + 1;
	memset(name_sem, '1', 10);
	sem_unlink(S_PRT_NAME);
	sem_unlink(S_FRK_NAME);
	sem_unlink(S_EXT_NAME);
	sem_unlink(S_EAT_NAME);
	while (i < count + SEM_PRINT)
	{
		sem_unlink(name_sem);
		name_sem[0] += 1;
		i++;
	}
	free(*sem);
}
