#include "../headers/phil_bonus.h"

time_t	get_time(void)
{
	struct timeval	time_struct;
	unsigned long	time;

	gettimeofday(&time_struct, NULL);
	time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	if (time < 0)
		time *= -1;
	return ((time_t)time);
}

time_t	timestamp(time_t start_time)
{
	return (get_time() - start_time);
}

int	ft_usleep(time_t usec)
{
	struct timeval	time;
	time_t			zero_time;
	time_t			current_time;

	gettimeofday(&time, NULL);
	zero_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	current_time = zero_time;
	while (usec > current_time - zero_time)
	{
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		usleep(100);
	}
	return (0);
}
