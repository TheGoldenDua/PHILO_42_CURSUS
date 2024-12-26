/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dua <dua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:27:58 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/25 16:11:28 by dua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int launch_threads(t_data *data)
{
    int i;
    int total_philos;

    total_philos = count_philos(data);
    data->start_time = get_time();
    i = 0;
    while (i < total_philos)
    {
        if (pthread_create(&data->philo_threads[i], NULL, &philo_monitor, &data->philos[i]))
            return (ERROR_THREAD_CREATION);
        i++;
    }
    if (pthread_create(&data->monitor_all_alive, NULL, &monitor_routine, data))
        return (ERROR_THREAD_CREATION);
    if (meals_option_enabled(data) && pthread_create(&data->monitor_all_full, NULL,
        &full_routine, data) != 0)
        return (ERROR_THREAD_CREATION);
    return (CODE_SUCCESS);
}

int wait_for_threads(t_data *simulation)
{
    int i;
    int nb_philos;

    nb_philos = count_philos(simulation);
    i = -1;

    if (pthread_join(simulation->monitor_all_alive, NULL))
        return (ERROR_THREAD_JOINING);

    if ((simulation->total_meals > 0) && pthread_join(simulation->monitor_all_full, NULL))
        return (ERROR_THREAD_JOINING);

    while (++i < nb_philos)
    {
        if (pthread_join(simulation->philo_threads[i], NULL))
            return (ERROR_THREAD_JOINING);
    }

    return (CODE_SUCCESS);
}

void	cleanup_tasks(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = count_philos(data);
	i = -1;
	while (++i < nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].state_lock);
		pthread_mutex_destroy(&data->philos[i].meals_lock);
		pthread_mutex_destroy(&data->philos[i].meal_time_lock);
	}
	pthread_mutex_destroy(&data->m_die_time);
	pthread_mutex_destroy(&data->m_eat_time);
	pthread_mutex_destroy(&data->m_sleep_time);
	pthread_mutex_destroy(&data->m_n_philos);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_keep_iter);
	pthread_mutex_destroy(&data->m_start_time);
	free(data->philo_threads);
	free(data->philos);
	free(data->forks);
}

int	setup_task(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av) != 0)
		return (ERROR_MEMORY_ALLOCATION);
	if (init_philos(&data) != 0 || init_forks(&data) != 0)
	{
		cleanup_tasks(&data);
		return (ERROR_MEMORY_ALLOCATION);
	}
	launch_threads(&data);
	wait_for_threads(&data);
	cleanup_tasks(&data);
	return (CODE_SUCCESS);
}