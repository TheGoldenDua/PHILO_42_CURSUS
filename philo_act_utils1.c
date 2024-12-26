/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:29:43 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:52:46 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_state(t_philo *philo, t_philo_status new_state)
{
	pthread_mutex_lock(&philo->state_lock);
	if (philo->status != DEAD)
		philo->status = new_state;
	pthread_mutex_unlock(&philo->state_lock);
}

int	get_state(t_philo *philo)
{
	t_philo_status	state;

	pthread_mutex_lock(&philo->state_lock);
	state = philo->status;
	pthread_mutex_unlock(&philo->state_lock);
	return (state);
}

long long	get_sleep_time(t_data *data)
{
	long long	sleep_time;

	pthread_mutex_lock(&data->m_sleep_time);
	sleep_time = data->sleep_time;
	pthread_mutex_unlock(&data->m_sleep_time);
	return (sleep_time);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

long long	get_die_time(t_data *data)
{
	long long	die_time;

	pthread_mutex_lock(&data->m_die_time);
	die_time = data->die_time;
	pthread_mutex_unlock(&data->m_die_time);
	return (die_time);
}
