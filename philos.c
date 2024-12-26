/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dua <dua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:25 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/25 18:19:53 by dua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int count_philos(t_data *data)
{
    return (data->nb_philos);
}

bool meals_option_enabled(t_data *data)
{
    return (data->total_meals > 0);
}

t_philo_status get_philo_state(t_philo *philo)
{
    t_philo_status s;

    pthread_mutex_lock(&philo->state_lock);
    s = philo->status;
    pthread_mutex_unlock(&philo->state_lock);
    return (s);
}

void *philo_monitor(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    update_last_meal_time(philo);
    if (philo->philo_id % 2 == 0)
        ft_usleep(philo->data->eat_time - EAT_TIME_OFFSET);
    while (get_philo_state(philo) != DEAD)
    {
        if (philo_eat(philo) != 0 || get_state(philo) == DEAD)
            break;
        if (philo_sleep(philo) != 0 || get_state(philo) == DEAD)
            break;
        if (philo_think(philo) != 0 || get_state(philo) == DEAD)
            break;
    }
    return (NULL);
}

void mark_philos_dead(t_data *data)
{
    t_philo *philo;
    int i;
    int nb_philos;

    nb_philos = count_philos(data);
    philo = data->philos;
    i = -1;
    while (++i < nb_philos)
        set_state(&philo[i], DEAD);
}


///                   

int	take_r_fork(t_philo *philo)
{
	if (philo_died(philo) || get_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->r_fork);
	print_message(philo->data, philo->philo_id, ACTION_TAKE_FORKS);
	return (0);
}

int	take_l_fork(t_philo *philo)
{
	if (philo_died(philo) || get_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->l_fork);
	print_message(philo->data, philo->philo_id, ACTION_TAKE_FORKS);
	return (0);
}

int take_forks(t_philo *philo)
{
    if (count_philos(philo->data) == 1)
		return (one_philo_case(philo));
    if (philo->philo_id % 2 == 0) {
        if (pthread_mutex_lock(philo->l_fork) != 0) {
            return 1;
        }
        if (pthread_mutex_lock(philo->r_fork) != 0) {
            pthread_mutex_unlock(philo->l_fork);
            return 1;
        }
    } 
    else {
        if (pthread_mutex_lock(philo->r_fork) != 0) {
            return 1;
        }
        if (pthread_mutex_lock(philo->l_fork) != 0) {
            pthread_mutex_unlock(philo->r_fork);
            return 1;
        }
    }
    return 0;
}



// int	take_forks(t_philo *philo)
// {
// 	if (count_philos(philo->data) == 1)
// 		return (one_philo_case(philo));
// 	if (take_r_fork(philo) != 0)
// 	{
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (1);
// 	}
// 	if (take_l_fork(philo) != 0)
// 	{
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (1);
// 	}
// 	return (0);
// }


// int take_forks(t_philo *philo)
// {
//     if (count_philos(philo->data) == 1)
//         return (one_philo_case(philo));

//     // Add a small delay for odd philosophers
//     if (philo->philo_id % 2 != 0)
//         usleep(100);

//     if (pthread_mutex_lock(philo->l_fork) != 0) {
//         return 1; // Failed to lock left fork
//     }
//     if (pthread_mutex_lock(philo->r_fork) != 0) {
//         pthread_mutex_unlock(philo->l_fork); // Unlock left fork if right fork lock fails
//         return 1;
//     }

//     return 0; // Success
// }
