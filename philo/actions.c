/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:47:53 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/30 13:26:42 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int		dead;
	long	current_time;
	long	time_since_last_meal;

	dead = 0;
	pthread_mutex_lock(&philo->table->death_mutex);
	current_time = get_current_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->time_to_die)
		dead = 1;
	else
		dead = philo->table->someone_died;
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (dead);
}

void	eating(t_philo *philo)
{
	if (check_death(philo))
		return ;
	take_forks(philo);
	if (check_death(philo))
	{
		release_forks(philo);
		return ;
	}
	printf("\033[1;32m🍴 Philosopher %d is eating (%d meals)\033[0m\n",
		philo->i, philo->meals_counter);
	philo->last_meal_time = get_current_time();
	usleep(philo->time_to_eat * 1000);
	philo->meals_counter++;
	release_forks(philo);
}

void	sleeping(t_philo *philo)
{
	if (check_death(philo))
		return ;
	printf("\033[1;34m💤 Philosopher %d is sleeping\033[0m\n", philo->i);
	usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	if (check_death(philo))
		return ;
	printf("\033[1;33m🤔 Philosopher %d is thinking\033[0m\n", philo->i);
}
