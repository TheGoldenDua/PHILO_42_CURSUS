/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dua <dua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:27:47 by del-ganb          #+#    #+#             */
/*   Updated: 2024/12/25 16:17:19 by dua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_constraints(int ac, char **av)
{
    int i;

    i = 1;
    if(ac == 6 && ft_atoi(av[5]) <= 0)
    {
        printf("Error: meals count must be a positive number\n");
        return (ERROR_INVALID_INPUT);
    }
    if(ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > 200)
    {
        printf("Error: number of philosophers must be between 1 and 200\n");
        return (ERROR_INVALID_INPUT);
    }
    while(++i < 5)
    {
        if(ft_atoi(av[i]) < 60)
        {
            printf("Error: time must more than 60 ms\n");
            return (ERROR_INVALID_INPUT);
        }
    } 
    return (CODE_SUCCESS);
}

int check_args(int ac, char **av)
{
    int i;
    int j;
    int res;
    
    if(ac < 5 || ac > 6)
    {
        printf("ERROR: At least 5 or 6 arguments are required\n");
        return (ERROR_INVALID_INPUT);
    }
    i = 1;
    while(i < ac)
    {
        j = 0;
        while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Error: argument must be a numeric value\n");
				return (ERROR_INVALID_INPUT);
			}
			j++;
		}
		i++;
    }
    res = check_constraints(ac, av);
    if(res != CODE_SUCCESS)
        return (res);
    return(CODE_SUCCESS);
}

void	show_usage(void)
{
	printf("\n*********EXAMPLE OF VALID INPUT*********\n\n");
	printf("  ./philo <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	printf("Parameters:\n");
	printf("  n_philos*:\t\t\tNumber of philosophers (1-200)\n");
	printf("  time_to_die* (ms):\t\tMinimum 60 ms\n");
	printf("  time_to_eat* (ms):\t\tMinimum 60 ms\n");
	printf("  time_to_sleep* (ms):\tMinimum 60 ms\n");
	printf("  nb_each_philo_must_eat (Optional):\tNumber of meals each philosopher must eat (0 or more)\n");
}

int main(int ac, char **av)
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