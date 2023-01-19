#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int id;
	int ate_count;
	int left_fork;
	int right_fork;
	long long last_meal;
	pthread_t thread;
	struct s_data *data;
} t_philo;

typedef struct s_data
{
	int num_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_must_eat;
	int num_already_ate;
	int dead;
	long long time_creation;
	pthread_mutex_t finish_mutex;
	pthread_mutex_t forks[200];
	pthread_mutex_t output;
	t_philo philos[200];
} t_data;

// functions.c
int	ft_is_valid(int argc, char **argv);
int	ft_get_args(t_data *data, char **argv);
void	ft_init_philo_struct(t_data *data);
int	ft_init_mutexes(t_data *data);

// tools.c
void	full_of_pasta(t_philo *philo, t_data *data);
int	exit_error(char *error);
long long	ft_at_time(long long now, long long then);
long long	ft_time_in_ms(void);
int	ft_atoi(const char *str);

// main.c
int	ft_start_simulation(t_data *data);
int	ft_init_structs(t_data *data);
// routine.c
void	*routine(void *ptr);

void	monitor(t_philo *philo, t_data *data);
void	output(t_philo *philo, char *action);
void	take_a_nap(long long time, t_data *data);
void	ft_finish_simulation(t_data *data, t_philo *philo);

#endif
