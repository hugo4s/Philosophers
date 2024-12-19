/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/19 13:06:13 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parser_args(t_table *table, int ac, char **av)
{
	int i = 0;
	if(ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return ;
	}

	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if(ac == 6)
		table->nbr_limit_meals = ft_atoi(av[5]);
	else
		table->nbr_limit_meals = 0;
	if (table->philo_nbr > 0 && table->time_to_die > 0 && table->time_to_eat > 0 && table->time_to_sleep > 0)
	{	
		printf("philo_nbr: %d\n", table->philo_nbr);
		printf("time_to_die: %d\n", table->time_to_die);
		printf("time_to_eat: %d\n", table->time_to_eat);
		printf("time_to_sleep: %d\n", table->time_to_sleep);
		if (table->nbr_limit_meals > 0)
			printf("nbr_limit_meals: %d\n", table->nbr_limit_meals);
	}
}

void	initializing(t_table	*table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	while(i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].philo_nbr = table->philo_nbr;
		table->philos[i].forks[i].fork_id = i + 1;
		table->philos[i].forks[i].using = 0;
		table->philos[i].i = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].full = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].left_fork = &table->forks[i];
		i++;
	}
}