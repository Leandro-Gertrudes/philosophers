/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:44:24 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/09 10:54:21 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ERROR_NUM_ARGS "Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define ERROR_NO_ISDIGIT "Error: Invalid input. Each parameter \
must be a single positive numeric value.\n"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_rules
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_limit;
	int				someone_died;
	long			start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philosopher
{
	int			id;
	long long	last_meal;
	int			count_eat;
	t_rules		*rules;
}	t_philosopher;

// Init args
int				validate_args(int argc, char **argv);
int				check_caracters(char **arr);
void			set_args(t_rules *rules, char **argv);
t_philosopher	*ft_init_philos(t_rules *rules);
// support functions
int				ft_atoi(const char *nptr);
char			*ft_strtrim(char const *s, char const *set);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
long			timestamp_ms(void);
// Philosophers
void			ft_philosophers(t_philosopher *philo, t_rules *rules);
void			*monitor_routine(void *arg);
void			log_action(t_philosopher *philo,
					const char *action, t_rules *rules);
void			*philosopher_routine(void *arg);
void			*ft_one_philo(t_philosopher *philo, t_rules *rules);
void			ft_take_forks(t_philosopher *philo, t_rules *rules);
int				is_finished(t_philosopher *philos, t_rules *rules);
void			*someone_dead(t_philosopher *philos,
					t_rules *rules, int i, long now);
int				advance_time(t_rules *rules, int stop);
void			*unlock_and_return(t_rules *rules, t_philosopher *philo);
#endif