/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:25:27 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 05:57:38 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define CODE_SUCCESS 0
# define ERROR_INVALID_INPUT 1
# define ERROR_MEMORY_ALLOCATION 2
# define ERROR_MUTEX_INITIALIZATION 3
# define ERROR_THREAD_CREATION 4
# define ERROR_THREAD_JOINING 5

# define ACTION_TAKE_FORKS "has taken a fork"
# define ACTION_THINK "is thinking"
# define ACTION_SLEEP "is sleeping"
# define ACTION_EAT "is eating"
# define ACTION_DIED "died"

# define EAT_TIME_OFFSET 10

typedef enum s_philo_status
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	SATISFIED = 4,
	INACTIVE = 5
}						t_philo_status;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					philo_id;
	int					meals_eaten;
	long long			last_meal;
	t_data				*data;
	t_philo_status		status;
	pthread_mutex_t		state_lock;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		meals_lock;
	pthread_mutex_t		meal_time_lock;
}						t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					total_meals;
	long long			eat_time;
	long long			die_time;
	long long			sleep_time;
	int					full_philo;
	bool				is_active;
	long long			start_time;
	pthread_mutex_t		m_eat_time;
	pthread_mutex_t		m_die_time;
	pthread_mutex_t		m_sleep_time;
	pthread_mutex_t		m_print;
	pthread_mutex_t		m_n_philos;
	pthread_mutex_t		m_keep_iter;
	pthread_mutex_t		m_start_time;
	pthread_t			monitor_all_alive;
	pthread_t			monitor_all_full;
	pthread_t			*philo_threads;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

int						init_forks(t_data *data);
int						init_philos(t_data *data);
int						init_data(t_data *data, int ac, char **av);
int						ft_atoi(const char *str);
int						allocate_srcs(t_data *data);
long long				get_time(void);
void					ft_usleep(long long sleep_time);
int						check_constraints(int ac, char **av);
int						check_args(int ac, char **av);
void					show_usage(void);
void					print_message(t_data *data, int id, const char *msg);
void					update_last_meal_time(t_philo *philo);
long long				get_last_eating_time(t_philo *philo);
void					eating_delay(t_philo *philo);
void					increment_meal_count(t_philo *philo);
void					set_state(t_philo *philo, t_philo_status new_state);
int						get_state(t_philo *philo);
long long				get_sleep_time(t_data *data);
void					unlock_forks(t_philo *philo);
long long				get_die_time(t_data *data);
int						one_philo_case(t_philo *philo);
int						philo_eat(t_philo *philo);
int						philo_sleep(t_philo *philo);
int						philo_think(t_philo *philo);
bool					philo_died(t_philo *philo);
int						count_philos(t_data *data);
bool					meals_option_enabled(t_data *info);
t_philo_status			get_philo_state(t_philo *philo);
void					*philo_monitor(void *arg);
void					mark_philos_dead(t_data *data);
int						take_l_fork(t_philo *philo);
int						take_forks(t_philo *philo);
bool					simulation_active(t_data *data);
void					*monitor_routine(void *data_p);
void					*full_routine(void *arg);
int						get_philos_meals(t_philo *philo);
bool					is_philo_done(t_data *data, t_philo *philo);
void					update_simulation_status(t_data *data, bool is_active);
int						launch_threads(t_data *data);
int						wait_for_threads(t_data *simulation);
void					cleanup_tasks(t_data *data);
int						setup_task(int ac, char **av);
long long				get_eating_time(t_data *data);
long long				get_start_time(t_data *data);
int						init_philo_mutexes(t_philo *philo);
void					free_philos(t_philo *philos, int count);
void					assign_forks(t_data *data);
void					free_forks(t_data *data, int count);
int						check_overflow(long result, int sign);
int						is_digits(const char *arg);

#endif