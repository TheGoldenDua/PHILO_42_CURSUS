
#include "philo.h"

int	one_philo_case(t_philo *philo)
{
	take_l_fork(philo);
	ft_usleep(get_die_time(philo->data));
	set_state(philo, DEAD);
	return (1);
}

int philo_eat(t_philo *philo)
{
    if (take_forks(philo) != 0)
        return (1);
    set_state(philo, EATING);
    print_message(philo->data, philo->philo_id, ACTION_EAT);
    update_last_meal_time(philo);
    eating_delay(philo);
    increment_meal_count(philo);
    unlock_forks(philo);
    return (0);
}

int philo_sleep(t_philo *philo)
{
    set_state(philo, SLEEPING);
    if (get_state(philo) == DEAD)
        return (1);
    print_message(philo->data, philo->philo_id, ACTION_SLEEP);
    ft_usleep(get_sleep_time(philo->data));
    return (0);
}

int philo_think(t_philo *philo)
{
    set_state(philo, THINKING);
    if (get_state(philo) == DEAD)
        return (1);
    print_message(philo->data, philo->philo_id, ACTION_THINK);
    return (0);
}

bool philo_died(t_philo *philo)
{
    bool res;
    t_data *data;

    data = philo->data;
    res = false;
    if (get_time() - get_last_eating_time(philo) > get_die_time(data)
        && get_state(philo) != EATING)
    {
        set_state(philo, DEAD);
        res = true;
    }
    return (res);
}
