#include "philo.h"

bool simulation_active(t_data *data)
{
    bool running;

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

void *full_routine(void *arg)
{
    t_data *data;
    int i;
    int nb_philos;

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


