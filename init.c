/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dua <dua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:22 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 01:12:38 by dua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	assign_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	philos[0].l_fork = &data->forks[0];
	philos[0].r_fork = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		philos[i].l_fork = &data->forks[i];
		philos[i].r_fork = &data->forks[i - 1];
	}
}

int init_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            free_forks(data, i);
            return (ERROR_MUTEX_INITIALIZATION);
        }
        i++;
    }
    assign_forks(data);
    return (CODE_SUCCESS);
}

int	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->state_lock, NULL) != 0)
		return (ERROR_MUTEX_INITIALIZATION);
	if (pthread_mutex_init(&philo->meals_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_lock);
		return (ERROR_MUTEX_INITIALIZATION);
	}
	if (pthread_mutex_init(&philo->meal_time_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->state_lock);
		pthread_mutex_destroy(&philo->meals_lock);
		return (ERROR_MUTEX_INITIALIZATION);
	}
	return (CODE_SUCCESS);
}

void	free_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].state_lock);
		pthread_mutex_destroy(&philos[i].meals_lock);
		pthread_mutex_destroy(&philos[i].meal_time_lock);
		i++;
	}
}

void	 update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
}

int init_philos(t_data *data)
{
	int			i;
	t_philo		*philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].data = data;
		philos[i].status = INACTIVE;
		if (init_philo_mutexes(&philos[i]) != CODE_SUCCESS)
		{
			free_philos(philos, i);
			return (ERROR_MUTEX_INITIALIZATION);
		}
		update_last_meal_time(&philos[i]);
		i++;
	}
	return (CODE_SUCCESS);
}

int init_data(t_data *data , int ac, char **av)
{
    data->full_philo = 0;
    data->is_active = true;
    data->nb_philos = ft_atoi(av[1]);
    data->die_time = (long long)ft_atoi(av[2]);
    data->eat_time = (long long)ft_atoi(av[3]);
    data->sleep_time = (long long)ft_atoi(av[4]);
    data->total_meals = -1;
    if(ac == 6)
        data->total_meals = ft_atoi(av[5]);
    pthread_mutex_init(&data->m_eat_time, NULL);
    pthread_mutex_init(&data->m_sleep_time, NULL);
    pthread_mutex_init(&data->m_die_time, NULL);
    pthread_mutex_init(&data->m_print, NULL);
    pthread_mutex_init(&data->m_n_philos, NULL);
    pthread_mutex_init(&data->m_keep_iter, NULL);
    pthread_mutex_init(&data->m_start_time, NULL);
    return(allocate_srcs(data));
}