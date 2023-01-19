#include "philosophers.h"

void	take_a_nap(long long time, t_data *data)
{
	long long then;
	long long now;

	then = ft_time_in_ms();
	while (!(data->dead))
	{
		now = ft_time_in_ms();
		if (ft_at_time(now, then) >= time)
			break ;
		usleep(50);
	}
}

void	full_of_pasta(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (data->num_must_eat != -1 && i < data->num_philo
		&& philo[i].ate_count >= data->num_must_eat)
		i++;
	if (i == data->num_philo)
		data->num_already_ate = 1;
}

int	ft_start_simulation(t_data *data)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = data->philos;
	data->time_creation = ft_time_in_ms();
	while (i < data->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
			return (1);
		philo[i].last_meal = ft_time_in_ms();
		i++;
	}
	monitor(philo, data);
	ft_finish_simulation(data, philo);
	return (0);
}

void	ft_finish_simulation(t_data *data, t_philo *philo)
{
	int i = 0;
	while (i < data->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&(data->output));
}
