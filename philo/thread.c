/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:04:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/30 09:53:38 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutexs(t_table *table, pthread_t **thread)
{
	int	i;

	*thread = malloc(sizeof(pthread_t) * table->philo_nbr);
	if (!*thread)
		return ;
	i = 0;
	pthread_mutex_init(&table->death_mutex, NULL);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i + 1;
		table->forks[i].using = 0;
		i++;
	}
}

void	create_threads(t_table *table,
			pthread_t *thread, pthread_t *supervisor_thread)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&thread[i], NULL, routine, (void *)&table->philos[i]);
		i++;
	}
	pthread_create(supervisor_thread, NULL, supervisor, (void *)table);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_join(*supervisor_thread, NULL);
}

void	thread_monitor(t_table *table)
{
	pthread_t	*thread;
	pthread_t	supervisor_thread;

	initialize_mutexs(table, &thread);
	if (!thread)
		return ;
	create_threads(table, thread, &supervisor_thread);
	free(thread);
}
