#include "philo_one.h"

static t_fork	*ft_selectfork(t_philo *ph)
{
	if (ph->n % 2)
		return (ph->left_fork);
	return (ph->right_fork);
}

static int		ft_takeforks(t_philo *ph)
{
	t_fork	*fork;
	int		i;

	if (ft_checkstate(ph))
		return (1);
	i = 0;
	fork = ft_selectfork(ph);
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->fork))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
		if (fork->lastphil != ph->n)
		{
			fork->lastphil = ph->n;
			ft_printstate(ph, TAKENFORK);
			if (++i == 2)
				break ;
			fork = ph->left_fork;
			if (ph->n % 2)
				fork = ph->right_fork;
		}
		else if (pthread_mutex_unlock(fork->fork))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
	}
	return (0);
}

static int		ft_eat(t_philo *ph)
{
	int		ret;

	ret = 0;
	if (ft_checkstate(ph))
		ret = 1;
	else
	{
		if (pthread_mutex_lock(ph->lastmeal_lock))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
		ph->lastmeal_ms = ft_getms();
		if (pthread_mutex_unlock(ph->lastmeal_lock))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
		ft_printstate(ph, EATING);
		ph->eaten_times++;
		usleep(ph->conf->ms_to_eat * 1000);
	}
	if (pthread_mutex_unlock(ph->right_fork->fork))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	if (pthread_mutex_unlock(ph->left_fork->fork))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	return (ret);
}

void			*ft_thread(void *ptr)
{
	t_philo		*ph;

	ph = (t_philo*)ptr;
	while (ph->eaten_times != ph->conf->eating_times)
	{
		if (ft_takeforks(ph))
			break ;
		if (ft_eat(ph))
			break ;
		if (ft_checkstate(ph))
			break ;
		ft_printstate(ph, SLEEPING);
		usleep(ph->conf->ms_to_sleep * 1000);
		if (ft_checkstate(ph))
			break ;
		ft_printstate(ph, THINKING);
	}
	return (NULL);
}

int				ft_runphilo(t_common *ph)
{
	int		i;

	i = -1;
	ph->conf->ms_start = ft_getms();
	while (ph->philo && ++i < ph->conf->number)
	{
		ph->philo[i].lastmeal_ms = ph->conf->ms_start;
		ph->philo[i].conf = ph->conf;
		if (pthread_create(ph->threads[i], NULL, ft_thread, &(ph->philo[i])))
			return (THREAD);
	}
	ft_philowatch(ph);
	i = -1;
	while (ph->philo && ++i < ph->conf->number)
		if (pthread_join(*(ph->threads[i]), NULL))
			return (THREAD);
	return (0);
}
