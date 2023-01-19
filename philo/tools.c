#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long aux;
	int signal = 1;

	aux = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			signal *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		aux = (aux * 10) + (*str - '0');
		str++;
	}
	return (aux * signal);
}

int	exit_error(char *error)
{
	printf("\033[0;31m\n");
	printf("Error\n%s\n", error);
	printf("\033[0m");
	return (1);
}

long long	ft_at_time(long long now, long long then)
{
	return (now - then);
}

long long	ft_time_in_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}
