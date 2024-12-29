/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:01:43 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/28 21:02:36 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_number(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	if (verify_number((char *)str) == -1)
		return (0);
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	cleanup(t_table *table)
{
	int	i;

	if (table)
	{
		if (table->forks)
		{
			i = table->philo_nbr;
			while (i--)
				pthread_mutex_destroy(&table->forks[i].fork);
			free(table->forks);
		}
		if (table->philos)
		{
			i = table->philo_nbr;
			while (i--)
				pthread_mutex_destroy(&table->philos[i].mutex);
			free(table->philos);
		}
		pthread_mutex_destroy(&table->death_mutex);
		free(table);
	}
}
