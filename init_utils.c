/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:28:37 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:28:48 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
}

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
