/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:50:47 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/19 12:49:47 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

	if(philo->full == 0)
	{
    	eating(philo, philo->time_to_eat);
	}
    sleeping(philo, philo->time_to_sleep);
    thinking(philo);
    
    return NULL;
}

void thread_create(t_table *table)
{
    pthread_t thread_id[table->philo_nbr];
    int i;
    
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_create(&thread_id[i], NULL, routine, (void *)&table->philos[i]);
        i++;
    }

    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(thread_id[i], NULL);
        i++;
    }
}


int main(int ac, char **av)
{
	int	i;
	t_table	*table;

	table = malloc(sizeof(t_table));
	parser_args(table, ac, av);
	initializing(table);
	
	thread_create(table);
	free(table);
}
