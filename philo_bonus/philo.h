/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:52:58 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/29 10:28:19 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
#include <fcntl.h>


typedef struct s_fork
{
	sem_t			fork;
	int				fork_id;
	int				using;
}	t_fork;

typedef struct s_philo
{
	pid_t			pid;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_fork			*forks;
	struct s_table	*table;
	long			last_meal_time;
	int				i;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_counter;
	int				nbr_limit_meals;
	int				full;
	int				current_forks;
	int				someone_died;
}	t_philo;

typedef struct s_table
{
	sem_t			death_sem;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_limit_meals;
	int				someone_died;
	t_philo			*philos;
	t_fork			*forks;
}	t_table;

void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*routine(void *arg);
void	cleanup(t_table *table);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	*supervisor(void *arg);
int check_all_philosophers_full(t_table *table);
int check_philosopher_death(t_table *table, int i);
int		ft_atoi(const char *str);
long	get_current_time(void);
int		verify_number(char *s);
int		parser_args(t_table *table, int ac, char **av);
int		initialize_table(t_table *table);
int		initialize_philosophers(t_table *table);
void	setup_philosopher_attributes(t_table *table, int i, long start_time);
int		check_death(t_philo *philo);
void pid_monitor(t_table *table);
void	create_pids(t_table *table, pid_t *pid);
void	initialize_sem(t_table *table);

#endif