/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:50:47 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/29 10:08:12 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_nbr == 1)
	{
		take_forks(philo);
		return (NULL);
	}
	while (!check_death(philo))
	{
		if (philo->nbr_limit_meals > 0
			&& philo->meals_counter >= philo->nbr_limit_meals)
			break ;
		eating(philo);
		if (check_death(philo))
			break ;
		sleeping(philo);
		if (check_death(philo))
			break ;
		thinking(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!parser_args(table, argc, argv)
		|| !initialize_table(table) || !initialize_philosophers(table))
	{
		cleanup(table);
		return (1);
	}
	pid_monitor(table);
	cleanup(table);
	return (0);
}
