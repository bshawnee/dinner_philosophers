#include "../headers/phil.h"

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
