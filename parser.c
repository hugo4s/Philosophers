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

int parser_args(t_table *table, int ac, char **av)
{
    if (ac != 5 && ac != 6)
    {
        printf("Wrong number of arguments\n");
        return (0);
    }

    table->philo_nbr = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        table->nbr_limit_meals = ft_atoi(av[5]);
    else
        table->nbr_limit_meals = 0;

    if (table->philo_nbr <= 0 || table->time_to_die <= 0 || 
        table->time_to_eat <= 0 || table->time_to_sleep <= 0)
    {
        printf("Invalid arguments\n");
        return (0);
    }
    return (1);
}

int initializing(t_table *table)
{
    int i;
    long start_time;

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

    if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
    {
        free(table->forks);
        free(table->philos);
        return (0);
    }

    start_time = get_current_time();
    i = -1;
    while (++i < table->philo_nbr)
    {
        if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i].fork);
            free(table->forks);
            free(table->philos);
            return (0);
        }
        table->forks[i].fork_id = i + 1;
        table->forks[i].using = 0;

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

        if (pthread_mutex_init(&table->philos[i].mutex, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->philos[i].mutex);
            free(table->forks);
            free(table->philos);
            return (0);
        }
    }
    return (1);
}