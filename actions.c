/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:47:53 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/19 13:11:26 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philo *philo)
{
    int dead;

    pthread_mutex_lock(&philo->table->death_mutex);
    dead = philo->table->someone_died;
    pthread_mutex_unlock(&philo->table->death_mutex);
    return (dead);
}

void eating(t_philo *philo)
{
    if (check_death(philo))
        return;
        
    take_forks(philo);
    
    if (check_death(philo))
    {
        release_forks(philo);
        return;
    }
    
    pthread_mutex_lock(&philo->table->death_mutex);
    philo->last_meal_time = get_current_time();
    philo->meals_counter++;
    pthread_mutex_unlock(&philo->table->death_mutex);
    
    pthread_mutex_lock(&philo->table->print_mutex);
    if (!check_death(philo))
        printf("\033[1;32m🍴 Philosopher %d is eating (%d meals)\033[0m\n", 
               philo->i, philo->meals_counter);
    pthread_mutex_unlock(&philo->table->print_mutex);
           
    usleep(philo->time_to_eat * 1000);
    
    release_forks(philo);
}

void sleeping(t_philo *philo)
{
    if (check_death(philo))
        return;
        
    printf("\033[1;34m💤 Philosopher %d is sleeping\033[0m\n", philo->i);
    usleep(philo->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
    if (check_death(philo))
        return;
        
    printf("\033[1;33m🤔 Philosopher %d is thinking\033[0m\n", philo->i);
}

void take_forks(t_philo *philo)
{
    // Para um filósofo sozinho, só precisa tentar pegar um garfo
    if (philo->philo_nbr == 1)
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        if (!check_death(philo))
            printf("🍴 Philosopher %d took the left fork (%d)\n", 
                   philo->i, philo->left_fork->fork_id);
        // Espera até morrer
        while (!check_death(philo))
            usleep(1000);
        pthread_mutex_unlock(&philo->left_fork->fork);
        return;
    }

    if (philo->i % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        if (!check_death(philo))
            printf("🍴 Philosopher %d took the right fork (%d)\n", 
                   philo->i, philo->right_fork->fork_id);
        
        pthread_mutex_lock(&philo->left_fork->fork);
        if (!check_death(philo))
            printf("🍴 Philosopher %d took the left fork (%d)\n", 
                   philo->i, philo->left_fork->fork_id);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        if (!check_death(philo))
            printf("🍴 Philosopher %d took the left fork (%d)\n", 
                   philo->i, philo->left_fork->fork_id);
        
        pthread_mutex_lock(&philo->right_fork->fork);
        if (!check_death(philo))
            printf("🍴 Philosopher %d took the right fork (%d)\n", 
                   philo->i, philo->right_fork->fork_id);
    }
}

void release_forks(t_philo *philo)
{
    if (philo->i % 2 == 0)
    {
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
    }
    else
    {
        pthread_mutex_unlock(&philo->right_fork->fork);
        pthread_mutex_unlock(&philo->left_fork->fork);
    }
}