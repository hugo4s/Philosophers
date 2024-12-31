/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:18:47 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/30 13:38:49 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_fork(t_philo *philo)
{
	if (philo->philo_nbr == 1)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		if (!check_death(philo))
			printf("🍴 Philosopher %d has taken the left fork (%d)\n",
				philo->i, philo->left_fork->fork_id);
		while (!check_death(philo))
			usleep(1000);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return ;
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->table->someone_died)
		return ;
	if (philo->i % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		if (!philo->table->someone_died)
			printf("🍴 Philosopher %d has taken a fork\n", philo->i);
		pthread_mutex_lock(&philo->left_fork->fork);
		if (!philo->table->someone_died)
			printf("🍴 Philosopher %d has taken a fork\n", philo->i);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(&philo->left_fork->fork);
		if (!philo->table->someone_died)
			printf("🍴 Philosopher %d has taken a fork\n", philo->i);
		pthread_mutex_lock(&philo->right_fork->fork);
		if (!philo->table->someone_died)
			printf("🍴 Philosopher %d has taken a fork\n", philo->i);
	}
	if (!philo->table->someone_died)
		philo->last_meal_time = get_current_time();
}

void	release_forks(t_philo *philo)
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
