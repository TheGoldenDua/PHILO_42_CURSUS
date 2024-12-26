/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:25 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:51:17 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_status	get_philo_state(t_philo *philo)
{
	t_philo_status	s;

	pthread_mutex_lock(&philo->state_lock);
	s = philo->status;
	pthread_mutex_unlock(&philo->state_lock);
	return (s);
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	update_last_meal_time(philo);
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->data->eat_time - EAT_TIME_OFFSET);
	while (get_philo_state(philo) != DEAD)
	{
		if (philo_eat(philo) != 0 || get_state(philo) == DEAD)
			break ;
		if (philo_sleep(philo) != 0 || get_state(philo) == DEAD)
			break ;
		if (philo_think(philo) != 0 || get_state(philo) == DEAD)
			break ;
	}
	return (NULL);
}

void	mark_philos_dead(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		nb_philos;

	nb_philos = count_philos(data);
	philo = data->philos;
	i = -1;
	while (++i < nb_philos)
		set_state(&philo[i], DEAD);
}

int	take_forks(t_philo *philo)
{
	if (count_philos(philo->data) == (1))
		return (one_philo_case(philo));
	if (philo->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return (1);
		if (pthread_mutex_lock(philo->r_fork) != 0)
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (1);
		if (pthread_mutex_lock(philo->l_fork) != 0)
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
	}
	return (0);
}
