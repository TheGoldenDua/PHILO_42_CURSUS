/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:31:05 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:51:58 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_active(t_data *data)
{
	bool	running;

	pthread_mutex_lock(&data->m_keep_iter);
	running = data->is_active;
	pthread_mutex_unlock(&data->m_keep_iter);
	return (running);
}

void	*monitor_routine(void *data_p)
{
	int		i;
	int		n_philos;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)data_p;
	philos = data->philos;
	n_philos = count_philos(data);
	i = -1;
	while (simulation_active(data))
	{
		i = -1;
		while (++i < n_philos)
		{
			if (philo_died(&philos[i]) && simulation_active(data))
			{
				print_message(data, philos[i].philo_id, ACTION_DIED);
				update_simulation_status(data, false);
				mark_philos_dead(data);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

void	*full_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		nb_philos;

	data = (t_data *)arg;
	i = -1;
	nb_philos = count_philos(data);
	while (++i < nb_philos && simulation_active(data))
	{
		usleep(1000);
		if (is_philo_done(data, &data->philos[i]) == false)
			i = -1;
	}
	if (simulation_active(data))
	{
		update_simulation_status(data, false);
		mark_philos_dead(data);
	}
	return (NULL);
}

int	take_l_fork(t_philo *philo)
{
	if (philo_died(philo) || get_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->l_fork);
	print_message(philo->data, philo->philo_id, ACTION_TAKE_FORKS);
	return (0);
}

void	increment_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_lock);
}
