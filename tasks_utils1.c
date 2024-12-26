/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dua <dua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:30 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/24 20:40:11 by dua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_philos_meals(t_philo *philo)
{
    int meals_eaten;

    pthread_mutex_lock(&philo->meals_lock);
    meals_eaten = philo->meals_eaten;
    pthread_mutex_unlock(&philo->meals_lock);

    return (meals_eaten);
}

bool is_philo_done(t_data *data, t_philo *philo)
{
    bool res;

    res = false;
    if (get_philos_meals(philo) >= data->total_meals)
        res = true;
    return (res);
}

void update_simulation_status(t_data *data, bool is_active)
{
    pthread_mutex_lock(&data->m_keep_iter);
    data->is_active = is_active;
    pthread_mutex_unlock(&data->m_keep_iter);
}
