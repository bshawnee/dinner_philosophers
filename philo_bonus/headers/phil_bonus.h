#ifndef PHIL_BONUS_H
# define PHIL_BONUS_H
# define COUNT_PHIL	0
# define T_T_DIE	1
# define T_T_EAT	2
# define T_T_SLEEP	3
# define MUST_EAT	4
# define COUNT_EAT	5
# define LEFT_FORK	0
# define RIGHT_FORK	1
# define SEM_PRINT	2
# define SEM_FORKS	0
# define SEM_EXIT	1
# define SEM_EAT	3
# define S_FRK_NAME	"Phil_Sem_Forks"
# define S_EXT_NAME	"Phil_Sem_Exit"
# define S_PRT_NAME	"Phil_Sem_Print"
# define S_EAT_NAME	"Phil_Eat_Print"
# define __INT_MAX	2147483647
# define __INT_MIN	-2147483648

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_arg_worker
{
	sem_t	**sem;
	time_t	*last_eat;
	time_t	zero_time;
	int		*param;
	int		id;
}			t_arg_worker;

typedef struct s_control_proc
{
	sem_t	**sem;
	int		count;
}			t_control_proc;

int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
int		ft_usleep(time_t usec);
time_t	get_time(void);
time_t	timestamp(time_t start_time);
void	free_and_exit(int *param, pid_t *forks, sem_t **sem);
void	print_msg(char *msg, int id, time_t zero, sem_t *sem);
sem_t	**get_sem(int count);
void	close_sem(sem_t ***sem, int count);
int		dinner_process(time_t zero_time, int id, int *param, sem_t **sem);
int		create_fork(int *param);
int		*correct_params(const char **argv);

#endif
