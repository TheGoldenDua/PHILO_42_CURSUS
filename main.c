/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:27:47 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/26 06:19:01 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_constraints(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		printf("Error: meals count must be a positive number\n");
		return (ERROR_INVALID_INPUT);
	}
	if (ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > 200)
	{
		printf("Error: number of philosophers must be between 1 and 200\n");
		return (ERROR_INVALID_INPUT);
	}
	while (++i < 5)
	{
		if (ft_atoi(av[i]) < 60)
		{
			printf("Error: time must be more than 60 ms\n");
			return (ERROR_INVALID_INPUT);
		}
	}
	return (CODE_SUCCESS);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;
	int	res;

	if (ac < 5 || ac > 6)
		return (printf("ERROR: 5 or 6 arguments are required\n"),
			ERROR_INVALID_INPUT);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (printf("Error: arg must be numeric\n"),
					ERROR_INVALID_INPUT);
			j++;
		}
		i++;
	}
	res = check_constraints(ac, av);
	if (res != CODE_SUCCESS)
		return (res);
	return (CODE_SUCCESS);
}

void	show_usage(void)
{
	printf("\n#### Example Command ####\n");
	printf("./philo <n_philos> <time_to_die>");
	printf("<time_to_eat> <time_to_sleep> [meals_per_philosopher]\n\n");
	printf("Arguments:\n");
	printf("  n_philos (1-200): Number of philosophers\n");
	printf("  time_to_die (>= 60 ms): Time before a philosopher dies\n");
	printf("  time_to_eat (>= 60 ms): Time to eat\n");
	printf("  time_to_sleep (>= 60 ms): Time to sleep\n");
	printf("  meals_per_philo (Optional): Meals each philo must eat\n\n");
	printf("Example:\n./philo 5 800 200 200 7\n");
}

int	main(int ac, char **av)
{
	if (check_args(ac, av) != CODE_SUCCESS)
	{
		show_usage();
		return (ERROR_INVALID_INPUT);
	}
	if (setup_task(ac, av) != CODE_SUCCESS)
	{
		printf("Error: Task setup failed.\n");
		return (ERROR_MEMORY_ALLOCATION);
	}
	return (CODE_SUCCESS);
}
