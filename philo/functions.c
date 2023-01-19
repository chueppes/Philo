#include "philosophers.h"

int	ft_is_valid(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_get_args(t_data *data, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->num_already_ate = 0;
	data->dead = 0;
	if (data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60
		|| data->num_philo > 200 || data->num_philo < 1)
		return (1);
	if (argv[5])
	{
		data->num_must_eat = ft_atoi(argv[5]);
		if (data->num_must_eat <= 0)
			return (1);
	}
	else
		data->num_must_eat = -1;
	return (0);
}

void	ft_init_philo_struct(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].ate_count = 0;
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philo;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
}

int	ft_init_mutexes(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&(data->forks[i]), NULL);
	if (pthread_mutex_init(&(data->output), NULL)
		|| pthread_mutex_init(&(data->finish_mutex), NULL))
		return (1);
	return (0);
}

int	ft_init_structs(t_data *data)
{
	if (ft_init_mutexes(data))
		return (1);
	ft_init_philo_struct(data);
	return (0);
}
