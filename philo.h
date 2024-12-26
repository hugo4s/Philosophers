/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:52:58 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/19 13:08:09 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_fork
{
    pthread_mutex_t fork;
    int fork_id;
    int using;
} t_fork;

typedef struct s_philo
{
    int i;
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_counter;
    int nbr_limit_meals;
    int full;
    int current_forks;
    int someone_died;
    long last_meal_time;
    t_fork *left_fork;
    t_fork *right_fork;
    t_fork *forks;
    pthread_mutex_t mutex;
    struct s_table *table;
} t_philo;

typedef struct s_table
{
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_limit_meals;
    int someone_died;
    pthread_mutex_t death_mutex;
    pthread_mutex_t start_mutex;
    pthread_mutex_t print_mutex;
    t_philo *philos;
    t_fork *forks;
} t_table;

int ft_atoi(const char *str);
int verify_number(char *s);
int parser_args(t_table *table, int ac, char **av);
int initializing(t_table *table);
void thinking(t_philo *philo);
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void *routine(void *arg);
void pick_up_forks(t_philo *philo);
long get_current_time(void);
int check_death(t_philo *philo);
void cleanup(t_table *table);
void take_forks(t_philo *philo);
void release_forks(t_philo *philo);
void *supervisor(void *arg);

#endif