#ifndef PHIL_H
# define PHIL_H
# define COUNT_PHIL	0
# define T_T_DIE	1
# define T_T_EAT	2
# define T_T_SLEEP	3
# define MUST_EAT	4
# define COUNT_EAT	5
# define LEFT_FORK	0
# define RIGHT_FORK	1
# define __INT_MAX	2147483647
# define __INT_MIN	-2147483648
# define EAT		1
# define SLEEP		2
# define THINK		0
# define TAKE_FORK	3
# define DIE		5

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_mtx
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_mtx;

typedef struct s_phil
{
	int				id;
	char			state;
	int				*sig_die;
	int				done_eat;
	time_t			*current_time;
	time_t			last_eat;
	pthread_t		thread;
	t_mtx			*mute;
	int				*params;
}					t_phil;

int					ft_isdigit(int ch);
time_t				get_time(void);
time_t				timestamp(time_t *start_time);
int					ft_atoi(const char *str);
void				destroy_mutex(t_mtx *mtx, const int *params);
t_phil				**init_phil(int *params);
int					all_eated(int *eat, int count);
void				*free_phil(int i, t_phil ***phil);
void				free_all(t_phil ***phil);
void				ft_swap_nums(int *n1, int *n2);
void				*thread_timer(void *arg);
void				*thread_dinner(void *arg);
int					ft_usleep(time_t usec, int *sig_die);
int					check_die(t_phil **phil);
int					init_lunch(int *param);
int					*correct_params(const char **argv);

#endif
