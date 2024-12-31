/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/30 10:26:03 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parser_args(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (invalid_args());
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		table->nbr_limit_meals = ft_atoi(av[5]);
		if (table->nbr_limit_meals <= 0)
			return (invalid_args());
	}
	else
		table->nbr_limit_meals = 0;
	if (table->philo_nbr <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (invalid_args());
	return (1);
}

int	initialize_table(t_table *table)
{
	int	i;

	table->someone_died = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (0);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
	{
		free(table->philos);
		return (0);
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		i++;
	}
	return (1);
}

void	setup_philosopher_attributes(t_table *table, int i, long start_time)
{
	table->philos[i].table = table;
	table->philos[i].time_to_die = table->time_to_die;
	table->philos[i].time_to_eat = table->time_to_eat;
	table->philos[i].time_to_sleep = table->time_to_sleep;
	table->philos[i].philo_nbr = table->philo_nbr;
	table->philos[i].i = i + 1;
	table->philos[i].meals_counter = 0;
	table->philos[i].full = 0;
	table->philos[i].last_meal_time = start_time;
	table->philos[i].left_fork = &table->forks[i];
	table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
	table->philos[i].current_forks = 0;
	table->philos[i].nbr_limit_meals = table->nbr_limit_meals;
	table->philos[i].forks = table->forks;
	table->philos[i].someone_died = 0;
}

int	initialize_philosophers(t_table *table)
{
	long	start_time;
	int		i;

	start_time = get_current_time();
	i = 0;
	while (i < table->philo_nbr)
	{
		setup_philosopher_attributes(table, i, start_time);
		i++;
	}
	return (1);
}
