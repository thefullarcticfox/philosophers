#include "philo_three.h"

static int	ft_initforks(t_common *ph)
{
	sem_unlink("/forks_sem");
	if ((ph->forks =
		sem_open("/forks_sem", O_CREAT, S_IRWXU, ph->conf->number)) ==
		SEM_FAILED)
		return (SEMAPH);
	sem_unlink("/forks_sem");
	return (0);
}

static int	ft_initlocks(t_common *ph)
{
	sem_unlink("/state_lock");
	sem_unlink("/write_lock");
	sem_unlink("/servant");
	if ((ph->conf->state_lock =
		sem_open("/state_lock", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (SEMAPH);
	if ((ph->conf->write_lock =
		sem_open("/write_lock", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (SEMAPH);
	if ((ph->conf->servant =
		sem_open("/servant", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (SEMAPH);
	sem_unlink("/state_lock");
	sem_unlink("/write_lock");
	sem_unlink("/servant");
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
	i = -1;
	while (++i < ph->conf->number)
	{
		ph->philo[i].n = i + 1;
		ph->philo[i].eaten_times = 0;
		ph->philo[i].forks = ph->forks;
	}
	return (0);
}
