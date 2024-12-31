/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:50:47 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/30 09:54:16 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	table->forks = NULL;
	table->philos = NULL;
	if (!parser_args(table, argc, argv)
		|| !initialize_table(table) || !initialize_philosophers(table))
	{
		cleanup(table);
		return (1);
	}
	thread_monitor(table);
	cleanup(table);
	return (0);
}
