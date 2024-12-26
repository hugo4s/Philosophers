/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:04:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/26 16:04:16 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_resources(t_table *table, pthread_t **thread_id)
{
    *thread_id = malloc(sizeof(pthread_t) * table->philo_nbr);
    if (!*thread_id)
        return ;
    pthread_mutex_init(&table->start_mutex, NULL);
    pthread_mutex_init(&table->print_mutex, NULL);
    pthread_mutex_lock(&table->start_mutex);
}

void create_threads(t_table *table, pthread_t *thread_id, pthread_t *supervisor_thread)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_create(&thread_id[i], NULL, routine, (void *)&table->philos[i]);
        i++;
    }
    pthread_create(supervisor_thread, NULL, supervisor, (void *)table);
    pthread_mutex_unlock(&table->start_mutex);
}

void finalize_threads(t_table *table, pthread_t *thread_id, pthread_t supervisor_thread)
{
    int i;

    pthread_join(supervisor_thread, NULL);
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(thread_id[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&table->start_mutex);
    pthread_mutex_destroy(&table->print_mutex);
    free(thread_id);
}

void thread_monitorate(t_table *table)
{
    pthread_t *thread_id;
    pthread_t supervisor_thread;

    initialize_resources(table, &thread_id);
    if (!thread_id)
        return;

    create_threads(table, thread_id, &supervisor_thread);
    finalize_threads(table, thread_id, supervisor_thread);
}
