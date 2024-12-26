/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:52:58 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/26 16:00:48 by husamuel         ###   ########.fr       */
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
	pthread_mutex_t	fork;
	int				fork_id;
	int				using;
}	t_fork;

typedef struct s_philo
{
	struct s_table	*table;
	pthread_mutex_t	mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_fork			*forks;
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
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	print_mutex;
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
int		initialize_philosopher_mutexes(t_table *table, int i);
int		initialize_philosophers(t_table *table);
void	setup_philosopher_attributes(t_table *table, int i, long start_time);
int		check_death(t_philo *philo);
int		clean_up_on_failure(t_table *table, int i);
void thread_monitorate(t_table *table);
void finalize_threads(t_table *table, pthread_t *thread_id, pthread_t supervisor_thread);
void create_threads(t_table *table, pthread_t *thread_id, pthread_t *supervisor_thread);
void initialize_resources(t_table *table, pthread_t **thread_id);


#endif