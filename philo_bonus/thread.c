/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:04:12 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/28 21:36:54 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_sem(t_table *table)
{
    int		i;

	i = 0;
    table->death_sem = *sem_open("/death_sem", O_CREAT, 0644, 1);
	while (i < table->philo_nbr)
    {
        char sem_name[32];
        snprintf(sem_name, sizeof(sem_name), "/fork_%d", i);

        table->forks[i].fork = *sem_open(sem_name, O_CREAT, 0644, 1);
		table->forks[i].fork_id = i + 1;
	    table->forks[i].using = 0;
        i++;
    }
}

void create_pids(t_table *table, pid_t *pid)
{
    pid_t supervisor_pid;
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        pid[i] = fork();
        i++;
    }
	supervisor_pid = fork();
	i = 0;
    while (i < table->philo_nbr)
    {
        waitpid(pid[i], NULL, 0);
        i++;
    }
	waitpid(supervisor_pid, NULL, 0);
}

void pid_monitor(t_table *table)
{
    pid_t *pid;

	pid = malloc(sizeof(pid_t) * table->philo_nbr);
    if (!pid)
        return ;
    initialize_sem(table);
    create_pids(table, pid);
	free(pid);
}
