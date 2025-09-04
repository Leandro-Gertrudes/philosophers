/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:52 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/04 13:09:11 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philosophers(t_philosopher *philos, t_rules *rules)
{
	pthread_t	*threads;
	pthread_t	monitoring;
	int			i;
	int			j;

	threads = malloc(sizeof(pthread_t) * rules->num_philos);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, monitor_routine, philos);
	j = -1;
	while (++j < rules->num_philos)
		pthread_join(threads[j], NULL);
	pthread_join(monitoring, NULL);
	j = -1;
	while (++j < rules->num_philos)
        pthread_mutex_destroy(&rules->forks[j]);
    pthread_mutex_destroy(&rules->print_lock);
	free(threads);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (rules->num_philos == 1)
		return (ft_one_philo(philo, rules));
	while (!rules->someone_died
		&& !(rules->meals_limit && philo->count_eat == rules->meals_limit))
	{
		ft_take_forks(philo, rules);
		philo->last_meal = timestamp_ms();
		log_action(philo, "is eating", rules);
		advance_time(rules, rules->time_to_eat);
		log_action(philo, "is sleeping", rules);
		pthread_mutex_unlock(&rules->forks[philo->id - 1]);
		pthread_mutex_unlock(&rules->forks[philo->id % rules->num_philos]);
		advance_time(rules, rules->time_to_sleep);
		log_action(philo, "is thiking", rules);
		philo->count_eat++;
	}
	return (NULL);
}

void	ft_take_forks(t_philosopher *philo, t_rules *rules)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id % rules->num_philos);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&rules->forks[right]);
		log_action(philo, "has taken a fork", rules);
		pthread_mutex_lock(&rules->forks[left]);
		log_action(philo, "has taken a fork", rules);
	}
	else
	{
		pthread_mutex_lock(&rules->forks[left]);
		log_action(philo, "has taken a fork", rules);
		pthread_mutex_lock(&rules->forks[right]);
		log_action(philo, "has taken a fork", rules);
	}
}

void	*ft_one_philo(t_philosopher *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[0]);
	log_action(philo, "has taken a fork", rules);
	usleep(rules->time_to_die);
	log_action(philo, "died", rules);
	rules->someone_died = 1;
	pthread_mutex_unlock(&rules->forks[0]);
	return (NULL);
}
void	advance_time(t_rules *rules, int stop)
{
	long	begin;

	begin = timestamp_ms();
	while (!rules->someone_died && (timestamp_ms() - begin) < stop)
		usleep(100);
}
