#include "philosophers.h"

void output(t_philo *philo, char *action)
{
   pthread_mutex_lock(&philo->data->output);
   if(!philo->data->dead)
        printf("%lldms\t%d\t %s\n", ft_at_time(ft_time_in_ms(), philo->data->time_creation), philo->id, action);
    pthread_mutex_unlock(&philo->data->output);
}

void get_fork(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&(data->forks[philo->left_fork]));
    output(philo, "Has taken a fork");
    if(philo->left_fork == philo->right_fork)
    {
        while(!data->dead)
            ;
        pthread_mutex_unlock(&(data->forks[philo->left_fork]));
        return ;
    }
    pthread_mutex_lock(&(data->forks[philo->right_fork]));
    output(philo, "Has taken a fork");
}

void eat(t_philo *philo)
{
    t_data *data;
    data = philo->data;
    philo->last_meal = ft_time_in_ms();
    pthread_mutex_lock(&(data->finish_mutex));
    if(!philo->data->dead)
        output(philo, "Is eating");
    (philo->ate_count)++;
    pthread_mutex_unlock(&(data->finish_mutex));   
    take_a_nap(data->time_eat, data); 
    pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
    pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
}

void    sleeping(t_philo *philo, t_data *data)
{
    output(philo, "Is sleeping");
    take_a_nap(philo->data->time_sleep, data);
}

void    think(t_philo *philo)
{
    output(philo, "Is thinking");
}

void *routine(void *ptr)
{
    t_philo *philo;
    t_data *data;

   
    philo = (t_philo *)ptr;
    philo->ate_count = 0;
    data = philo->data;
    if(philo->id % 2==0)
        usleep(philo->data->time_eat * 1000);
    while(!(data->dead))
    {
        get_fork(philo);
        eat(philo);
        if(data->num_already_ate)
            break ;
        sleeping(philo, data);
        think(philo);
    }
    return(NULL);
}