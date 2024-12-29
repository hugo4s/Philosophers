/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:04:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/29 11:03:03 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_mutexs(t_table *table, pthread_t **thread)
{
    *thread = malloc(sizeof(pthread_t) * table->philo_nbr);
	if (!table->forks)
 		return ;
    int		i;

	i = 0;
    if (!*thread)
        return ;
    pthread_mutex_init(&table->death_mutex, NULL);
	while (i < table->philo_nbr)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
	    table->forks[i].fork_id = i + 1;
	    table->forks[i].using = 0;
        i++;
    }    
}

void create_threads(t_table *table, pthread_t *thread, pthread_t *supervisor_thread)
{
    int i;

    i = 0;
    pthread_create(supervisor_thread, NULL, supervisor, (void *)table);
    while (i < table->philo_nbr)
    {
        pthread_create(&thread[i], NULL, routine, (void*)&table->philos[i]);
        i++;
    }
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    pthread_join(*supervisor_thread, NULL);
}

void thread_monitor(t_table *table)
{
    pthread_t *thread;
    pthread_t supervisor_thread;

    initialize_mutexs(table, &thread);
    if (!thread)
        return ;

    create_threads(table, thread, &supervisor_thread);
}
