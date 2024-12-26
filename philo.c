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
    
    pthread_mutex_lock(&philo->table->start_mutex);
    pthread_mutex_unlock(&philo->table->start_mutex);

    // Caso especial para um filósofo
    if (philo->philo_nbr == 1)
    {
        take_forks(philo);
        return NULL;
    }

    if (philo->i % 2 == 0)
        usleep(200);

    while (!check_death(philo))
    {
        if (philo->nbr_limit_meals > 0 && philo->meals_counter >= philo->nbr_limit_meals)
            break;

        eating(philo);
        if (check_death(philo))
            break;

        sleeping(philo);
        if (check_death(philo))
            break;

        thinking(philo);
    }
    return NULL;
}

void *supervisor(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    int all_full;
    long current_time;

    usleep(1000);
    while (1)
    {
        i = 0;
        all_full = 1;
        while (i < table->philo_nbr)
        {
            pthread_mutex_lock(&table->death_mutex);
            current_time = get_current_time();
            
            if ((current_time - table->philos[i].last_meal_time) > table->time_to_die)
            {
                table->someone_died = 1;
                printf("\033[1;31m☠️ Philosopher %d has died\033[0m\n", table->philos[i].i);
                pthread_mutex_unlock(&table->death_mutex);
                return NULL;
            }

            if (table->nbr_limit_meals > 0 && table->philos[i].meals_counter < table->nbr_limit_meals)
                all_full = 0;

            pthread_mutex_unlock(&table->death_mutex);
            i++;
        }

        if (table->nbr_limit_meals > 0 && all_full)
        {
            pthread_mutex_lock(&table->death_mutex);
            table->someone_died = 1;
            pthread_mutex_unlock(&table->death_mutex);
            printf("\033[1;32m✅ All philosophers have eaten %d times!\033[0m\n", 
                   table->nbr_limit_meals);
            return NULL;
        }
        usleep(100);
    }
}

void thread_create(t_table *table)
{
    pthread_t thread_id[table->philo_nbr];
    pthread_t supervisor_thread;
    int i;

    pthread_mutex_init(&table->start_mutex, NULL);
    pthread_mutex_init(&table->print_mutex, NULL);
    pthread_mutex_lock(&table->start_mutex);

    i = 0;
    while (i < table->philo_nbr)
    {
        if (pthread_create(&thread_id[i], NULL, routine, (void *)&table->philos[i]) != 0)
        {
            printf("Error creating thread\n");
            return;
        }
        i++;
    }

    if (pthread_create(&supervisor_thread, NULL, supervisor, (void *)table) != 0)
    {
        printf("Error creating supervisor thread\n");
        return;
    }

    usleep(1000);
    pthread_mutex_unlock(&table->start_mutex);

    // Aguardar supervisor primeiro
    pthread_join(supervisor_thread, NULL);

    // Aguardar todas as threads de filósofos
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(thread_id[i], NULL);
        i++;
    }

    pthread_mutex_destroy(&table->start_mutex);
    pthread_mutex_destroy(&table->print_mutex);
}

int main(int argc, char **argv)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (1);

    if (!parser_args(table, argc, argv) || !initializing(table))
    {
        free(table);
        return (1);
    }

    thread_create(table);
    cleanup(table);
    return (0);
}