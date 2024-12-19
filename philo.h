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

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx fork;
	int	fork_id;
	int using;
}	t_fork;

typedef struct s_philo
{
	int	i;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	long	meals_counter;
	int	full;
	long	last_meal_time;
	t_fork	*forks;
	pthread_t thread_id;
}	t_philo;

typedef struct s_table
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_limit_meals;
	t_philo	*philos;
}	t_table;

int	ft_atoi(const char *str);
int	verify_number(char *s);
void	parser_args(t_table *philo_info, int ac, char **av);
void	initializing(t_table	*table);
//actions
void	thinking(t_philo	*philo);
void	eating(t_philo	*philo, int time_to_eat);
void	sleeping(t_philo	*philo, int time_to_sleep);
void *routine(void *arg);

#endif
