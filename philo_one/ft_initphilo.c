#include "philo_one.h"

static int	ft_initforks(t_common *ph)
{
	int		i;

	if (!(ph->forks = (t_fork*)malloc(sizeof(t_fork) * ph->conf->number)))
		return (MALLOC);
	memset(ph->forks, 0, sizeof(t_fork) * ph->conf->number);
	i = -1;
	while (++i < ph->conf->number)
		if (!(ph->forks[i].fork = (pthread_mutex_t*)malloc(
			sizeof(pthread_mutex_t))))
			return (MALLOC);
	i = -1;
	while (++i < ph->conf->number)
	{
		if (!(ph->philo[i].lastmeal_lock =
			(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
			return (MALLOC);
		if (pthread_mutex_init(ph->forks[i].fork, NULL))
			return (MUTEXF);
		if (pthread_mutex_init(ph->philo[i].lastmeal_lock, NULL))
			return (MUTEXF);
	}
	return (0);
}

static int	ft_initthreads(t_common *ph)
{
	int		i;

	if (!(ph->threads = (pthread_t**)malloc(sizeof(pthread_t*) *
		ph->conf->number)))
		return (MALLOC);
	i = -1;
	while (++i < ph->conf->number)
		if (!(ph->threads[i] = (pthread_t*)malloc(sizeof(pthread_t))))
			return (MALLOC);
	return (0);
}

static int	ft_initlocks(t_common *ph)
{
	if (!(ph->conf->state_lock = (pthread_mutex_t*)malloc(
		sizeof(pthread_mutex_t))))
		return (MALLOC);
	if (pthread_mutex_init(ph->conf->state_lock, NULL))
		return (MUTEXF);
	if (!(ph->conf->write_lock = (pthread_mutex_t*)malloc(
		sizeof(pthread_mutex_t))))
		return (MALLOC);
	if (pthread_mutex_init(ph->conf->write_lock, NULL))
		return (MUTEXF);
	return (0);
}

int			ft_initphilo(t_common *ph)
{
	int		i;

	if (!(ph->philo = (t_philo*)malloc(sizeof(t_philo) * ph->conf->number)))
		return (MALLOC);
	memset(ph->philo, 0, sizeof(t_philo) * ph->conf->number);
	if ((i = ft_initlocks(ph)) < 0)
		return (i);
	if ((i = ft_initforks(ph)) < 0)
		return (i);
	if ((i = ft_initthreads(ph)) < 0)
		return (i);
	i = -1;
	while (++i < ph->conf->number)
	{
		ph->philo[i].n = i + 1;
		ph->philo[i].eaten_times = 0;
		ph->philo[i].left_fork = &(ph->forks[i]);
		ph->philo[i].right_fork = &(ph->forks[(i + 1) % ph->conf->number]);
	}
	return (0);
}
