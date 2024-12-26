/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:29:27 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:29:28 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_start_time(t_data *data)
{
	long long	time;

	pthread_mutex_lock(&data->m_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->m_start_time);
	return (time);
}

void	print_message(t_data *data, int id, const char *msg)
{
	long long	time;

	pthread_mutex_lock(&data->m_print);
	time = get_time() - get_start_time(data);
	if (simulation_active(data))
		printf("%llu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->m_print);
}

long long	get_last_eating_time(t_philo *philo)
{
	long long	eating_time;

	pthread_mutex_lock(&philo->meal_time_lock);
	eating_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time_lock);
	return (eating_time);
}

long long	get_eating_time(t_data *data)
{
	long long	eat_time;

	pthread_mutex_lock(&data->m_eat_time);
	eat_time = data->eat_time;
	pthread_mutex_unlock(&data->m_eat_time);
	return (eat_time);
}

void	eating_delay(t_philo *philo)
{
	ft_usleep(get_eating_time(philo->data));
}
