/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:19 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 06:13:27 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (ERROR_INVALID_INPUT);
	}
	return ((int)(result * sign));
}

int	allocate_srcs(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (ERROR_MEMORY_ALLOCATION);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
		return (free(data->philos), ERROR_MEMORY_ALLOCATION);
	data->philo_threads = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_threads == NULL)
	{
		free(data->philos);
		free(data->forks);
		return (ERROR_MEMORY_ALLOCATION);
	}
	return (CODE_SUCCESS);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long sleep_time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}
