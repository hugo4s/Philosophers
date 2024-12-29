/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:03:48 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/29 10:09:00 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_philosopher_death(t_table *table, int i)
{
    long current_time;
    long time_since_last_meal;

    sem_wait(&table->death_sem);
    current_time = get_current_time();
    time_since_last_meal = current_time - table->philos[i].last_meal_time;

    if (time_since_last_meal > (table->time_to_die + 5))
    {
        table->someone_died = 1;
        printf("\033[1;31m☠️ Philosopher %d has died\033[0m\n", table->philos[i].i);
        sem_post(&table->death_sem);
        return (1);
    }
    sem_post(&table->death_sem);
    return (0);
}

int check_all_philosophers_full(t_table *table)
{
    int i;
    int all_full;

    i = 0;
    all_full = 1;
    while (i < table->philo_nbr)
    {
        sem_wait(&table->death_sem);
        if (table->nbr_limit_meals > 0 && table->philos[i].meals_counter < table->nbr_limit_meals)
            all_full = 0;
        sem_post(&table->death_sem);
        i++;
    }
    return (all_full);
}

void *supervisor(void *arg)
{
    t_table *table;
    int i;

    table = (t_table *)arg;
    while (1)
    {
        i = 0;
        while (i < table->philo_nbr)
        {
            if (check_philosopher_death(table, i))
                return (NULL);
            i++;
        }
        if (table->nbr_limit_meals > 0 && check_all_philosophers_full(table))
        {
            sem_wait(&table->death_sem);
            table->someone_died = 1;
            sem_post(&table->death_sem);
            printf("\033[1;32m✅ All philosophers have eaten %d times!\033[0m\n", 
                   table->nbr_limit_meals);
            return (NULL);
        }
    }
}
