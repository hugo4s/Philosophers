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

void	thinking(t_philo	*philo)
{
    printf("Philo %d is thinking\n", philo->i);
}

void eating(t_philo *philo, int time_to_eat)
{
	int	j;

	j = 0;
	while(philo->forks[j])
	{
		if(philo->forks[j].using == 0)
		{
			pthread_mutex_unlock(&philo->forks[j].fork);
			philo->forks[j].using = 1;
		}
		//continuar aqui a percorrer os garfos
		j++;
	}
}

void	sleeping(t_philo	*philo, int time_to_sleep)
{
	usleep(time_to_sleep);
    printf("Philo %d is sleeping\n", philo->i);
}