/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalvo4 <acalvo4@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:36:14 by acalvo4           #+#    #+#             */
/*   Updated: 2023/01/19 09:36:14 by acalvo4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (!(data->num_already_ate))
	{
		i = 0;
		while (i < data->num_philo && !(data->dead))
		{
			pthread_mutex_lock(&(data->finish_mutex));
			if ((ft_at_time(ft_time_in_ms(),
						philo[i].last_meal)) > data->time_die)
			{
				usleep(100);
				output(philo, "Has died.");
				data->dead = 1;
			}
			pthread_mutex_unlock(&(data->finish_mutex));
			i++;
		}
		if (data->dead)
			break ;
		full_of_pasta(philo, data);
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_is_valid(argc, argv))
		return (exit_error("Invalid arguments"));
	if (ft_get_args(&data, argv))
		return (exit_error("Arguments Error"));
	if (ft_init_structs(&data))
		return (exit_error("An error has occurred during the initialization"));
	ft_start_simulation(&data);
	return (0);
}
